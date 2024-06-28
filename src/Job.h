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
	unsigned long startTime;
	unsigned long stopTime;
	bool isStartTimeSet;
	unsigned long id;
	unsigned long runs_until;
public:
	unsigned long slack;
	bool hasTaskRunning(unsigned long task);
	std::vector<Task> tasks;
	Job();
	void addTask(Task task);
	unsigned long calcSlack(Job* longest_job);

	unsigned long calcSlack(unsigned long currentTime, unsigned long maxFinishTime);
	void runsUntil(unsigned long time);

	unsigned long getRemainingDuration();
	unsigned long getDuration();
	unsigned long getSlack();
	std::optional<std::reference_wrapper<Task>>  getSchedulableTask();
	bool isDone();
	bool startTimeSet();
	void setStartTime(unsigned long starttime);
	unsigned long getStartTime();
	void setStopTime(unsigned long stoptime);
	unsigned long getStopTime();
	bool allTasksPlanned();
	void setId(unsigned long id);
	unsigned long getId();
	virtual ~Job() = default;
	void updateSlack(unsigned long duration) {
	    this->slack -= duration;
	}
};

#endif /* JOB_H_ */
