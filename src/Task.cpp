/*
 * Task.cpp
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#include "Task.h"

Task::Task(unsigned long machine, unsigned long duration, unsigned long jobNr):machine(machine),duration(duration),scheduled(false),jobNr(jobNr){

}

unsigned long Task::getMachineNr() {
	return machine;
}

void Task::setScheduled() {
	scheduled = true;
}

unsigned long Task::getDuration() {
	return duration;
}

bool Task::isScheduled(){
	return scheduled;
}

unsigned long Task::getJobNr(){
	return jobNr;
}
