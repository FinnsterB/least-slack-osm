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
	std::getline(file, token, ' ');
	unsigned long jobCount = std::stoi(token);
	std::cout << "jobCount:" << jobCount << std::endl;
	std::getline(file, token);
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
			std::cout << "Line: " << token << std::endl;

			if (machine == 999) {
				machine = std::stoi(word);
				std::cout << "Machine: " << machine;
			} else {
				duration = std::stoi(word);
				std::cout <<"task" << TaskId << "job " << i << " machine: " << machine
						<< " duration: " << duration << std::endl;
				Task xTask = Task(machine, duration, TaskId);
				TaskId++;
				xjob.tasks.push_back(xTask);
				machine = 999;
				duration = 999;
			}
		}
		xjob.taskIterator = xjob.tasks.begin();
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
//		for (Job &j : x.jobs) {
//			for (Task &t : j.tasks) {
////				std::cout << "Task " << t.getId() << " duration: "
////						<< t.getDuration() << std::endl;
//			}
//		}
//		for (Machine &m : machines) {
//			std::cout << "Machine build with ID: " << m.id << std::endl;
//		}

		//algorithm
		//1) find longest task (i guess longest job?)

		Job *longest_job = x.getLongestJob();
//		std::cout << "Duration of longest job: " << longest_job->getDuration()
//				<< std::endl;

		// 2) slack bepalen
		for (Job &j : x.jobs) {
			j.calcSlack(longest_job);
		}

//		for (Job j : x.jobs) {
//			std::cout << "SLACK CALCULATED: " << j.slack << std::endl;
//		}
		//sorteer Jobs op slack
		std::sort(x.jobs.begin(), x.jobs.end());//Gebruikt operator<() die op slack controleert.
//		for (Job j : x.jobs) {
//			std::cout << "SORTED SLACK CALCULATED: " << j.slack << std::endl;
//		}
		// 3) loopen over taken in volgorde van slack, als taak is schedulebaar (taak is niet bezig) en machine is vrij, schedulen.
		//  for()
