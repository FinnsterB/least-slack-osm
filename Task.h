/*
 * Task.h
 *
 *  Created on: Mar 9, 2023
 *      Author: finn
 */

#ifndef TASK_H_
#define TASK_H_

class Task {
public:
	Task();
	Task(unsigned long machineNumber, unsigned long duration);
	virtual ~Task();
	unsigned long machineNumber;
	unsigned long duration;
};

#endif /* TASK_H_ */
