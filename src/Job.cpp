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
	unsigned long duration = getRemainingDuration();
	if(duration == 0) {
		return true;
	}
	return false;
}

void Job::runsUntil(unsigned long time) {
	runs_until = time;
}

bool Job::hasTaskRunning(unsigned long time){
	if(runs_until > time) {
		return true;
	}
	return false;
}

std::optional<std::reference_wrapper<Task>> Job::getSchedulableTask() {
	std::optional<std::reference_wrapper<Task>> foundTask;
	for(Task& t : tasks) {
		if(t.isScheduled() == false) {
			foundTask.emplace(std::reference_wrapper<Task>(t));
			return foundTask;
		}
	}
	return foundTask;
}

bool Job::allTasksPlanned(){
	for(Task& t : tasks) {
		if(t.isScheduled() == false) {
			return false;
		}
	}
	return true;
}

void Job::addTask(Task task) {
	tasks.push_back(task);
}

unsigned long Job::calcSlack(unsigned long currentTime, unsigned long maxFinishTime) {
    // Calculate the slack as the difference between the latest finish time and the current time plus remaining job duration
    slack = maxFinishTime - (currentTime + getRemainingDuration());
    return slack;
}

unsigned long Job::getRemainingDuration() {
    unsigned long remainingDuration = 0;
    for (Task& task : tasks) {
    	if (!task.isScheduled()) {
            remainingDuration += task.getDuration();
        }
    }
    return remainingDuration;
}

unsigned long Job::getSlack() {
	return slack;
}

void Job::setStartTime(unsigned long aStartTime){
	startTime = aStartTime;
	isStartTimeSet = true;
}

bool Job::startTimeSet() {
	return isStartTimeSet;
}

unsigned long Job::getStartTime(){
	return startTime;
}

void Job::setStopTime(unsigned long aStopTime) {
	stopTime = aStopTime;
}

unsigned long Job::getStopTime() {
	return stopTime;
}

void Job::setId(unsigned long aId) {
	id = aId;
}

unsigned long Job::getId() {
	return id;
}