//		for (Job &j : x.jobs) {
//			if (!j.isDone()) {//Check of de job niet klaar is. Anders gaat hij buiten de vector....
//				Task &currentTask = j.tasks.at(j.taskIterator); //Een reference naar de taak die we willen inplannen.
//				std::cout << "CurrentTask Duration: " << currentTask.getDuration();
//			}
//		}
		unsigned long timeT = 0;
		int i = 0;
		for(Job& j : x.jobs) {
			j.taskIterator = j.tasks.begin();
		}
		//x.jobs.at(0).taskIterator = x.jobs.at(0).tasks.begin();
		std::cout << x.jobs.at(0).taskIterator->getId() << "TRACTOR" << std::endl;
		while (!x.everyTaskPlanned()) {
			for (Job &j : x.jobs) {
				i++;
				if (!j.isDone()) {//Check of de job niet klaar is. Anders gaat hij buiten de vector....

					//Task &currentTask = j.tasks.at(j.taskIterator->getId()); //Een reference naar de taak die we willen inplannen.
//					if(currentTask.getDuration() == 0) {
//											j.taskIterator++;
//											if(!j.startTimeIsSet()) {
//												j.setStartTime(timeT);
//											}
//										}
					std::cout << "TESTJE TASK ITERATOR:" << j.taskIterator->getId() << std::endl;
					std::cout << "TESTJE TASK ITERATOR:" << j.taskIterator->getMachineNr() << std::endl;

					Machine &currentMachine = machines.at(
							j.taskIterator->getMachineNr()); //Een reference naar de machine die we willen inplannen.
					std::cout << "HIER KOM IK VERMOEDELIJKE NIET" << std::endl;

					//euhm... dit werkt niet.. want taakIDs zijn niet per job maar over alle taken.
					//gaat dus fout op tasks.at(i)
					bool tasksBeforeSelectedDone = true;
//					int selectedID = j.taskIterator->getId(); //begint te tellen bij 0
//
//					for(Task& t : j.tasks) {
//						if(j.taskIterator->getId() >= selectedID) {
//							tasksBeforeSelectedDone = true;
//						}
//					}
					//if first task, always done
//					if(j.taskIterator->getId() == j.tasks.at(0).getId()) {
//						tasksBeforeSelectedDone = true;
//					}
					std::cout << tasksBeforeSelectedDone << "WAT?" << std::endl;
					//tasksBeforeSelectedDone = true;
					if (j.taskIterator->isSchedulable() && tasksBeforeSelectedDone) {
						//if duration is 0 skip picking task and just ignore task.
//						std::cout << "I Come Here 0" << std::endl;
//						std::cout << "CurrentTAsk Duration: " << currentTask.getDuration() << std::endl;
//						std::cout << "CurrentMachine " << currentMachine.id << "  TimeBusy: " << currentMachine.getTimeBusy() << std::endl;

						if(j.taskIterator->getDuration() == 0 && currentMachine.getTimeBusy() != 0) {
						//	std::cout << "I Come Here 1" << std::endl;
							std::cout << "Ik kom hier i: " << i <<std::endl;
							j.taskIterator->setIfSchedulable(false);

//							unsigned long oldTaskIt = j.taskIterator->getId();
//							for(Task& t : j.tasks) {
//								if(t.getId() - 1 == oldTaskIt) {
//									j.taskIterator = &t;
//								}
//							}
							j.taskIterator += 1;

							if(!j.startTimeIsSet()) {
								j.setStartTime(timeT);
							}
						}
						if (currentMachine.getTimeBusy() == 0 && j.taskIterator->getDuration() != 0) {//Kijk of de machine vrij is.

							currentMachine.setTimeBusy(j.taskIterator->getDuration());
							currentMachine.currentRunningTask = &*j.taskIterator;
						//	std::cout << "I Come Here 2" << std::endl;

							j.taskIterator->setIfSchedulable(false);//De taak is nu ingepland en kan verder genegeerd worden.
//							unsigned long oldTaskIt = j.taskIterator->getId();
//							for(Task& t : j.tasks) {
//								if(t.getId() - 1 == oldTaskIt) {
//									j.taskIterator = &t;
//								}
//							}
							j.taskIterator += 1;//Voor deze job kan de volgende ronde een andere taak ingepland worden.
							std::cout << "SCHEDULED TASK NR: "
									<< j.taskIterator->getId() << " FROM JOB " << j.id << " TO MACHINE NR: "
									<< currentMachine.id << std::endl;

							if(!j.startTimeIsSet()) {
								j.setStartTime(timeT);
							}
							j.setStopTime(j.taskIterator->getDuration()+timeT);
						}
					}
				}
				else {
					std::cout << "Job is Done" << std::endl;
				}
			}
			//Verkrijg de kortste tijd die een machine nog te draaien heeft.
			unsigned long shortestTaskDuration = machines.at(0).getTimeBusy(); //Houdt bij hoelang de kortste ingeplande taak duurt.
			shortestTaskDuration = 0;
			for (Machine m : machines) {
				std::cout << "this machine is machine " << m.id << " and busy for " <<  m.getTimeBusy() << std::endl;
				if ((shortestTaskDuration > m.getTimeBusy() && m.getTimeBusy() != 0) || (shortestTaskDuration == 0 && m.getTimeBusy() != 0)) {
					shortestTaskDuration = m.getTimeBusy();
				}
			}

			std::cout << "machine shortest busy: " << shortestTaskDuration << std::endl;

			//Update de tijd die de machines nog bezig zijn met de tijd van de machine die het kortst bezig is.
			std::for_each(machines.begin(), machines.end(),
					[shortestTaskDuration](Machine &m) {
						if (m.getTimeBusy() >= shortestTaskDuration) {
							m.setTimeBusy(
									m.getTimeBusy() - shortestTaskDuration);
						}
					});
			//Update de slack van elke Job.
//			std::for_each(x.jobs.begin(), x.jobs.end(),
//					[shortestTaskDuration](Job &job) {
//						if (job.slack >= shortestTaskDuration) {
//							job.slack -= shortestTaskDuration;
//						}
//					});
			//Update de slack van elke Job.
			for (Job &j : x.jobs) {
				j.calcSlack(longest_job);
			}

			//Sorteer opnieuw de Jobs op slack.
			std::sort(x.jobs.begin(), x.jobs.end()); //Gebruikt operator<() die op slack controleert.

			//shortest task duratoin is 0?
//			if(shortestTaskDuration == 1) {
//				shortestTaskDuration = 100;
//			}
			std::cout << "MOVED " << shortestTaskDuration
					<< " TIME-UNITS INTO THE FUTURE" << std::endl;
			timeT += shortestTaskDuration;

		}

		//sort on job id
		sort(x.jobs.begin(), x.jobs.end(),
		    [](const Job & a, const Job & b)
		{
		    return a.id < b.id;
		});

		std::cout << "----------OUTPUT-------------" << std::endl;
		for(Job &j : x.jobs) {
			std::cout << j.id << " " << j.startTime << " " << (j.getDuration()+j.startTime) << std::endl;
		}
		std::cout << "end program" << std::endl;

	} else {
		std::cout << "No file provided" << '\n';
	}

	return 0;
}
