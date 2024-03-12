//
// Created by root on 24. 3. 7.
//

#include "EpollManager.h"
#include <cstdio>
#include <fcntl.h>
#include <netinet/in.h>
#include "RecvBuffer.h"
int EpollManager::EpollInit() {
    if((_fdEpoll=epoll_create(MAX_EVENTS))>0)
        _isEpollInit=true;

    return _isEpollInit;
}

int EpollManager::epollAdd(int fd) {
    struct epoll_event ev{};
    ev.events=EPOLLIN|EPOLLET;
    ev.data.fd=fd;
    _socketFd=fd;
    return epoll_ctl(_fdEpoll,EPOLL_CTL_ADD,fd,&ev);
}

void EpollManager::EpollRunning() {
    //Event loop
    while(true){
        _eventCount = epoll_wait(_fdEpoll,_events,MAX_EVENTS,_timeout);
        if(_eventCount<0)
        {
            printf("epoll_wait() error [%d] \n",_eventCount);
        }
        for(int i=0;i<_eventCount;i++)
        {
            int client_fd,client_len;
            struct sockaddr_in client_addr;
            client_len=sizeof(client_addr);

            client_fd = accept(_socketFd,(struct sockaddr*)&client_addr,(socklen_t*)&client_len);

            int flags = fcntl(client_fd,F_GETFL);

            flags |= O_NONBLOCK;
            if(fcntl(client_fd,F_SETFL,flags)<0)
            {
                printf("client_fd[%d] fcntl error \n",client_fd);
                return;
            }

            if(client_fd<0)
            {
                printf("accept() error [%d] \n",client_fd);
                continue;
            }

            struct epoll_event clientEvents;
            clientEvents.events=EPOLLIN|EPOLLET;
            clientEvents.data.fd=client_fd;
            if(epoll_ctl(_fdEpoll,EPOLL_CTL_ADD,client_fd,&clientEvents)<0)
            {
                printf("client epoll ctl error \n");
                close(client_fd);
                continue;
            }
            else
            {
                int str_len;
                client_fd = _events[i].data.fd;

                char* buffer =GRecvBuffer->WritePos();
                int len = GRecvBuffer->FreeSize();

                str_len = read(client_fd,buffer,len);

                GRecvBuffer->OnWrite(str_len);

                if(str_len == 0)
                {
                    printf("client Disconnect [%d] \n",client_fd);
                    close(client_fd);
                    epoll_ctl(_fdEpoll,EPOLL_CTL_DEL,client_fd,nullptr);
                }
                else
                {
                    int dataSize = GRecvBuffer->DataSize();

                }



            }
        }

    }
}
