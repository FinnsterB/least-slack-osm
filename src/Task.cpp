/*
 * Task.cpp
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#include "Task.h"

Task::Task(const unsigned long machine, const unsigned long duration, const unsigned long jobNr):
		machine(machine),duration(duration),scheduled(false),jobNr(jobNr){

}

Task::Task(const Task &t): machine(t.machine), duration(t.duration), scheduled(t.scheduled), jobNr(t.jobNr)
{
}

unsigned long Task::getMachineNr() const{
	return machine;
}

void Task::setScheduled() {
	scheduled = true;
}

unsigned long Task::getDuration() const{
	return duration;
}

bool Task::isScheduled() const{
	return scheduled;
}

unsigned long Task::getJobNr() const{
	return jobNr;
}
