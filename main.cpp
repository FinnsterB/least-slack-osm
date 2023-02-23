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
#include <sstream>

//Function to make jobshop from file.
JobShop makeJobShop(std::ifstream& file){
  JobShop jobshop;

  //Get amount of Jobs and Machines
  std::string token;
  std::getline(file, token);
  unsigned long jobCount = std::stoi(token);
  std::cout << "jobCount:" << jobCount << std::endl;
  //std::getline(file, token, ' ');
  unsigned long machineCount = std::stoi(token); // MachineCount = TaskCount
  std::cout << "machineCount:" << machineCount << std::endl;

  //Loop door
  int TaskId = 0;
  for(unsigned long i = 0; i < jobCount; ++i){
      std::vector<Task> tasks;
      std::getline(file, token);
      std::cout << token << std::endl;
      std::vector<std::string> v;

      std::stringstream ss(token);

      std::string word;

      Job xjob = Job();

      int machine = 999;
      int duration = 999;
	  while (ss >> word) { // Extract word from the stream.
		  if(machine == 999) {
			  machine = std::stoi(word);
		  }
		  else {
			  duration = std::stoi(word);
			  std::cout << "job " << i << " machine: " << machine << " duration: " << duration << std::endl;
			  Task xTask = Task(machine,duration,TaskId);
			  TaskId++;
			  xjob.tasks.push_back(xTask);
			  machine = 999;
			  duration = 999;
		  }
	  }
	  jobshop.jobs.push_back(xjob);
	  std::cout << std::endl;
  }


  return jobshop;
}

int main(int argc, char **argv) {
  if(argc < 2){
	std::cout << "No path provided" << '\n';
  }

  std::ifstream file;
  file.open(argv[argc-1]);
  if(file.is_open()){
     std::cout << " file provided" << '\n';
     JobShop x = makeJobShop(file);

     //check if jobshop is build properly
     for(Job& j : x.jobs)  {
    	 for(Task& t : j.tasks) {
        	 std::cout << "Task " << t.getId() << " duration: " << j.tasks.at(0).getDuration() << std::endl;
    	 }
     }
     //algorithm
     //1) find longest task (i guess longest job?)

     Job* longest_job = x.getLongestJob();
     std::cout << "Duration of longest job: " << longest_job->getDuration();


  } else{
	  std::cout << "No file provided" << '\n';
  }







  return 0;
}




