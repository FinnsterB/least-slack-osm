/*
 * Job.cpp
 *
 *  Created on: Feb 17, 2023
 *      Author: finn
 */

#include "Job.h"

Job::Job ()
{
  // TODO Auto-generated constructor stub

}

Job::Job (std::vector<Task> a_Tasks): tasks(a_Tasks)
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;

}

Job::~Job ()
{
  // TODO Auto-generated destructor stub
}
