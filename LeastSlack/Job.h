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
  Job ();
  Job (std::vector<Task> a_Tasks);
  virtual
  ~Job ();
private:
  std::vector<Task> tasks;
};

#endif /* JOB_H_ */