//
// Created by root on 24. 3. 14.
//

#include "Responser.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <iostream>
void Responser::Response(uint8_t responseCode, uint8_t output, uint32_t len) {
    if(send(_conn.GetFd(), reinterpret_cast<const void *>(output), len, 0) == -1){
        std::cout << "client send error" << std::endl;
    }
}
