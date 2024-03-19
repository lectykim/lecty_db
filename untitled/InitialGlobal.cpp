//
// Created by root on 24. 3. 19.
//

#include "InitialGlobal.h"
PacketQueue* GPacketQueue;
ThreadPool* GThreadPool;
ConnectionPool* GConnectionPool;
EpollManager* GEpollManager;
const int MAX_THREAD_COUNT=16;

void InitialGlobal::Init() {
    GPacketQueue = new PacketQueue();
    GThreadPool = new ThreadPool(16);
    GConnectionPool = new ConnectionPool();
    GEpollManager = new EpollManager();
}
