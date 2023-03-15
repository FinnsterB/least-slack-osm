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

unsigned long Job::getEnd() const
{
	return end;
}

void Job::setEnd(unsigned long end)
{
	this->end = end;
}

bool Job::isFinished() const
{
	return finished;
}

void Job::setFinished(bool finished)
{
	this->finished = finished;
}

unsigned long Job::getId() const
{
	return id;
}

unsigned long Job::getSlack() const
{
	return slack;
}

void Job::setSlack(unsigned long slack)
{
	this->slack = slack;
}

unsigned long Job::getStart() const
{
	return start;
}

void Job::setStart(unsigned long start)
{
	this->start = start;
}

bool Job::isStarted() const
{
	return started;
}

void Job::setStarted(bool started)
{
	this->started = started;
}

std::queue<Task>& Job::getTasks()
{
	return tasks;
}

void Job::setTasks(const std::queue<Task> &tasks)
{
	this->tasks = tasks;
}

unsigned long Job::getTotalDurationOnStart() const
{
	return totalDurationOnStart;
}

void Job::setTotalDurationOnStart(unsigned long totalDurationOnStart)
{
	this->totalDurationOnStart = totalDurationOnStart;
}
