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
	runsUntil = 0;
}

Job::Job(const Job &j) : startTime(j.startTime), stopTime(j.stopTime), isStartTimeSet(j.isStartTimeSet), 
					id(j.id), runsUntil(j.runsUntil), slack(j.slack), tasks(j.tasks)
{
}

unsigned long Job::getDuration() {
	unsigned long duration = 0;
	for(Task& t : tasks) {
		duration += t.getDuration();
	}
	return duration;
}

bool Job::isDone() {
	unsigned long duration = getRemainingDuration();
	if(duration == 0) {
		return true;
	}
	return false;
}

void Job::setRunsUntil(const unsigned long time) {
	runsUntil = time;
}

bool Job::hasTaskRunning(const unsigned long time) const{
	if(runsUntil > time) {
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

void Job::addTask(const Task& task) {
	tasks.push_back(task);
}

std::vector<Task> &Job::getTasks()
{
    return tasks;
}

unsigned long Job::calcSlack(const unsigned long currentTime, const unsigned long maxFinishTime) {
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

unsigned long Job::getSlack() const{
	return slack;
}

void Job::setStartTime(const unsigned long aStartTime){
	startTime = aStartTime;
	isStartTimeSet = true;
}

bool Job::startTimeSet() const{
	return isStartTimeSet;
}

unsigned long Job::getStartTime() const{
	return startTime;
}

void Job::setStopTime(const unsigned long aStopTime) {
	stopTime = aStopTime;
}

unsigned long Job::getStopTime() const{
	return stopTime;
}

void Job::setId(const unsigned long aId) {
	id = aId;
}

unsigned long Job::getId() const {
	return id;
}

