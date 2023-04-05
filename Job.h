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
	unsigned long timeNotPossible;
	bool started;
	bool finished;
	unsigned long start;
	unsigned long end;
public:
	Job(unsigned long id);
	virtual ~Job();

	/**
	* getEnd()
	* @brief getter for endtime.
	*/
	unsigned long getEnd() const;
	/**
	* setEnd()
	* @brief setter for endtime.
	* @param a entime of current job
	*/
	void setEnd(unsigned long end);
	/**
	* isFinished()
	* @brief returns true if finished, returns false if job is still running or not started.
	*/
	bool isFinished() const;
	/**
	* setFinished()
	* @brief sets state of job
	* @param true if job is finished, false if not
	*/
	void setFinished(bool finished);
	/**
	* getId()
	* @brief returns id of job
	*/
	unsigned long getId() const;
	/**
	* getSlack()
	* @brief returns slack of job
	*/
	unsigned long getSlack() const;
	/**
	* setSlack()
	* @brief setter for slack of job
	* @param slack
	*/
	void setSlack(unsigned long slack);
	/**
	* getStart()
	* @brief returns starttime of job
	*/
	unsigned long getStart() const;
	/**
	* setStart()
	* @brief sets starttime of job
	* @param starttime to set.
	*/
	void setStart(unsigned long start);
	/**
	* isStarted()
	* @brief returns true if job is started, returns false if not
	*/
	bool isStarted() const;
	/**
	* setStarted()
	* @brief setter for startstatus
	* @param true if job is started, false if not
	*/
	void setStarted(bool started);
	/**
	* getTasks()
	* @brief returns all current Tasks
	*/
	std::queue<Task>& getTasks();
	/**
	* setTasks()
	* @brief fills job with tasks
	* @param ordered queue of tasks.
	*/
	void setTasks(const std::queue<Task> &tasks);
	/**
	* getTotalDurationOnStart()
	* @brief returns total duration of all tasks in job.
	*/
	unsigned long getTotalDurationOnStart() const;
	/**
	* setTotalDurationOnStart()
	* @brief sets totalDuration of all tasks in job.
	*/
	void setTotalDurationOnStart(unsigned long totalDurationOnStart);

	void setWantToStartTime(unsigned long time);
	void resetTimeNotPossible();
	void addDuration(unsigned long time);
	unsigned long getWantToStartTime();
};

#endif /* JOB_H_ */
