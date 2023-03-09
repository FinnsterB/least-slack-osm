/*
 * Job.h
 *
 *  Created on: Mar 9, 2023
 *      Author: finn
 */

#ifndef JOB_H_
#define JOB_H_
#include "Task.h"
#include <queue>

class Job {
public:
	Job(unsigned long id);
	virtual ~Job();
	std::queue<Task> tasks;
	unsigned long id;
	unsigned long slack;
	unsigned long totalDurationOnStart;
	bool started;
	bool finished;
	unsigned long start;
	unsigned long end;
};

#endif /* JOB_H_ */
