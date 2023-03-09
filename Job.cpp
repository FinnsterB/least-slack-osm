/*
 * Job.cpp
 *
 *  Created on: Mar 9, 2023
 *      Author: finn
 */

#include "Job.h"

Job::Job(unsigned long anId):id(anId), slack(0), totalDurationOnStart(0), started(false), finished(false), start(0), end(0) {
	// TODO Auto-generated constructor stub
}

Job::~Job() {
	// TODO Auto-generated destructor stub
}

