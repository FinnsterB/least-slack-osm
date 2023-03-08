/*
 * Machine.h
 *
 *  Created on: 24 feb. 2023
 *      Author: marcv
 */

#ifndef MACHINE_H_
#define MACHINE_H_
#include "Task.h"

struct TaskPos{
	unsigned long jobId;
	unsigned long taskId;
	bool accesible;
};

class Machine
{
public:
	unsigned long id;
	Task* currentTaskPointer;
	//TaskPos currentTask;
	unsigned long currentJob;
	Machine(unsigned long id);
	virtual ~Machine();
	void setPreviousTaskDone();
	unsigned long getTimeBusy() const;
	bool isFree();
	void moveTime(unsigned long time);
	void setTimeBusy(unsigned long time);
};

#endif /* MACHINE_H_ */
