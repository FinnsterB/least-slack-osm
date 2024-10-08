/*
 * JobShop.h
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#ifndef JOBSHOP_H_
#define JOBSHOP_H_
#include <vector>
#include <optional>
#include "Machine.h"
#include "Task.h"
#include "Job.h"
class JobShop {
public:
	std::vector<Job> jobs;
	std::vector<Machine> machines;

	void addJob(const Job& j);
	/**
	 * @brief Return std::optional to longest job.
	 * May return empty if the jobs vector is empty.
	 */
	std::optional<Job> getLongestJob();
	bool everyTaskDone();
	bool run(const unsigned long amountOfMachines);
	bool schedule();
	JobShop() = default;
	virtual ~JobShop() = default;
};

#endif /* JOBSHOP_H_ */
