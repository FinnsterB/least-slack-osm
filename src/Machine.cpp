/*
 * Machine.cpp
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#include "Machine.h"

Machine::Machine(const Machine &m) : busyUntil(m.busyUntil)
{
}

unsigned long Machine::getBusyUntil() const
{
    return busyUntil;
}

void Machine::setBusyUntil(const unsigned long time) {
	busyUntil = time;
}
