/*
 * JobShop.h
 *
 *  Created on: Mar 9, 2023
 *      Author: finn
 */

#ifndef JOBSHOP_H_
#define JOBSHOP_H_
#include "Job.h"
#include "Machine.h"
#include <vector>

class JobShop {
public:
	JobShop();
	virtual ~JobShop();
	void schedule();
	bool done();
	void sortById();
	std::vector<Job> jobs;
	std::vector<Machine> machines;
};

#endif /* JOBSHOP_H_ */
