/*
 * Machine.cpp
 *
 *  Created on: Mar 9, 2023
 *      Author: finn
 */

#include "Machine.h"

Machine::Machine(unsigned long anId) : id(anId), currentJobId(99999999), busy(false){

}

unsigned long Machine::getCurrentJobId() const
{
	return currentJobId;
}

void Machine::setCurrentJobId(unsigned long currentJobId)
{
	this->currentJobId = currentJobId;
}

bool Machine::isBusy() const
{
	return busy;
}

void Machine::setBusy(bool busy)
{
	this->busy = busy;
}

Task* Machine::getCurrentTask(){
	return &this->currentTask;
}

void Machine::setCurrentTask(Task& t){
	this->currentTask = t;
}
