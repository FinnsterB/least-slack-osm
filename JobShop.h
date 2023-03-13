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
#include <fstream>

class JobShop {
private:
	std::vector<Job> jobs;
	std::vector<Machine> machines;
public:
	JobShop(std::ifstream &file, std::vector<Machine> &machines);
	virtual ~JobShop();
	void schedule();
	bool done();
	void sortById();

	std::vector<Job> getJobs();
};

#endif /* JOBSHOP_H_ */
