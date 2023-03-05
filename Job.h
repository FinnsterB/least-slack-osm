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
  Job (unsigned long id);
  Job (unsigned long id,std::vector<Task> a_Tasks);
  unsigned long calcSlack(Job* longest_job);
  unsigned long getDuration();
  virtual
  ~Job ();
  unsigned long id;
  std::vector<Task> tasks;
  unsigned long taskIterator;
  unsigned long startTime;
  unsigned long stopTime;
  unsigned long slack;

/*
 * Only sets startTime when the first task is being planned. Use BEFORE taskIterator is incremented.
 */
  void setStartTime(unsigned long time) {
	  if(taskIterator == 0){
		  this->startTime = time;
	  }
  }

  /*
   * Only sets stopTime after the last task is planned. Use AFTER taskIterator is incremented.
   */
  void addLastTaskToStopTime(unsigned long time) {
	  if(isDone()){
		  this->stopTime += time;
	  }
  }

  bool isDone(){
	  if(taskIterator >= this->tasks.size()) {
		  return true;
	  }
	  return false;
  }

  bool previousTaskDone();
  bool operator<(Job &j);
private:
};

#endif /* JOB_H_ */
