//
// Created by root on 24. 3. 12.
//

#ifndef UNTITLED_SENDBUFFER_H
#define UNTITLED_SENDBUFFER_H

#include <vector>
enum {BUFFER_COUNT=10,BUFFER_SIZE=1024};

class SendBuffer {
public:
    SendBuffer(int bufferSize);
    ~SendBuffer() = default;

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


#endif //UNTITLED_SENDBUFFER_H
