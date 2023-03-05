/*
 * Task.h
 *
 *  Created on: Feb 17, 2023
 *      Author: finn
 */

#ifndef TASK_H_
#define TASK_H_
#include <iostream>

class Task
{
public:
  Task ();
  Task (unsigned long a_machineNr, unsigned long a_duration, unsigned long a_id, unsigned long job_id) ;
  unsigned long getId();
  unsigned long getJobId() {return this->JobId;}

  unsigned long getDuration();
  bool isDone();
  bool isSchedulable();
  void setIfDone(bool isDone);
  void setIfSchedulable(bool isSchedulable);

  virtual
  ~Task ();
	unsigned long getMachineNr() const;
	void setMachineNr(unsigned long machineNr);//TODO: Niet nodig.
	  bool done;

private:
  unsigned long machineNr;
  unsigned long duration;
  unsigned long id;
  unsigned long JobId;
  bool schedulable;
};

#endif /* TASK_H_ */
