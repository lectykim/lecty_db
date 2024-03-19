//
// Created by root on 24. 3. 7.
//

#ifndef LECTY_DB_RECVBUFFER_H
#define LECTY_DB_RECVBUFFER_H

#include <vector>
enum class RECV_BUFFER:int{BUFFER_COUNT=10,BUFFER_SIZE=1024};
class RecvBuffer {


public:
    RecvBuffer(int bufferSize);
    ~RecvBuffer() = default;

    void Clean();
    bool OnRead(int numOfBytes);
    bool OnWrite(int numOfBytes);

    char* ReadPos(){return &_buffer[_readPos];}
    char* WritePos(){return &_buffer[_writePos];}
    int DataSize() const{return _writePos- _readPos;}
    int FreeSize() const{return _capacity-_writePos;}


private:
    int _capacity=0;
    int _bufferSize=0;
    int _readPos=0;
    int _writePos=0;
    std::vector<char> _buffer;
};


#endif //LECTY_DB_RECVBUFFER_H
