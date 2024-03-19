//
// Created by root on 24. 3. 19.
//

#ifndef UNTITLED_INITIALGLOBAL_H
#define UNTITLED_INITIALGLOBAL_H
#include "PacketQueue.h"
#include "ThreadPool.h"
#include "EpollManager.h"
extern PacketQueue* GPacketQueue;
extern ThreadPool* GThreadPool;
extern ConnectionPool* GConnectionPool;
extern EpollManager* GEpollManager;
class InitialGlobal {
public:
    static void Init();
};


#endif //UNTITLED_INITIALGLOBAL_H
