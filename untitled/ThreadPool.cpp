//
// Created by root on 24. 3. 14.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads)
:_numThreads(numThreads),_stopAll(false){
    _workerThreads.reserve(_numThreads);
    for(size_t i=0;i<_numThreads;i++){
        _workerThreads.emplace_back([this](){this->WorkerThread();});
    }
}

ThreadPool::~ThreadPool() {
    _stopAll=true;
    for (auto& t : _workerThreads) {
        t.join();
    }
}

void ThreadPool::WorkerThread() {
    while(true){
        std::unique_lock<std::mutex> lock(m);
        size_t size = _globalQueue.GetSize();
        if(size == 0)
            continue;

        std::shared_ptr<JobQueue> jobQueueRef = _globalQueue.Pop();
        jobQueueRef->Execute();

    }
}
