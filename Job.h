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

	unsigned long getEnd() const
	{
		return end;
	}

	void setEnd(unsigned long end)
	{
		this->end = end;
	}

	bool isFinished() const
	{
		return finished;
	}

	void setFinished(bool finished)
	{
		this->finished = finished;
	}

	unsigned long getId() const
	{
		return id;
	}

	void setId(unsigned long id)
	{
		this->id = id;
	}

	unsigned long getSlack() const
	{
		return slack;
	}

	void setSlack(unsigned long slack)
	{
		this->slack = slack;
	}

	unsigned long getStart() const
	{
		return start;
	}

	void setStart(unsigned long start)
	{
		this->start = start;
	}

	bool isStarted() const
	{
		return started;
	}

	void setStarted(bool started)
	{
		this->started = started;
	}

	std::queue<Task>& getTasks()
	{
		return tasks;
	}

	void setTasks(const std::queue<Task> &tasks)
	{
		this->tasks = tasks;
	}

	unsigned long getTotalDurationOnStart() const
	{
		return totalDurationOnStart;
	}

	void setTotalDurationOnStart(unsigned long totalDurationOnStart)
	{
		this->totalDurationOnStart = totalDurationOnStart;
	}
};

#endif /* JOB_H_ */
