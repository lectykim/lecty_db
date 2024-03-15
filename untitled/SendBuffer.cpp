//
// Created by root on 24. 3. 12.
//

#include "SendBuffer.h"
#include <cstring>
SendBuffer::SendBuffer(int bufferSize):_bufferSize(bufferSize)
{
    _capacity = bufferSize*static_cast<int>(SEND_BUFFER::BUFFER_COUNT);
    _buffer.resize(_capacity);
}

void SendBuffer::Clean() {
    int dataSize = DataSize();
    if(dataSize == 0)
    {
        _readPos = _writePos = 0;
    }
    else
    {
        if(FreeSize()<_bufferSize)
        {
            ::memcpy(&_buffer[0],&_buffer[_readPos],dataSize);
            _readPos=0;
            _writePos = dataSize;
        }
    }
}

bool SendBuffer::OnRead(int numOfBytes) {
    if(numOfBytes>DataSize())
        return false;
    _readPos += numOfBytes;
    return true;
}

bool SendBuffer::OnWrite(int numOfBytes) {
    if(numOfBytes>FreeSize())
        return false;
    _writePos += numOfBytes;
    return true;
}
