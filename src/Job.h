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
	/**
	 * @brief checks if there are tasks running
	 * @return true if task is currently running, false if not
	 * @param1 timepoint to check if task is running
	 */
	bool hasTaskRunning(const unsigned long time)const;
	
	/**
	 * @brief constructs a job
	 * @return job
	 */
	Job();
	/**
	 * @brief copy constructs a job
	 * @param1 job
	 * @return job
	 */
	Job(const Job& j);

	/**
	 * @brief adds a task
	 * @param1 task to add
	 */
	void addTask(const Task& task);

	/**
	 * @brief returns all tasks
	 * @return vector of all tasks
	 */
	std::vector<Task>& getTasks();

	/**
	 * @brief calculates current slack of job
	 * @return slack
	 */
	unsigned long calcSlack(const unsigned long currentTime, const unsigned long maxFinishTime);
	/**
	 * @brief sets timepoint until job is running
	 */
	void setRunsUntil(const unsigned long time);

	/** getters */
	unsigned long getRemainingDuration();
	unsigned long getDuration();
	unsigned long getSlack() const;
	std::optional<std::reference_wrapper<Task>>  getSchedulableTask();
	bool isDone();
	bool startTimeSet() const;
	unsigned long getStartTime() const;
	bool allTasksPlanned();
	unsigned long getStopTime() const;
	unsigned long getId() const;

	/** setters */
	void setStartTime(const unsigned long starttime);
	void setStopTime(const unsigned long stoptime);
	void setId(const unsigned long id);

	/** destructor */
	virtual ~Job() = default;
};

#endif /* JOB_H_ */
