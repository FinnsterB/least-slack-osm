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

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "No path provided" << '\n';
	}
	std::vector<Machine> machines;

	std::ifstream file;
	file.open(argv[argc - 1]);
	if (file.is_open()) {
		JobShop x(file, machines);
		x.schedule();
		x.sortById();
		for(Job& job: x.getJobs()){
			std::cout << job.getId() << ' ' << job.getStart() << ' ' << job.getEnd() << std::endl;
		}
	}

	return 0;
}

