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
				xjob.setTotalDurationOnStart(xjob.getTotalDurationOnStart() + duration);
				xjob.getTasks().push(xTask);
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
	//keep track of global timing. used for start and endtimes of jobs.
	unsigned long globTime = 0;

	while (!done()) {
		//calculate critPath
		auto longestDurationJob = std::max_element( jobs.begin(), jobs.end(),
		[]( const Job &a, const Job &b )
		{
			return a.getTotalDurationOnStart() < b.getTotalDurationOnStart();
		});
		unsigned long longestDur = longestDurationJob->getTotalDurationOnStart();

		//calculate slack
		std::for_each(jobs.begin(),jobs.end(), [&](Job& j){
			j.setSlack(longestDur - j.getTotalDurationOnStart());
		});

		//sort by slack
		std::sort(jobs.begin(), jobs.end(), [](Job &j0, Job &j1) {
			return j0.getSlack() < j1.getSlack();
		});

		//use algorythm
		for (Job &j : jobs) {
			if (!j.getTasks().empty()) {
				//get currenttask and currentmachine
				Task &currentTask = j.getTasks().front();
				Machine &currentMachine = machines.at(currentTask.machineNumber);

				//lambda that checks all preconditions
				auto shouldDoTask = [*this, j, currentMachine]() {
					if (currentMachine.isBusy()) { //if currentmachine busy, not schedulable
						return false;
					}
					//if job is still running, then tasks before this tasks are still running so this task cant run
					for (Machine m : machines) {
						if ((m.getCurrentJobId() == j.getId())) {
							if (m.isBusy()) {
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
					currentMachine.setCurrentTask(currentTask);
					currentMachine.setBusy(true);
					currentMachine.setCurrentJobId(j.getId());
					//registers start time only when the first task is planned
					if (!j.isStarted()) {
						j.setStart(globTime);
						j.setStarted(true);
					}
					(j.getTasks()).pop(); //pops task from queue when planned
				}
			}
		}

		//calculate shortest time left on a machine
		unsigned long shortestTimeLeft = 0;
		shortestTimeLeft--; //overflow value, for checkingin loop
		std::for_each(machines.begin(),machines.end(), [&](Machine& m){
			if ((m.getCurrentTask()->duration < shortestTimeLeft) && m.isBusy()) {
				shortestTimeLeft = m.getCurrentTask()->duration;
			}
		});

		//update global time
		globTime += shortestTimeLeft;

		//update duration on machines
		for (Machine &m : machines) {
			//get job that is scheduled/running on current machine
			auto currentJob = std::find_if(this->jobs.begin(), this->jobs.end(),
					[&m](Job &j) {
						return j.getId() == m.getCurrentJobId();
					});
			//if machine is busy, update duration left, if not possible, scheduling is not possible of given input
			if (m.isBusy()) {
				m.getCurrentTask()->duration -= shortestTimeLeft;
				if (currentJob->getTotalDurationOnStart() >= shortestTimeLeft) {
					currentJob->setTotalDurationOnStart(currentJob->getTotalDurationOnStart() - shortestTimeLeft);
				} else {
					std::cout << "ERROR, TASK TAKES TOO LONG" << std::endl;
					abort();
				}
			}
			//if duration of currenttask on machine is 0, machine is not busy anymore
			if (m.getCurrentTask()->duration <= 0) {
				m.setBusy(false);
				//if currentjobid is a valid id
				if (m.getCurrentJobId() != 99999999) {
					//update job endtime if last task if finished, and label as finished
					if (currentJob->getTasks().empty() && !currentJob->isFinished()) {
						currentJob->setFinished(true);
						currentJob->setEnd(globTime);
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
