/*
 * Job.h
 *
 *  Created on: Feb 17, 2023
 *      Author: finn
 */

#ifndef JOB_H_
#define JOB_H_
#include "Task.h"
#include <iostream>
#include <vector>

class Job
{
public:
  Job (int id);
  Job (int id,std::vector<Task> a_Tasks);
  unsigned long calcSlack(Job* longest_job);
  unsigned long getDuration();
  virtual
  ~Job ();
  int id;
  std::vector<Task> tasks;
  unsigned long taskIterator;
  unsigned long startTime;
  unsigned long stopTime;
  unsigned long slack;
  bool startTimeSet = false;


  void setStartTime(unsigned long time) {
	  this->startTime = time;
	  startTimeSet = true;
  }
  void setStopTime(unsigned long time) {
  	  this->stopTime = time;
  }

  bool isDone(){
	  unsigned long tIt = this->taskIterator;
	  std::cout << "tIt: " << tIt << " tasks Size: " << this->tasks.size() << std::endl;
	  if(tIt >= this->tasks.size()) {
		  return true;
	  }
	  return false;
  }

  bool startTimeIsSet(){
	  return startTimeSet;
  }

  bool operator<(Job &j);
private:
};

#endif /* JOB_H_ */
