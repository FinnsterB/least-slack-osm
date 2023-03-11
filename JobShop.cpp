/*
 * JobShop.cpp
 *
 *  Created on: Mar 9, 2023
 *      Author: finn
 */

#include "JobShop.h"

#include <algorithm>
#include <iostream>

JobShop::JobShop() {
	// TODO Auto-generated constructor stub

}

JobShop::~JobShop() {
	// TODO Auto-generated destructor stub
}

void JobShop::schedule() {
	//variable to calculate critPath
	unsigned long longestDur = 0;
	//Variable to keep global time
	unsigned long globTime = 0;

	while (!done()) {

		//calculate critPath
		longestDur = 0;
		for (Job &j : jobs) {
			if (j.totalDurationOnStart > longestDur) {
				longestDur = j.totalDurationOnStart;
			}
		}

		//calculate slack
		for (Job &j : jobs) {
			j.slack = longestDur - j.totalDurationOnStart;
		}
		//sort by slack
		std::sort(jobs.begin(), jobs.end(), [](Job &j0, Job &j1) {
			return j0.slack < j1.slack;
		});

		//use algorythm
		for (Job &j : jobs) {
			if (!j.tasks.empty()) {
				//useful references
				Task &currentTask = j.tasks.front();
				Machine &currentMachine = machines.at(
						currentTask.machineNumber);

				//lambda that checks all preconditions
				auto shouldDoTask = [*this, j, currentMachine]() {
					if (currentMachine.busy) {
						return false;
					}
					for (Machine m : machines) {
						if ((m.currentJobId == j.id)) {
							if (m.busy) {
								return false;
							}
						}
					}
					return true;
				};

				//checks with lambda if task should be planned
				if (shouldDoTask()) {
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
		shortestTimeLeft--;
		for (Machine &m : machines) {
			if ((m.currentTask.duration < shortestTimeLeft) && m.busy) {
				shortestTimeLeft = m.currentTask.duration;
			}
		}

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
					if (currentJob->tasks.empty()
							&& !currentJob->finished) {
						currentJob->finished = true;
						currentJob->end = globTime; //updates end time when the last task is FINISHED.
					}
				}
			}
		}

	}
}

bool JobShop::done() {
	for (Job &j : jobs) {
		if(j.end == 0){
		//if (!j.tasks.empty()) {
			return false;
		}
	}
	return true;
}

void JobShop::sortById() {
	std::sort(jobs.begin(), jobs.end(), [](Job &j1, Job &j2) {
		return j1.id < j2.id;
	});
}
