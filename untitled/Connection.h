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
#include <arpa/inet.h>
#include <sys/socket.h>
#include <memory>
#include <netinet/ip.h>
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
    Connection(int fd,sockaddr_in address):_fd(fd), _address(address){

        _recvBuffer = new RecvBuffer(K_MAX_BUF);
        _sendBuffer = new SendBuffer(K_MAX_BUF);
        _state = STATE_REQ;
    }
    ~Connection() = default;
    void Clear();
    int GetFd () const{return _fd;}
    std::string GetAddress(){
        char addr[100];
        inet_ntop(AF_INET,(struct sockaddr_in*)&_address.sin_addr,addr,sizeof(addr));
        return addr;
    }
    uint32_t OnRecv(char* buffer,int len);
    RecvBuffer* GetRecvBuffer(){return _recvBuffer;}
    SendBuffer* GetSendBuffer(){return _sendBuffer;}
private:
    int _fd=-1;
    uint32_t _state=0; //either STATE_REQ or STATE_RES
    RecvBuffer* _recvBuffer;
    SendBuffer* _sendBuffer;
    sockaddr_in _address;

};

class ConnectionPool{
public:
    ConnectionPool() = default;

    void connPut(Connection* conn){

        _connections[conn->GetFd()] = conn;
    }

    Connection* getCon(int fd){
        return _connections[fd];
    }

    void connPush(int fd){
        Connection* conn = _connections[fd];
        delete conn;
        _connections[fd] = nullptr;
    }



    void Clear(){
        for(auto* conn : _connections){
            delete conn;
        }

    }

    std::vector<Connection*> _connections;
};
extern ConnectionPool* GConnectionPool;



#endif //UNTITLED_CONNECTION_H
