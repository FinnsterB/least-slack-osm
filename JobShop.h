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
	virtual ~JobShop() = default;
	/**
	* schedule()
	* @brief schedules jobs and tasks currently available in JobShop
	*/
	void schedule();
	/**
	* done()
	* @brief returns true if every job is done, otherwise returns false.
	*/
	bool done();
	/**
	* sortById()
	* @brief sorts current jobs in jobshop on jobid's.
	*/
	void sortById();
	/**
	* getJobs()
	* @brief returns all jobs in jobshop.
	*/
	std::vector<Job> getJobs();
};

#endif /* JOBSHOP_H_ */
