/*
 * Machine.cpp
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#include "Machine.h"

Machine::Machine() {
	// TODO Auto-generated constructor stub

}

unsigned long Machine::getBusyUntil() {
	return this->busyUntil;
}

void Machine::setBusyUntil(unsigned long time) {
	this->busyUntil = time;
}
