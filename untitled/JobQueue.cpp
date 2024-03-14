//
// Created by root on 24. 3. 14.
//

#include "JobQueue.h"

#include <utility>

void JobQueue::Push(std::shared_ptr<Job> jobRef) {
    _jobs.Push(std::move(jobRef));

}

void JobQueue::Execute() {
        std::vector<std::shared_ptr<Job>> jobs;
        _jobs.PopAll(jobs);
        for(auto &job:jobs){
            job->Execute();
        }
}
