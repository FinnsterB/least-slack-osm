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
	return this->machine;
}

void Task::setScheduled() {
	this->scheduled = true;
}

unsigned long Task::getDuration() {
	return this->duration;
}

bool Task::isScheduled(){
	return this->scheduled;
}

unsigned long Task::getJobNr(){
	return this->jobNr;
}
