/*
 * Machine.h
 *
 *  Created on: 24 feb. 2023
 *      Author: marcv
 */

#ifndef MACHINE_H_
#define MACHINE_H_
#include "Task.h"

class Machine
{
public:
	unsigned long id;
	Task* current;
	Machine(unsigned long id);
	virtual ~Machine();
	void setCurrentTaskDone();
	unsigned long getTimeBusy();
	bool isFree();
	void moveTime(unsigned long time);
	void setTimeBusy(unsigned long time);
};

#endif /* MACHINE_H_ */
