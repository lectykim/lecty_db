//
// Created by root on 24. 3. 7.
//

#ifndef LECTY_DB_EPOLLMANAGER_H
#define LECTY_DB_EPOLLMANAGER_H
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/unistd.h>
enum{
    MAX_EVENTS=1024
};
class EpollManager {
public:
    int EpollInit();
    int epollAdd(int fd);
    void EpollRunning();

private:
    int _fdEpoll=-1;
    bool _isEpollInit=false;
    struct epoll_event _events[MAX_EVENTS];
    int _eventCount=-1,_timeout=-1;
    int _socketFd=-1;
};


#endif //LECTY_DB_EPOLLMANAGER_H
