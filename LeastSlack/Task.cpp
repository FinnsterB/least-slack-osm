/*
 * Task.cpp
 *
 *  Created on: Feb 17, 2023
 *      Author: finn
 */

#include "Task.h"

Task::Task ()
{
  // TODO Auto-generated constructor stub

}

Task::Task (unsigned long a_machineNr, unsigned long a_duration, unsigned long a_id):machineNr(a_machineNr), duration(a_duration), id(a_id)
{
  // TODO Auto-generated constructor stub
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

Task::~Task ()
{
  // TODO Auto-generated destructor stub
}
