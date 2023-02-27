/*
 * main.cpp
 *
 *  Created on: Feb 17, 2023
 *      Author: finn
 */
#include "JobShop.h"
#include "Task.h"
#include "Job.h"
#include "Machine.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

//Function to make jobshop from file.
JobShop makeJobShop(std::ifstream &file, std::vector<Machine> &machines) {
	JobShop jobshop;

	//Get amount of Jobs and Machines
	std::string token;
	std::getline(file, token);
	unsigned long jobCount = std::stoi(token);
	std::cout << "jobCount:" << jobCount << std::endl;
	//std::getline(file, token, ' ');
	unsigned long machineCount = std::stoi(token); // MachineCount = TaskCount
	std::cout << "machineCount:" << machineCount << std::endl;

	//create machines
	//machineCount = 5;
	for (unsigned long i = 0; i < machineCount; ++i) {
		Machine m(i);
		machines.push_back(m);
	}

	//Loop door
	int TaskId = 0;
	for (unsigned long i = 0; i < jobCount; ++i) {
		std::vector<Task> tasks;
		std::getline(file, token);
		//std::cout << token << std::endl;
		std::vector<std::string> v;

		std::stringstream ss(token);

		std::string word;

		Job xjob = Job(i);

		int machine = 999;
		int duration = 999;
		while (ss >> word) { // Extract word from the stream.
			if (machine == 999) {
				machine = std::stoi(word);
			} else {
				duration = std::stoi(word);
//				std::cout << "job " << i << " machine: " << machine
//						<< " duration: " << duration << std::endl;
				Task xTask = Task(machine, duration, TaskId);
				TaskId++;
				xjob.tasks.push_back(xTask);
				machine = 999;
				duration = 999;
			}
		}
		jobshop.jobs.push_back(xjob);
	}
	return jobshop;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "No path provided" << '\n';
	}

	std::vector<Machine> machines;

	std::ifstream file;
	file.open(argv[argc - 1]);
	if (file.is_open()) {
		std::cout << " file provided" << '\n';
		JobShop x = makeJobShop(file, machines);

//	`	check if jobshop is build properly
		for (Job &j : x.jobs) {
			for (Task &t : j.tasks) {
				std::cout << "Task " << t.getId() << " duration: "
						<< t.getDuration() << std::endl;
			}
		}
//		for (Machine &m : machines) {
//			std::cout << "Machine build with ID: " << m.id << std::endl;
//		}

		//algorithm
		//1) find longest task (i guess longest job?)

		Job *longest_job = x.getLongestJob();
		std::cout << "Duration of longest job: " << longest_job->getDuration()
				<< std::endl;

		// 2) slack bepalen
		for (Job &j : x.jobs) {
			j.calcSlack(longest_job);
		}

		for (Job j : x.jobs) {
			std::cout << "SLACK CALCULATED: " << j.slack << std::endl;
		}
		//sorteer Jobs op slack
		std::sort(x.jobs.begin(), x.jobs.end());//Gebruikt operator<() die op slack controleert.
		for (Job j : x.jobs) {
			std::cout << "SORTED SLACK CALCULATED: " << j.slack << std::endl;
		}
		// 3) loopen over taken in volgorde van slack, als taak is schedulebaar (taak is niet bezig) en machine is vrij, schedulen.
		//  for()
		int timeT = 0;
		while (!x.everyTaskPlanned()) {
			for (Job &j : x.jobs) {
				if (!j.isDone()) {//Check of de job niet klaar is. Anders gaat hij buiten de vector....

					Task &currentTask = j.tasks.at(j.taskIterator); //Een reference naar de taak die we willen inplannen.
					if(currentTask.getDuration() == 0) {
											j.taskIterator++;
											if(!j.startTimeIsSet()) {
												j.setStartTime(timeT);
											}
										}

					std::cout << "CurrentTask Duration " << currentTask.getDuration() <<std::endl;
					std::cout << "CurrentJob Slack " << j.slack << std::endl;
					std::cout << "looking for machine " << currentTask.getMachineNr() <<std::endl;
					Machine &currentMachine = machines.at(
							currentTask.getMachineNr()); //Een reference naar de machine die we willen inplannen.
					std::cout << "MACHINE BUSY: " << currentMachine.timeBusy;
					if (currentTask.isSchedulable()) {
						std::cout << "SCHEDULABLE" << std::endl;
						//if duration is 0 skip picking task and just ignore task.
						if(currentTask.getDuration() == 0 && currentMachine.getTimeBusy() != 0) {
							std::cout << "Duration is 0 so skip" << std::endl;
							currentTask.setIfSchedulable(false);
							j.taskIterator += 1;
						}
						if (currentMachine.getTimeBusy() == 0) {//Kijk of de machine vrij is.
std::cout << "Tijd om in te plannen, Tijd om in te plannen, Tijd om in te plannen " << std::endl;
							currentMachine.setTimeBusy(currentTask.getDuration());
							currentTask.setIfSchedulable(false);//De taak is nu ingepland en kan verder genegeerd worden.
							j.taskIterator += 1;//Voor deze job kan de volgende ronde een andere taak ingepland worden.
							std::cout << "SCHEDULED TASK NR: "
									<< currentTask.getId() << " TO MACHINE NR: "
									<< currentMachine.id << std::endl;

							if(!j.startTimeIsSet()) {
								j.setStartTime(timeT);
								std::cout << "setStartTime of Job " << j.id << " to " << j.startTime << std::endl;
							}
							j.setStopTime(j.getDuration());
						}
					}
				}
			}
			//Verkrijg de kortste tijd die een machine nog te draaien heeft.
			unsigned long shortestTaskDuration = machines.at(0).getTimeBusy(); //Houdt bij hoelang de kortste ingeplande taak duurt.
			for (Machine m : machines) {
				if ((shortestTaskDuration > m.getTimeBusy())
						&& (m.getTimeBusy() != 0)) {
					shortestTaskDuration = m.getTimeBusy();
				}
				if(shortestTaskDuration == 0 && m.getTimeBusy() != 0) {
					shortestTaskDuration = m.getTimeBusy();
				}
			}
			std::cout << shortestTaskDuration << " IS SHORTEDTASKDURATION" << std::endl; //die is 0, dat mag niet!

			//Update de tijd die de machines nog bezig zijn met de tijd van de machine die het kortst bezig is.
			std::for_each(machines.begin(), machines.end(),
					[shortestTaskDuration](Machine &m) {
						if (m.getTimeBusy() >= shortestTaskDuration) {
							m.setTimeBusy(
									m.getTimeBusy() - shortestTaskDuration);
						}
					});
			//Update de slack van elke Job.
			std::for_each(x.jobs.begin(), x.jobs.end(),
					[shortestTaskDuration](Job &job) {
						if (job.slack >= shortestTaskDuration) {
							job.slack -= shortestTaskDuration;
						}
					});
			//Sorteer opnieuw de Jobs op slack.
			std::sort(x.jobs.begin(), x.jobs.end()); //Gebruikt operator<() die op slack controleert.

			//shortest task duratoin is 0?
//			if(shortestTaskDuration == 0) {
//				shortestTaskDuration = 100;
//			}
			std::cout << "MOVED " << shortestTaskDuration
					<< " TIME-UNITS INTO THE FUTURE" << std::endl;
			timeT += shortestTaskDuration;

		}

		//sort on job id
		sort(x.jobs.begin(), x.jobs.end(),
		    [](const Job & a, const Job & b) -> bool
		{
		    return a.id < b.id;
		});

		std::cout << "----------OUTPUT-------------" << std::endl;
		for(Job &j : x.jobs) {
			std::cout << j.id << " " << j.startTime << " " << (j.getDuration()+j.startTime) << std::endl;
		}

	} else {
		std::cout << "No file provided" << '\n';
	}

	return 0;
}

