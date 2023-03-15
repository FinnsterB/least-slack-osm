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
	Task(unsigned long machineNumber = 0, unsigned long duration = 0);
	virtual ~Task() = default;
	unsigned long machineNumber;
	unsigned long duration;
};

#endif /* TASK_H_ */
