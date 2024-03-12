//
// Created by root on 24. 3. 12.
//

#ifndef UNTITLED_CONNECTION_H
#define UNTITLED_CONNECTION_H
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <vector>
#include "RecvBuffer.h"
#include "SendBuffer.h"
#include <mutex>
enum {
    K_MAX_BUF=4096,
    MAX_CONNECTION_COUNT=4096,
};
enum {
    STATE_REQ = 0,
    STATE_RES = 1,
    STATE_END = 2,  // mark the connection for deletion
};
class Connection {
public:
    Connection(int fd):_fd(fd){

        _recvBuffer = new RecvBuffer(K_MAX_BUF);
        _sendBuffer = new SendBuffer(K_MAX_BUF);
        _state = STATE_REQ;
    }
    ~Connection() = default;
private:
    int _fd=-1;
    uint32_t _state=0; //either STATE_REQ or STATE_RES
    RecvBuffer* _recvBuffer;
    SendBuffer* _sendBuffer;


};

class ConnectionPool{
public:
    ConnectionPool() = default;

    static void connPut(int fd){
        auto* conn = new Connection(fd);
        _connections[fd] = conn;
    }

    static void Clear(){
        for(auto* conn : _connections){
            delete conn;
        }

    }

    static std::vector<Connection*> _connections;
};




#endif //UNTITLED_CONNECTION_H
