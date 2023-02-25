/*
 * JobShop.cpp
 *
 *  Created on: Feb 17, 2023
 *      Author: finn
 */

#include "JobShop.h"

JobShop::JobShop ()
{
  // TODO Auto-generated constructor stub
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

Job* JobShop::getLongestJob() {
	Job* longestJob = &jobs.at(0);
	for(Job& x : jobs) {
		if(x.getDuration() > longestJob->getDuration()) {
			longestJob = &x;
		}
	}
	return longestJob;
}

JobShop::~JobShop ()
{
  // TODO Auto-generated destructor stub
}

bool JobShop::everyTaskPlanned() {
	for(Job& j: jobs){
		if(j.taskIterator < j.tasks.size() - 1){
			return false;
		}
	}
	return true;
}
