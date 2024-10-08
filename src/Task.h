/*
 * Task.h
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#ifndef TASK_H_
#define TASK_H_

class Task {
private:
	unsigned long machine;
	unsigned long duration;
	bool scheduled;
	unsigned long jobNr;
public:
	Task() = delete;
	/**
	 * @brief constructs a task
	 * @return task
	 */
	Task(const unsigned long machine, const unsigned long duration, const unsigned long jobNr);
	/**
	 * @brief copyconstructs a task
	 * @return task
	 */
	Task(const Task& t);

	/*getters*/
	unsigned long getMachineNr() const;
	unsigned long getDuration() const;
	bool isScheduled() const;
	unsigned long getJobNr() const;

	/*setters*/
	void setScheduled();

	/*destructor*/
	virtual ~Task() = default;
};

#endif /* TASK_H_ */
