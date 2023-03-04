/*
 * Machine.h
 *
 *  Created on: 24 feb. 2023
 *      Author: marcv
 */

#include "Task.h"

#ifndef MACHINE_H_
#define MACHINE_H_

class Machine
{
public:
	unsigned long id;
	unsigned long timeBusy;
	Task* currentRunningTask = nullptr;
	//bool available = true;
	Machine(unsigned long id);
	virtual ~Machine();
	bool operator<(const Machine& rhs);
	unsigned long
	getTimeBusy() const;
	void
	setTimeBusy(unsigned long timeBusy);
};

#endif /* MACHINE_H_ */
