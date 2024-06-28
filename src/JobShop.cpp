/*
 * JobShop.cpp
 *
 *  Created on: 18 jun 2024
 *      Author: Surface Pro 8 i7
 */

#include "JobShop.h"
#include "Task.h"
#include "Job.h"

#include <iostream>
#include <climits>

void JobShop::addJob(Job j) {
	jobs.push_back(j);
}

Job& JobShop::getLongestJob() {
    unsigned long longestDuration = 0;
    Job* longestJob = nullptr;
    for(Job& j : jobs) {
        unsigned long duration = j.getDuration();
        if(duration > longestDuration) {
            longestDuration = duration;
            longestJob = &j; // Assign the address of j to longestJob
        }
    }
    return *longestJob; // Dereference longestJob to return a Job&
}

bool JobShop::everyTaskDone() {
	for(Job j : jobs) {
		for(Task t : j.tasks) {
			if(t.isScheduled() == false) {
				return false;
			}
		}
	}
	return true;
}

bool JobShop::schedule()
{
    // 1) Get job with longest duration
    Job longest_job = getLongestJob();

    // 2) Calculate slack for every job
    for (Job& j : jobs) {
        j.calcSlack(0, longest_job.getDuration());
    }
    // 3) Sort jobs on slack
    std::sort(jobs.begin(), jobs.end(), [](Job& job1, Job& job2) {
        return job1.getSlack() < job2.getSlack();
    });

    // 4) Plan tasks
    unsigned long time = 0;
    while (!everyTaskDone()) {
        // Loop over every job
        for (Job &j : jobs) {
            // Check if the job is not done
            if (j.isDone()) {
                continue;
            }

            // Get the task that we want to schedule
            std::optional<std::reference_wrapper<Task>> optionalTaskToPlan = j.getSchedulableTask();
            if(!optionalTaskToPlan.has_value()){
                std::cerr << "Critical error: No schedulable task found!" << std::endl;
                exit(1);
            }
            Task& taskToPlan = optionalTaskToPlan.value();
            // Get the machine on which the task should run
            Machine &currentMachine = machines.at(taskToPlan.getMachineNr());

            // Check if the task can be scheduled
            bool machineFree = currentMachine.getBusyUntil() <= time;
            bool taskNotScheduledYet = !taskToPlan.isScheduled();
            bool jobHasTaskRunning = j.hasTaskRunning(time);
            if (machineFree && taskNotScheduledYet && jobHasTaskRunning == false) {
                // Set machine busy for the duration of the task
                currentMachine.setBusyUntil(time + taskToPlan.getDuration());
                j.runsUntil(time + taskToPlan.getDuration());

                // Set start time of the job if not already set
                if (!j.startTimeSet()) {
                    j.setStartTime(time);
                }

                // Task can now no longer be scheduled
                taskToPlan.setScheduled();

                // Set stop time of job (current time + duration of the task)
                j.setStopTime(time + taskToPlan.getDuration());
            }
        }

        // Get the shortest time a machine is still busy (which machine is free the soonest?)
        unsigned long shortestMachineDuration = ULONG_MAX;
        for (Machine& m : machines) {
            if (m.getBusyUntil() > time) {
                unsigned long busyTime = m.getBusyUntil() - time;
                if (busyTime < shortestMachineDuration) {
                    shortestMachineDuration = busyTime;
                }
            }
        }

        // Update slack of each job
        // 2) Calculate slack for every job
        for (Job& j : jobs) {
            j.calcSlack(0, longest_job.getRemainingDuration());
        }
        // Sort again by slack
        std::sort(jobs.begin(), jobs.end(), [](Job& job1, Job& job2) {
            if(job1.getSlack() < job2.getSlack()) {
            	return true;
            }
            if(job1.getSlack() == job2.getSlack()) {
            	return job1.getId() < job2.getId();
            }
            return false;
        });




        // Update current time with the new shortest time
        time += shortestMachineDuration;

    }
    return false;
}
