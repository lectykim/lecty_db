//
// Created by root on 24. 3. 14.
//

#ifndef UNTITLED_GLOBALQUEUE_H
#define UNTITLED_GLOBALQUEUE_H
#include "JobQueue.h"

class GlobalQueue {
public:
    GlobalQueue()=default;
    ~GlobalQueue()=default;

    void Push(std::shared_ptr<JobQueue> jobqueue);
    std::shared_ptr<JobQueue> Pop();
    size_t GetSize(){return _jobQueues.Size();}

private:
    LockQueue<std::shared_ptr<JobQueue>> _jobQueues;
};


#endif //UNTITLED_GLOBALQUEUE_H
