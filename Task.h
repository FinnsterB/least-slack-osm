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
  Task (unsigned long a_machineNr, unsigned long a_duration, unsigned long a_id) ;
  unsigned long getId();
  unsigned long getDuration();

  virtual
  ~Task ();
private:
  unsigned long machineNr;
  unsigned long duration;
  unsigned long id;
};

#endif /* TASK_H_ */
