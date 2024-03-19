//
// Created by root on 24. 3. 14.
//

#ifndef UNTITLED_THREADPOOL_H
#define UNTITLED_THREADPOOL_H
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <thread>
#include <mutex>
#include "PacketQueue.h"

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();
private:
    size_t _numThreads;
    std::vector<std::thread> _workerThreads;

    std::mutex m;

    bool _stopAll;

    void WorkerThread();

};


#endif //UNTITLED_THREADPOOL_H
