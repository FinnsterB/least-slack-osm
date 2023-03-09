/*
 * main.cpp
 *
 *  Created on: Mar 9, 2023
 *      Author: finn
 */
#include "JobShop.h"

#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>

//Functie maakt een JobShop klasse van een bestand.
JobShop makeJobShop(std::ifstream &file, std::vector<Machine> &machines) {
	JobShop jobshop;

	//Get amount of Jobs and Machines
	std::string token;
	std::getline(file, token, ' ');
	unsigned long jobCount = std::stoi(token);
	std::getline(file, token);
	unsigned long machineCount = std::stoi(token); // MachineCount = TaskCount

	//create machines
	//machineCount = 5;
	for (unsigned long i = 0; i < machineCount; ++i) {
		Machine m(i);
		jobshop.machines.push_back(m);
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
		jobshop.jobs.push_back(xjob);
	}
	return jobshop;
}

int main(int argc, char **argv) {
//	std::vector<std::pair<unsigned long, unsigned long>> input;
//	input = { { 0, 60 }, { 1, 15 }, { 2, 10 } };
//	std::vector<std::pair<unsigned long, unsigned long>> input1;
//	input1 = { { 0, 30 }, { 1, 30 }, { 2, 10 } };
//
//	JobShop j;
//	Job job1(0);
//	Job job2(1);
//	unsigned long machineId = 0;
//	for (auto pair : input) {
//		job1.tasks.push(Task(pair.first, pair.second));
//		j.machines.push_back(Machine(machineId));
//		job1.totalDurationOnStart += pair.second;
//		machineId++;
//	}
//	for (auto pair : input1) {
//		job2.tasks.push(Task(pair.first, pair.second));
//		job2.totalDurationOnStart += pair.second;
//	}
//	j.jobs.push_back(job1);
//	j.jobs.push_back(job2);
//	j.schedule();

	if (argc < 2) {
		std::cout << "No path provided" << '\n';
	}
	std::vector<Machine> machines;

	std::ifstream file;
	file.open(argv[argc - 1]);
	if (file.is_open()) {
		JobShop x = makeJobShop(file, machines);
		x.schedule();
		x.sortById();
		for(Job& j8: x.jobs){
			std::cout << j8.id << ' ' << j8.start << ' ' << j8.end << std::endl;
		}
	}

	return 0;
}

