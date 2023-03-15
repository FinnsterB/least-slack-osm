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
	Task currentTask;

public:
	Machine(unsigned long anId);
	virtual ~Machine() = default;

	unsigned long getCurrentJobId() const;
	void setCurrentJobId(unsigned long currentJobId);
	bool isBusy() const;
	void setBusy(bool busy);
	Task* getCurrentTask();
	void setCurrentTask(Task& t);
};

#endif /* MACHINE_H_ */
