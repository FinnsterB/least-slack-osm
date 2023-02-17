/*
 * main.cpp
 *
 *  Created on: Feb 17, 2023
 *      Author: finn
 */
#include "JobShop.h"
#include "Task.h"
#include "Job.h"
#include <fstream>
#include <vector>
#include <iostream>

//Function to make jobshop from file
JobShop makeJobShop(std::fstream& file){
  JobShop jobshop;

  //Get amount of Jobs and Machines
  std::string token;
  std::getline(file, token, ' ');
  unsigned long jobCount = std::stoi(token);
  std::getline(file, token, ' ');
  unsigned long machineCount = std::stoi(token); // MachineCount = TaskCount

  //Loop door
  for(unsigned long i = 0; i < jobCount; ++i){
      std::vector<Task> tasks;
      for(unsigned long j = 0; j < machineCount; ++j){
	  std::getline(file, token, ' ');
	  unsigned long machineNr = std::stoi(token);
	  std::getline(file, token, ' ');
	  unsigned long duration = std::stoi(token);
	  tasks.push_back(Task(machineNr, duration, j));
      }
      Job job(tasks);
      jobshop.jobs.push_back(job);
  }

  return jobshop;
}

int main(int argc, char **argv) {
  if(argc < 2){
        std::cout << "No path provided" << '\n';
    }

  std::ifstream file;
  file.open(argv[argc-1]);//TODO:anders

  if(!file){
      std::cout << "No file provided" << '\n';
  }

  return 0;
}




