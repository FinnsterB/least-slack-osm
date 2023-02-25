/*
 * Machine.cpp
 *
 *  Created on: 24 feb. 2023
 *      Author: marcv
 */

#include "Machine.h"

Machine::Machine(unsigned long id):id(id), timeBusy(0)
{
	// TODO Auto-generated constructor stub

}

Machine::~Machine()
{
	// TODO Auto-generated destructor stub
}

unsigned long
Machine::getTimeBusy () const
{
  return timeBusy;
}

void
Machine::setTimeBusy (unsigned long aTimeBusy)
{
  timeBusy = aTimeBusy;
}

bool Machine::operator <(const Machine &rhs) {
	return timeBusy < rhs.getTimeBusy();
}
