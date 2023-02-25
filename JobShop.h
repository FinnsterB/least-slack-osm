/*
 * JobShop.h
 *
 *  Created on: Feb 17, 2023
 *      Author: finn
 */

#ifndef JOBSHOP_H_
#define JOBSHOP_H_
#include "Job.h"
#include <iostream>
#include <vector>
class JobShop
{
public:
  std::vector<Job> jobs;
  JobShop ();
  Job* getLongestJob();
  bool everyTaskPlanned();
  virtual
  ~JobShop ();
};

#endif /* JOBSHOP_H_ */
