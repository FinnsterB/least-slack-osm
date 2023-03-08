/*
 * Machine.cpp
 *
 *  Created on: 24 feb. 2023
 *      Author: marcv
 */

#include "Machine.h"

Machine::Machine(unsigned long anId) :
		id(anId), currentTaskPointer(0), currentJob(0) {
	// TODO Auto-generated constructor stub

}

Machine::~Machine() {
	// TODO Auto-generated destructor stub
}

unsigned long Machine::getTimeBusy() const {
	if(currentTaskPointer != 0){
		return currentTaskPointer->getDuration();
	}
	return 0;
}

//Beweegt naar voren in de tijd.
void Machine::moveTime(unsigned long time) {
	if (currentTaskPointer != 0) {
		currentTaskPointer->setDuration(currentTaskPointer->getDuration() - time);
	}
}

bool Machine::isFree() {
	if(currentTaskPointer != 0){
		return currentTaskPointer->isDone();
	}
	return true;
}

//Stelt de tijd in.
void Machine::setTimeBusy(unsigned long time) {
	if (currentTaskPointer != 0) {
		currentTaskPointer->setDuration(time);
	}
}
