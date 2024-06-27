/*
 * Job.cpp
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#include "Job.h"
#include "Task.h"

Job::Job() {
	isStartTimeSet = false;
	runs_until = 0;
}

unsigned long Job::getDuration(){
	unsigned long duration = 0;
	for(Task& t : tasks) {
		duration += t.getDuration();
	}
	return duration;
}

bool Job::isDone(){
	unsigned long duration = this->getRemainingDuration();
	if(duration == 0) {
		return true;
	}
	return false;
}

void Job::runsUntil(unsigned long time) {
	this->runs_until = time;
}

bool Job::hasTaskRunning(unsigned long time){
	if(this->runs_until > time) {
		return true;
	}
	return false;
}

Task& Job::getSchedulableTask() {
	for(Task& t : this->tasks) {
		if(t.isScheduled() == false) {
			return t;
		}
	}
}

bool Job::allTasksPlanned(){
	for(Task& t : this->tasks) {
		if(t.isScheduled() == false) {
			return false;
		}
	}
	return true;
}

void Job::addTask(Task task) {
	this->tasks.push_back(task);
}

unsigned long Job::calcSlack(unsigned long currentTime, unsigned long maxFinishTime) {
    // Calculate the slack as the difference between the latest finish time and the current time plus remaining job duration
    this->slack = maxFinishTime - (currentTime + this->getRemainingDuration());
    return this->slack;
}

unsigned long Job::getRemainingDuration() {
    unsigned long remainingDuration = 0;
    for (Task& task : tasks) {
    	//if (!task.isDone()) {
    	if (!task.isScheduled()) {
            remainingDuration += task.getDuration();
        }
    }
    return remainingDuration;
}

unsigned long Job::getSlack() {
	return this->slack;
}

void Job::setStartTime(unsigned long startTime){
	this->startTime = startTime;
	this->isStartTimeSet = true;
}

bool Job::startTimeSet() {
	return this->isStartTimeSet;
}

unsigned long Job::getStartTime(){
	return this->startTime;
}

void Job::setStopTime(unsigned long stopTime) {
	this->stopTime = stopTime;
}

unsigned long Job::getStopTime() {
	return this->stopTime;
}

void Job::setId(unsigned long id) {
	this->id = id;
}

unsigned long Job::getId() {
	return id;
}

