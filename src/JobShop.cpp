/*
 * JobShop.cpp
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#include "JobShop.h"
#include "Task.h"
#include "Job.h"

void JobShop::addJob(Job j) {
	this->jobs.push_back(j);
}

Job& JobShop::getLongestJob() {
    unsigned long longestDuration = 0;
    Job* longestJob = nullptr;
    for(Job& j : this->jobs) {
        unsigned long duration = j.getDuration();
        if(duration > longestDuration) {
            longestDuration = duration;
            longestJob = &j; // Assign the address of j to longestJob
        }
    }
    return *longestJob; // Dereference longestJob to return a Job&
}

bool JobShop::everyTaskDone() {
	for(Job j : this->jobs) {
		for(Task t : j.tasks) {
			if(t.isScheduled() == false) {
				return false;
			}
		}
	}
	return true;
}
