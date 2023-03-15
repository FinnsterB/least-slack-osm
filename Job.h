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
private:
	std::queue<Task> tasks;
	unsigned long id;
	unsigned long slack;
	unsigned long totalDurationOnStart;
	bool started;
	bool finished;
	unsigned long start;
	unsigned long end;
public:
	Job(unsigned long id);
	virtual ~Job();

	unsigned long getEnd() const;
	void setEnd(unsigned long end);
	bool isFinished() const;
	void setFinished(bool finished);
	unsigned long getId() const;
	unsigned long getSlack() const;
	void setSlack(unsigned long slack);
	unsigned long getStart() const;
	void setStart(unsigned long start);
	bool isStarted() const;
	void setStarted(bool started);
	std::queue<Task>& getTasks();
	void setTasks(const std::queue<Task> &tasks);
	unsigned long getTotalDurationOnStart() const;
	void setTotalDurationOnStart(unsigned long totalDurationOnStart);
};

#endif /* JOB_H_ */
