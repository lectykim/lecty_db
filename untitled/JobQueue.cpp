//
// Created by root on 24. 3. 14.
//

#include "JobQueue.h"

#include <utility>

void JobQueue::Push(std::shared_ptr<Job> jobRef) {
    _jobs.Push(std::move(jobRef));

}

void JobQueue::Execute() {

}
