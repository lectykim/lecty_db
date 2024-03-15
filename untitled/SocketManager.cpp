//
// Created by root on 24. 3. 14.
//

#include "SocketManager.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <cstdio>
#include <fcntl.h>
#include <csignal>
#include <cstring>

int SocketManager::Init() {
    int serverFd = socket(AF_INET,SOCK_STREAM,0);
    if(serverFd<0)
    {
        printf("Socket() serror \n");
        return 0;
    }

    //server_fd nonblock socket setting, use edge trigger
    int flags = fcntl(serverFd,F_GETFL);
    flags |= O_NONBLOCK;
    //소켓 옵션 설정 비정상 종료 시 해당 포트 재사용 가능하도록 설정
    int option = true;
    int error_check = setsockopt(serverFd,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
    if(error_check<0)
    {
        printf("setsockopt error [%d] \n",error_check);
        close(serverFd);
        return 0;
    }

    struct sockaddr_in mSockAddr;
    memset(&mSockAddr,0,sizeof(mSockAddr));
    mSockAddr.sin_family = AF_INET;
    mSockAddr.sin_port = htons(7777);
    mSockAddr.sin_addr.s_addr = htonl(INADDR_ANY); //사용 가능한 ip 사용하기

    error_check = bind(serverFd,(struct sockaddr*)&mSockAddr,sizeof(mSockAddr));
    if(error_check<0)
    {
        printf("bind error [%d] \n",error_check);
        close(serverFd);
        return 0;
    }

    listen(serverFd,5);

    return serverFd;

}
