//
// Created by root on 24. 3. 12.
//

#include "Connection.h"


void Connection::Clear() {
    delete _recvBuffer;
    delete _sendBuffer;
}
