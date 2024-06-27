#include <iostream>
#include <algorithm>
#include "JobShop.h"
#include "Machine.h"
#include "Job.h"
#include "Task.h"
#include "Parser.h"
using namespace std;

int main() {
    // Working with that input
    Parser p = Parser();
    std::string filename = "input.txt";
    JobShop js = p.parse(filename);

    std::vector<Machine> machines;
    std::cout << "Amount machines from parser: " << p.getAmountMachines() << std::endl;
    for (unsigned short i = 0; i < p.getAmountMachines(); i++) {
        machines.push_back(Machine());
    }

    // 1) Get job with longest duration
    Job longest_job = js.getLongestJob();
    std::cout << "Longest job duration: " << longest_job.getDuration() << std::endl;

    // 2) Calculate slack for every job
    for (Job& j : js.jobs) {
        j.calcSlack(0, longest_job.getDuration());
    }
    // 3) Sort jobs on slack
    std::sort(js.jobs.begin(), js.jobs.end(), [](Job& job1, Job& job2) {
        return job1.getSlack() < job2.getSlack();
    });

    // 4) Plan tasks
    unsigned long time = 0;
    while (!js.everyTaskDone()) {
        // Loop over every job
        for (Job &j : js.jobs) {
            // Check if the job is not done
            if (j.isDone()) {
                continue;
            }

            // Get the task that we want to schedule
            Task& taskToPlan = j.getSchedulableTask();

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
        for (Job& j : js.jobs) {
            j.calcSlack(0, longest_job.getRemainingDuration());
        }
        // Sort again by slack
        std::sort(js.jobs.begin(), js.jobs.end(), [](Job& job1, Job& job2) {
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

    // Output: sort on job id
    std::sort(js.jobs.begin(), js.jobs.end(), [](Job& a, Job& b) -> bool {
        return a.getId() < b.getId();
    });

    std::cout << "---------- OUTPUT -------------" << std::endl;
    for (Job &j : js.jobs) {
        std::cout << j.getId() << " " << j.getStartTime() << " " << (j.getStopTime()) << std::endl;
    }

    return 0;
}
