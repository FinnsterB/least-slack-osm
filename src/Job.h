/*
 * Job.h
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#ifndef JOB_H_
#define JOB_H_
#include <vector>
#include <optional>
#include <functional>
#include "Task.h"

class Job {
private:
	unsigned long startTime;
	unsigned long stopTime;
	bool isStartTimeSet;
	unsigned long id;
	unsigned long runsUntil;
	unsigned long slack;
	std::vector<Task> tasks;
public:
	bool hasTaskRunning(const unsigned long task)const;
	
	Job();
	Job(const Job& j);
	void addTask(const Task& task);
	std::vector<Task>& getTasks();

	unsigned long calcSlack(const unsigned long currentTime, const unsigned long maxFinishTime);
	void setRunsUntil(const unsigned long time);

	unsigned long getRemainingDuration();
	unsigned long getDuration();
	unsigned long getSlack() const;
	std::optional<std::reference_wrapper<Task>>  getSchedulableTask();
	bool isDone();
	bool startTimeSet() const;
	void setStartTime(const unsigned long starttime);
	unsigned long getStartTime() const;
	void setStopTime(const unsigned long stoptime);
	unsigned long getStopTime() const;
	bool allTasksPlanned();
	void setId(const unsigned long id);
	unsigned long getId() const;
	virtual ~Job() = default;
	void updateSlack(const unsigned long duration);
};

#endif /* JOB_H_ */
