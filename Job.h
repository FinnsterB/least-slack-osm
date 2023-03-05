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
  //unsigned long taskIterator;
  std::vector<Task>::iterator taskIterator;

  unsigned long startTime;
  unsigned long stopTime;
  unsigned long slack;
  bool startisset = false;

/*
 * Only sets startTime when the first task is being planned. Use BEFORE taskIterator is incremented.
 */
  void setStartTime(unsigned long time) {
	  if(taskIterator == tasks.begin()){
		  this->startTime = time;
	  }
	  this->startisset = true;
  }
  bool startTimeIsSet() {
	  return this->startisset;
  }
  /*
   * Only sets stopTime after the last task is planned. Use AFTER taskIterator is incremented.
   */
  void addLastTaskToStopTime(unsigned long time) {
	  if(this->isDone()){
		  this->stopTime += time;
	  }
  }

  bool isDone(){
	  bool done = true;
	  for(Task t : tasks) {
		  if(t.isDone() == false) {
			  done = false;
		  }
	  }
	  return done;
  }

  bool operator<(Job &j);
private:
};

#endif /* JOB_H_ */
