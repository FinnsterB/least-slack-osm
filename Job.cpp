/*
 * Job.cpp
 *
 *  Created on: Feb 17, 2023
 *      Author: finn
 */

#include "Job.h"

Job::Job (int id):taskIterator(0),id(id), startTime(0), stopTime(0)
{

}

Job::Job (std::vector<Task> a_Tasks,int id): tasks(a_Tasks), taskIterator(0), id(id), startTime(0), stopTime(0)
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

	std::cout << "slack: " << this->slack << std::endl;

	return this->slack;
}

bool Job::operator<(Job &j) {
	if(this->slack < j.slack) {
		return true;
	}
	return false;
}
