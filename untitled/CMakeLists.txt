cmake_minimum_required(VERSION 3.27)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp
        hashtable.cpp
        hashtable.h
        avl_tree.cpp
        avl_tree.h
        EpollManager.cpp
        EpollManager.h
        RecvBuffer.cpp
        RecvBuffer.h
        Connection.cpp
        Connection.h
        Parser.cpp
        Parser.h
        SendBuffer.cpp
        SendBuffer.h
        PacketQueue.cpp
        PacketQueue.h
        LockQueue.cpp
        LockQueue.h
        ThreadPool.cpp
        ThreadPool.h
        SocketManager.cpp
        SocketManager.h
)
