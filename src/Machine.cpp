/*
 * Machine.cpp
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#include "Machine.h"

unsigned long Machine::getBusyUntil() {
	return busyUntil;
}

void Machine::setBusyUntil(unsigned long time) {
	busyUntil = time;
}
