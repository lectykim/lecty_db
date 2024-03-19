//
// Created by root on 24. 3. 14.
//

#ifndef UNTITLED_PACKETQUEUE_H
#define UNTITLED_PACKETQUEUE_H
#include "LockQueue.h"
#include "Connection.h"
#include <atomic>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <iostream>

struct PacketItem{
    Connection* conn;
    const char* buffer;
    uint32_t code;
    int len;
    void Execute() const{

        // TODO: CODE값에 따른 데이터 수정

        if(send(conn->GetFd(), reinterpret_cast<const void *>(buffer), len, 0) == -1){
            std::cout << "client send error" << std::endl;
        }
    }
};
class PacketQueue{

public:
    PacketQueue()=default;
    void Execute();

    size_t GetSize() {return _jobs.Size();}

    void Push(const PacketItem& packetItem);

protected:
    LockQueue<std::shared_ptr<PacketItem>> _jobs;
    std::atomic<int32_t> _jobCount=0;
};

#endif //UNTITLED_PACKETQUEUE_H
