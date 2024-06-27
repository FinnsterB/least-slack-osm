/*
 * JobShop.h
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#ifndef JOBSHOP_H_
#define JOBSHOP_H_
#include <vector>
#include "Task.h"
#include "Job.h"
class JobShop {
public:
	std::vector<Job> jobs;

	void addJob(Job j);
	Job& getLongestJob();
	bool everyTaskDone();
	JobShop() = default;
	virtual ~JobShop() = default;
};

#endif /* JOBSHOP_H_ */
