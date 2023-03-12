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
				xjob.totalDurationOnStart += duration;
				xjob.tasks.push(xTask);
				machine = 999;
				duration = 999;
			}
		}
		this->jobs.push_back(xjob);
	}
}

JobShop::~JobShop() {
	// Auto-generated destructor stub
}

void JobShop::schedule() {
	unsigned long globTime = 0;

	while (!done()) {
		//calculate critPath
		auto longestDurationJob = std::max_element( jobs.begin(), jobs.end(),
		[]( const Job &a, const Job &b )
		{
			return a.totalDurationOnStart < b.totalDurationOnStart;
		});
		unsigned long longestDur = longestDurationJob->totalDurationOnStart;

		//calculate slack
		std::for_each(jobs.begin(),jobs.end(), [&](Job& j){
			j.slack = longestDur - j.totalDurationOnStart;
		});

		//sort by slack
		std::sort(jobs.begin(), jobs.end(), [](Job &j0, Job &j1) {
			return j0.slack < j1.slack;
		});

		//use algorythm
		for (Job &j : jobs) {
			if (!j.tasks.empty()) {
				//get currenttask and currentmachine
				Task &currentTask = j.tasks.front();
				Machine &currentMachine = machines.at(currentTask.machineNumber);

				//lambda that checks all preconditions
				auto shouldDoTask = [*this, j, currentMachine]() {
					if (currentMachine.busy) { //if currentmachine busy, not schedulable
						return false;
					}
					for (Machine m : machines) { //if job is still running, then tasks before this tasks are still running so this task cant run
						if ((m.currentJobId == j.id)) {
							if (m.busy) {
								return false;
							}
						}
					}
					//if macine is free and task before selected tasks are done, task is schedulable
					return true;
				};

				//checks with lambda if task should be planned
				if (shouldDoTask()) {
					//set currenttask on currentmachine
					currentMachine.currentTask = currentTask;
					currentMachine.busy = true;
					currentMachine.currentJobId = j.id;
					//registers start time only when the first task is planned
					if (!j.started) {
						j.start = globTime;
						j.started = true;
					}
					j.tasks.pop(); //pops task from queue when planned
				}
			}
		}

		//calculate shortest time left on a machine
		unsigned long shortestTimeLeft = 0;
		shortestTimeLeft--; //overflow value, for checkingin loop

		std::for_each(machines.begin(),machines.end(), [&](const Machine& m){
			if ((m.currentTask.duration < shortestTimeLeft) && m.busy) {
				shortestTimeLeft = m.currentTask.duration;
			}
		});

		//update global time
		globTime += shortestTimeLeft;

		//update duration on machines
		for (Machine &m : machines) {
			auto currentJob = std::find_if(jobs.begin(), jobs.end(),
					[&m](Job &j) {
						return j.id == m.currentJobId;
					});
			if (m.busy) {
				m.currentTask.duration -= shortestTimeLeft;
				if (currentJob->totalDurationOnStart >= shortestTimeLeft) {
					currentJob->totalDurationOnStart -= shortestTimeLeft;
				} else {
					std::cout << "ERROR, TASK TAKES TOO LONG" << std::endl;
					abort();
				}
			}
			if (m.currentTask.duration <= 0) {
				m.busy = false;
				if (m.currentJobId != 99999999) {
					if (currentJob->tasks.empty() && !currentJob->finished) {
						currentJob->finished = true;
						currentJob->end = globTime; //updates end time when the last task is FINISHED.
					}
				}
			}
		}
	}
}

bool JobShop::done() {
	bool returnV = true;
	std::for_each(jobs.begin(),jobs.end(), [&](const Job& s){
		if(!s.finished) {
			returnV = false;
		}
	});
	return returnV;
}

void JobShop::sortById() {
	std::sort(jobs.begin(), jobs.end(), [](Job &j1, Job &j2) {
		return j1.id < j2.id;
	});
}
