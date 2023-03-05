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

Task::Task (unsigned long a_machineNr, unsigned long a_duration, unsigned long a_id)
:machineNr(a_machineNr), duration(a_duration), id(a_id), schedulable(1), done(0)
{
  //std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

unsigned long Task::getDuration(){
	return duration;
}

unsigned long Task::getId(){
	return id;
}

bool
Task::isSchedulable ()
{
  return schedulable;
}

void
Task::setIfSchedulable (bool isSchedulable)
{
  schedulable = isSchedulable;
}

Task::~Task ()
{
  // TODO Auto-generated destructor stub
}

unsigned long Task::getMachineNr() const {
	return machineNr;
}

void Task::setMachineNr(unsigned long aMachineNr) {
	machineNr = aMachineNr;
}

bool Task::isDone() {
	return done;
}

void Task::setIfDone(bool aIsDone) {
	done = aIsDone;
}

void Task::setDuration(unsigned long time) {
	duration = time;
}
