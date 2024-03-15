//
// Created by root on 24. 3. 12.
//

#include "Connection.h"
#include "Parser.h"
ConnectionPool* GConnectionPool = new ConnectionPool();
void Connection::Clear() {
    delete _recvBuffer;
    delete _sendBuffer;
}

uint32_t Connection::OnRecv(char* buffer,int len) {
    uint32_t resCode;
    GParser->doRequest(
            buffer,static_cast<uint32_t>(len),&resCode, nullptr, nullptr
            );
    return resCode;
}
