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

const int MAX_THREAD_COUNT=16;

ThreadPool* GThreadPool = new ThreadPool(MAX_THREAD_COUNT);
EpollManager* GEpollManager= new EpollManager();
int main() {
    int fd = SocketManager::Init();
    GEpollManager->EpollInit();
    GEpollManager->epollAdd(fd);
    std::vector<std::thread> threads;
    threads.emplace_back([](){
        GEpollManager->EpollRunning();
    });

}