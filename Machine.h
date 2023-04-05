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

	/**
	* getCurrentJobId()
	* @brief returns the job id of current running job on machine.
	*/
	unsigned long getCurrentJobId() const;
	/**
	* setCurrentJobId()
	* @brief sets current jobid of job currently running on machine
	*/
	void setCurrentJobId(unsigned long currentJobId);
	/**
	* isBusy()
	* @brief returns true if machine is running a job, returns false otherwise.
	*/
	bool isBusy() const;
	/**
	* setBusy()
	* @brief sets machine busy or not.
	* @param boolean true if machine is set to busy, false if machine is set to free
	*/
	void setBusy(bool busy);
	/**
	* getCurrentTask()
	* @brief returns current running task on machine.
	*/
	Task* getCurrentTask();
	/**
	* setCurrentTask()
	* @brief sets current running task to this machine.
	*/
	void setCurrentTask(Task& t);
};

#endif /* MACHINE_H_ */
