//
// Created by root on 24. 3. 14.
//

#include "GlobalQueue.h"

#include <utility>

void GlobalQueue::Push(std::shared_ptr<JobQueue> jobqueue) {
    _jobQueues.Push(std::move(jobqueue));
}

std::shared_ptr<JobQueue> GlobalQueue::Pop() {
    return _jobQueues.Pop();
}
