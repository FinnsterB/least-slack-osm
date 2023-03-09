/*
 * Machine.h
 *
 *  Created on: Mar 9, 2023
 *      Author: finn
 */

#ifndef MACHINE_H_
#define MACHINE_H_
#include "Task.h"

class Machine {
public:
	Machine(unsigned long anId);
	virtual ~Machine();
	unsigned long id;
	Task currentTask;
	unsigned long currentJobId;
	bool busy;
};

#endif /* MACHINE_H_ */
