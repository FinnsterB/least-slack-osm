/*
 * JobShop.h
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#ifndef JOBSHOP_H_
#define JOBSHOP_H_
#include <vector>
#include "Machine.h"
#include "Task.h"
#include "Job.h"
class JobShop {
public:
	std::vector<Job> jobs;
	std::vector<Machine> machines;

	void addJob(Job j);
	Job& getLongestJob();
	bool everyTaskDone();
	bool schedule();
	JobShop() = default;
	virtual ~JobShop() = default;
};

#endif /* JOBSHOP_H_ */
