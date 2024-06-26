/*
 * JobShop.cpp
 *
 *  Created on: Mar 9, 2023
 *      Author: finn
 */

#include "JobShop.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <limits>

JobShop::JobShop(std::ifstream &file, std::vector<Machine> &machines) {
	//Get amount of Jobs and Machines
	std::string token;
	std::getline(file, token);
	bool tab = false;
	unsigned long jobCount;
	unsigned long machineCount; // MachineCount = TaskCount
	for (unsigned long i = 0; i < token.size(); i++)
	{
		if (token[i] == '\t'){ //first rule has tab
			tab = true;
		}
	}

	std::stringstream x(token);
	std::string machine = "";
	std::getline(x, machine, (tab) ? '	' : ' ');
	jobCount = std::stoi(machine);
	std::getline(x, machine, '	');
	machineCount = std::stoi(machine);

	//create machines
	for (unsigned long i = 0; i < machineCount; ++i) {
		Machine m(i);
		this->machines.push_back(m);
	}

	//create jobs and tasks
	for (unsigned long i = 0; i < jobCount; ++i) {
		int TaskId = 0;
		std::vector<Task> tasks;
		std::getline(file, token);
		std::vector<std::string> v;
		std::stringstream ss(token);
		std::string word;

		Job xjob = Job(i);

		unsigned long machine = 999;
		unsigned long duration = 999;
		while (ss >> word) { // Extract word from the stream.
			if (machine == 999) {
				machine = std::stoi(word);
			} else {
				duration = std::stoi(word);
				Task xTask = Task(machine, duration);
				TaskId++;
				xjob.setTotalDurationOnStart(xjob.getTotalDurationOnStart() + duration);
				xjob.getTasks().push(xTask);
				machine = 999;
				duration = 999;
			}
		}
		this->jobs.push_back(xjob);
	}
}

void JobShop::schedule() {
    unsigned long globTime = 0;

    while (!done()) {
        // Calculate critical path
        auto longestDurationJob = std::max_element(jobs.begin(), jobs.end(),
        [](const Job &a, const Job &b) {
            return a.getTotalDurationOnStart() < b.getTotalDurationOnStart();
        });
        unsigned long longestDur = longestDurationJob->getTotalDurationOnStart();

        // Calculate slack
        std::for_each(jobs.begin(), jobs.end(), [&](Job &j) {
            j.setSlack(longestDur - j.getTotalDurationOnStart());
        });

        // Sort jobs by slack
        std::sort(jobs.begin(), jobs.end(), [](Job &j0, Job &j1) {
            return j0.getSlack() < j1.getSlack();
        });

        // Use algorithm to schedule tasks
        for (Job &j : jobs) {
            if (!j.getTasks().empty()) {
                Task &currentTask = j.getTasks().front();
                Machine &currentMachine = machines.at(currentTask.machineNumber);

                auto shouldDoTask = [&]() {
                    if (currentMachine.isBusy()) return false;
                    for (Machine &m : machines) {
                        if (m.getCurrentJobId() == j.getId() && m.isBusy()) return false;
                    }
                    return true;
                };

                if (shouldDoTask()) {
                    currentMachine.setCurrentTask(currentTask);
                    currentMachine.setBusy(true);
                    currentMachine.setCurrentJobId(j.getId());
                    if (!j.isStarted()) {
                        j.setStart(globTime);
                        j.setStarted(true);
                    }
                    j.getTasks().pop();
                }
            }
        }

        // Calculate shortest time left on a machine
        unsigned long shortestTimeLeft = std::numeric_limits<unsigned long>::max();
        for (Machine &m : machines) {
            if (m.isBusy() && m.getCurrentTask()->duration < shortestTimeLeft) {
                shortestTimeLeft = m.getCurrentTask()->duration;
            }
        }

        if (shortestTimeLeft == std::numeric_limits<unsigned long>::max()) {
            break; // No tasks are running, should not happen if while(!done()) is correct
        }

        // Update global time
        globTime += shortestTimeLeft;

        // Update durations on machines
        for (Machine &m : machines) {
            if (m.isBusy()) {
                Task *currentTask = m.getCurrentTask();
                currentTask->duration -= shortestTimeLeft;

                auto currentJob = std::find_if(jobs.begin(), jobs.end(), [&](Job &j) {
                    return j.getId() == m.getCurrentJobId();
                });

                if (currentJob != jobs.end()) {
                    if (currentJob->getTotalDurationOnStart() >= shortestTimeLeft) {
                        currentJob->setTotalDurationOnStart(currentJob->getTotalDurationOnStart() - shortestTimeLeft);
                    } else {
                        std::cout << "ERROR, TASK TAKES TOO LONG" << std::endl;
                        abort();
                    }

                    if (currentTask->duration <= 0) {
                        m.setBusy(false);
                        if (currentJob->getTasks().empty() && !currentJob->isFinished()) {
                            currentJob->setFinished(true);
                            currentJob->setEnd(globTime);
                        }
                    }
                }
            }
        }
    }
}


bool JobShop::done() {
	//working with return value because otherwise we return only out of the for loop
	bool returnV = true;
	std::for_each(jobs.begin(),jobs.end(), [&](const Job& s){
		if(!s.isFinished()) {
			returnV = false;
		}
	});
	return returnV;
}

void JobShop::sortById() {
	//sort jobs by job id
	std::sort(jobs.begin(), jobs.end(), [](Job &j1, Job &j2) {
		return j1.getId() < j2.getId();
	});
}

std::vector<Job> JobShop::getJobs(){
	return this->jobs;
}
