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
private:
	unsigned long id;
	unsigned long currentJobId;
	bool busy;
public:
	Task currentTask;

	Machine(unsigned long anId);
	virtual ~Machine();

	unsigned long getCurrentJobId() const
	{
		return currentJobId;
	}

	void setCurrentJobId(unsigned long currentJobId)
	{
		this->currentJobId = currentJobId;
	}

	bool isBusy() const
	{
		return busy;
	}

	void setBusy(bool busy)
	{
		this->busy = busy;
	}
};

#endif /* MACHINE_H_ */
