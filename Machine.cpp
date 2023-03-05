/*
 * Machine.cpp
 *
 *  Created on: 24 feb. 2023
 *      Author: marcv
 */

#include "Machine.h"

Machine::Machine(unsigned long anId) :
		id(anId), current(0) {
	// TODO Auto-generated constructor stub

}

Machine::~Machine() {
	// TODO Auto-generated destructor stub
}

unsigned long Machine::getTimeBusy() const {
	if(current != 0){
		return current->getDuration();
	}
	return 0;
}

//Beweegt naar voren in de tijd.
void Machine::moveTime(unsigned long time) {
	if (current != 0) {
		current->setDuration(current->getDuration() - time);
	}
}

bool Machine::isFree() {
	if(current != 0){
		return current->isDone();
	}
	return true;
}

//Stelt de tijd in.
void Machine::setTimeBusy(unsigned long time) {
	if (current != 0) {
		current->setDuration(time);
	}
}

void Machine::setCurrentTaskDone() {
	if(current != 0){
		current->setIfDone(true);
	}
}
