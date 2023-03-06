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

//Functie maakt een JobShop klasse van een bestand.
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

//	`	check if jobshop is built properly
		for (Job &j : x.jobs) {
			for (Task &t : j.tasks) {
				std::cout << "Task " << t.getId() << " duration: "
						<< t.getDuration() << std::endl;
			}
		}




		//algoritme
		//1) Zoek de langste Job

		Job *longest_job = x.getLongestJob();

		// 2) slack bepalen
		for (Job &j : x.jobs) {
			j.calcSlack(longest_job);
		}

		//sorteer Jobs op slack
		std::sort(x.jobs.begin(), x.jobs.end());//Gebruikt operator<() die op slack controleert.

		unsigned long timeT = 0;//Variabele om de globale tijd in het systeem bij te houden.
		while (!x.everyTaskPlanned()) {
			for (Job &j : x.jobs) {
				if (!j.isDone()) {//Check of de job niet klaar is. Anders gaat hij buiten de vector....

					Task &currentTask = j.tasks.at(j.taskIterator); //Een reference naar de taak die we willen inplannen.
					Machine &currentMachine = machines.at(
							currentTask.getMachineNr()); //Een reference naar de machine die we willen inplannen.

					//Onderstaand wordt gecheckt of de taken schedulable zijn en of de voorgaande taak van een job klaar is.
					if (currentTask.isSchedulable() && j.previousTaskDone()) {
						if (currentMachine.isFree()) {//Kijk of de machine vrij is.
							currentMachine.setTimeBusy(
									currentTask.getDuration());
							j.setStartTime(timeT);
							currentTask.setIfSchedulable(false);//De taak is nu ingepland.
							j.taskIterator += 1;//Voor deze job kan de volgende ronde een andere taak ingepland worden.
							currentMachine.current = &currentTask;
							std::cout << "SCHEDULED TASK NR: "
									<< currentTask.getId() << " FROM JOB NR: "
									<< j.id << " TO MACHINE NR: "
									<< currentMachine.id << std::endl;
						}

						j.addLastTaskToStopTime(currentTask.getDuration());
					}
				}
			}
			//Verkrijg de kortste tijd die een machine nog te draaien heeft.
			unsigned long shortestTaskDuration = 0; //Houdt bij hoelang de kortste ingeplande taak duurt.
			shortestTaskDuration--; //Even een stomme manier om de hoogst mogelijke waarde te krijgen.
			unsigned long compShort = shortestTaskDuration; // Variabele om te kijken of shortestTaskDuration is veranderd.

			for (Machine &m : machines) {

				if(m.getTimeBusy() != 0){
					if(m.getTimeBusy() < shortestTaskDuration){
						shortestTaskDuration = m.getTimeBusy();
					}
				}
			}
			if(shortestTaskDuration == compShort){
				shortestTaskDuration  = 0;
			}
			//Update de tijd die de machines nog bezig zijn met de tijd van de machine die het kortst bezig is.
			for (Machine &m : machines) {
				if (m.getTimeBusy() >= shortestTaskDuration) {
					m.moveTime(shortestTaskDuration);
				}
				if (m.getTimeBusy() == 0) {
					m.setCurrentTaskDone();
				}
			}

			//Update de slack van elke Job.
			std::for_each(x.jobs.begin(), x.jobs.end(),
					[shortestTaskDuration](Job &job) {
						if (job.slack >= shortestTaskDuration) {
							job.slack -= shortestTaskDuration;
						}
					});

			//Sorteer opnieuw de Jobs op slack.
			std::sort(x.jobs.begin(), x.jobs.end()); //Gebruikt operator<() die op slack controleert.

			std::cout << "MOVED " << shortestTaskDuration
					<< " TIME-UNITS INTO THE FUTURE" << std::endl;
			timeT += shortestTaskDuration;

			std::for_each(x.jobs.begin(), x.jobs.end(),
					[shortestTaskDuration](Job &j) {
						if (!j.isDone()) {
							j.stopTime += shortestTaskDuration;
						}
					});

		}

		//sort on job id
		sort(x.jobs.begin(), x.jobs.end(),
				[](const Job &a, const Job &b) -> bool {
					return a.id < b.id;
				});

		std::cout << "----------OUTPUT-------------" << std::endl;
		for (Job &j : x.jobs) {
			std::cout << j.id << " " << j.startTime << " " << j.stopTime
					<< std::endl;
		}

	} else {
		std::cout << "No file provided" << '\n';
	}

	return 0;
}
