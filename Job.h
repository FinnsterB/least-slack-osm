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
  Job (std::vector<Task> a_Tasks, int id);
  unsigned long calcSlack(Job* longest_job);
  unsigned long getDuration();
  virtual
  ~Job ();
  std::vector<Task> tasks;
  unsigned long slack;
  unsigned long taskIterator;
  unsigned long startTime;
  unsigned long stopTime;
  bool startTimeSet = false;

  int id;

  void setStartTime(unsigned long time) {
	  this->startTime = time;
	  startTimeSet = true;
  }
  void setStopTime(unsigned long time) {
  	  this->stopTime = time;
  }

  bool isDone(){
	  if(this->taskIterator + 1 >= this->tasks.size()) {
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
