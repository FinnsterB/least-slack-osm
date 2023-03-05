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

	for (unsigned long i = 0; i < jobCount; ++i) {
		int TaskId = 0;
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
				Task xTask = Task(machine, duration, TaskId, i);
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



//	`	check if jobshop is built properly
		for (Job &j : x.jobs) {
			for (Task &t : j.tasks) {
				std::cout << "Task " << t.getId() << " duration: "
						<< t.getDuration() << std::endl;
			}
		}

		//algorithm
		//1) find longest task (i guess longest job?)

		Job *longest_job = x.getLongestJob();

		// 2) slack bepalen
		for (Job &j : x.jobs) {
			j.calcSlack(longest_job);
		}

		//sorteer Jobs op slack
		std::sort(x.jobs.begin(), x.jobs.end());//Gebruikt operator<() die op slack controleert.

		unsigned long timeT = 0;
		int i = 0;
		for(Job& j : x.jobs) {
			j.taskIterator = j.tasks.begin();
		}
		while (!x.everyTaskPlanned()) {
			for (Job &j : x.jobs) {
				i++;
				if (j.isDone() == false) {//Check of de job niet klaar is. Anders gaat hij buiten de vector....
					std::cout << "machineNR: " << j.taskIterator->getMachineNr() << std::endl;
					Machine &currentMachine = machines.at(j.taskIterator->getMachineNr()); //Een reference naar de machine die we willen inplannen.

					if(j.taskIterator->isDone() == true) {
						if(j.taskIterator < j.tasks.end()-1){
							std::cout << "Increase Iterator" << i << std::endl;

						  j.taskIterator++;
						}
						//continue;
					}
				//	j.taskIterator++;

					//euhm... dit werkt niet.. want taakIDs zijn niet per job maar over alle taken.
					//gaat dus fout op tasks.at(i)
					bool tasksBeforeSelectedDone = true;
					int selectedID = j.taskIterator->getId(); //begint te tellen bij 0

					for(Task& t : j.tasks) {
						if(t.getId() < selectedID && t.isDone() == false) {
							tasksBeforeSelectedDone = false;
						}
					}
					//	if first task, always done
					if(selectedID == j.tasks.at(0).getId()) {
						tasksBeforeSelectedDone = true;
					}
					//std::cout << tasksBeforeSelectedDone << "WAT?" << std::endl;
					if (j.taskIterator->isSchedulable() && j.taskIterator->done == false) {
//						if(currentMachine.getTimeBusy() != 0) {
////							j.taskIterator->setIfSchedulable(false);
////
////							if(j.taskIterator < j.tasks.end()-1){
////								j.taskIterator++;
////							}
////							if(!j.startTimeIsSet()) {
////								j.setStartTime(timeT);
////							}
//						}
						if (currentMachine.getTimeBusy() == 0) {//Kijk of de machine vrij is.
							std::cout << "KOM HIER " << i <<std::endl;
							currentMachine.setTimeBusy(j.taskIterator->getDuration());
							currentMachine.current = &*j.taskIterator;

							j.taskIterator->setIfSchedulable(false);//De taak is nu ingepland en kan verder genegeerd worden.

							std::cout << "SCHEDULED TASK NR: "
									<< j.taskIterator->getId() << " FROM JOB " << j.id << " TO MACHINE NR: "
									<< currentMachine.id << std::endl;

							if(!j.startTimeIsSet()) {
								j.setStartTime(timeT);
							}

							j.stopTime = j.taskIterator->getDuration()+timeT;
							if(j.taskIterator < j.tasks.end()-1){
								//j.taskIterator++;
							}
						}else if(j.taskIterator->getDuration() == 0){
							if(!j.startTimeIsSet()) {
								j.setStartTime(timeT);
							}
							j.taskIterator->setIfSchedulable(false);
							if(j.taskIterator != j.tasks.end() - 1){
								//j.taskIterator++;//Voor deze job kan de volgende ronde een andere taak ingepland worden.
							}
						}

						j.addLastTaskToStopTime(j.taskIterator->getDuration());
					}
				}
				else {
					std::cout << "Job "<< j.id <<" is Done" << std::endl;
				}
			}
			//Verkrijg de kortste tijd die een machine nog te draaien heeft.
			unsigned long shortestTaskDuration = machines.at(0).getTimeBusy(); //Houdt bij hoelang de kortste ingeplande taak duurt.
			shortestTaskDuration = 0;
			for (Machine m : machines) {
				std::cout << "TIME-UNIT GETTER OPTION: " << m.getTimeBusy() << std::endl;
				if ((shortestTaskDuration > m.getTimeBusy() && m.getTimeBusy() != 0) || (shortestTaskDuration == 0 && m.getTimeBusy() != 0)) {
					shortestTaskDuration = m.getTimeBusy();
				}
			}

			//Update de tijd die de machines nog bezig zijn met de tijd van de machine die het kortst bezig is.
			std::for_each(machines.begin(), machines.end(),
					[shortestTaskDuration](Machine &m) {
						if (m.getTimeBusy() >= shortestTaskDuration) {
							m.setTimeBusy(
									m.getTimeBusy() - shortestTaskDuration);
						}
					});

			//check of taken klaar zijn en zet ze op done
			for(Machine& m : machines) {
				if(m.current != nullptr && m.getTimeBusy() == 0) {
					int taskID = m.current->getId();
					int jobID = m.current->getJobId();
					std::cout << "SET TASK " << m.current->getId() << "FROM JOB " << m.current->getJobId() << " DONE" <<std::endl;
					for(Job& j : x.jobs) {
						for(Task& t : j.tasks) {
							if(j.id == jobID && t.getId() == taskID) {
								t.done = true;
							}
						}
					}
					m.current = nullptr;
				}
			}


			std::for_each(x.jobs.begin(), x.jobs.end(),
					[shortestTaskDuration](Job &job) {
						if (job.slack >= shortestTaskDuration) {
							job.slack -= shortestTaskDuration;
						}
					});

			//Sorteer opnieuw de Jobs op slack.
			std::sort(x.jobs.begin(), x.jobs.end()); //Gebruikt operator<() die op slack controleert.

			//check if TASKS are DONE
			for(Job j : x.jobs) {
				for(Task t : j.tasks) {
					if(t.isDone() == false) {
						std::cout << "TASK " << t.getId() << " FROM JOB " << t.getJobId() << "IS NOT DONE" << std::endl;
					} else {
						std::cout << "TASK " << t.getId() << " FROM JOB " << t.getJobId() << "IS DONE" << std::endl;
					}
				}
			}
			//check is jobs are DONE
			for(Job j : x.jobs) {
				if(j.isDone()) {
					std::cout << "JOB " << j.id << " IS DONE" << std::endl;
				} else {
					std::cout << "JOB " << j.id << " IS NOT DONE" << std::endl;
				}
			}

			//shortest task duratoin is 0?
			if(shortestTaskDuration == 0) {
				shortestTaskDuration = 1;
			}

			std::cout << "MOVED " << shortestTaskDuration
					<< " TIME-UNITS INTO THE FUTURE" << std::endl;
			timeT += shortestTaskDuration;


			std::for_each(x.jobs.begin(), x.jobs.end(), [shortestTaskDuration](Job& j){
				if(!j.isDone()){
					j.stopTime += shortestTaskDuration;
				}
			});

		}

		//sort on job id
		sort(x.jobs.begin(), x.jobs.end(),
		    [](const Job & a, const Job & b)
		{
		    return a.id < b.id;
		});

		std::cout << "----------OUTPUT-------------" << std::endl;
		for(Job &j : x.jobs) {
			std::cout << j.id << " " << j.startTime << " " << j.stopTime << std::endl;
		}
		std::cout << "end program" << std::endl;

	} else {
		std::cout << "No file provided" << '\n';
	}

	return 0;
}
