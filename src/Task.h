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
	unsigned long jobNr;
	bool scheduled;
public:
	Task() = delete;
	Task(unsigned long machine, unsigned long duration, unsigned long jobNr);

	unsigned long getMachineNr();
	unsigned long getDuration();
	bool isScheduled();
	void setScheduled();
	unsigned long getJobNr();
	virtual ~Task() = default;
};

#endif /* TASK_H_ */
