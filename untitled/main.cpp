#include "PacketQueue.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <string>
#include <vector>
#include <map>
#include "EpollManager.h"
#include "ThreadPool.h"
#include "SocketManager.h"
#include <thread>
#include "InitialGlobal.h"


int main() {
    InitialGlobal::Init();
    int fd = SocketManager::Init();
    GEpollManager->EpollInit();
    GEpollManager->epollAdd(fd);
    std::vector<std::thread> threads;
    //threads.emplace_back([](){});

    while(true){
        GEpollManager->EpollRunning();
    }

}