/*
 * Job.cpp
 *
 *  Created on: Feb 17, 2023
 *      Author: finn
 */

#include "Job.h"

Job::Job (int id):id(id),taskIterator(0), startTime(0), stopTime(0), slack(0)
{

}

Job::Job (int id,std::vector<Task> a_Tasks):id(id), tasks(a_Tasks), taskIterator(0), startTime(0), stopTime(0), slack(0)
{
  std::cerr << __PRETTY_FUNCTION__ << std::endl;
}

unsigned long Job::getDuration() {
	unsigned long duration = 0;
	for(Task x : tasks) {
		duration += x.getDuration();
	}
	return duration;
}

Job::~Job ()
{
  // TODO Auto-generated destructor stub
}

unsigned long Job::calcSlack(Job* longest_job) {
	this->slack = longest_job->getDuration() - this->getDuration();
	return this->slack;
}

bool Job::operator<(Job &j) {
	if(this->slack < j.slack) {
		return true;
	}
	if(this->slack == j.slack) {
		if(this->id < j.id) {
			return true;
		}
	}
	return false;
}
