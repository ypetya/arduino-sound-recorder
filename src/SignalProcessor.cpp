
#include <cstring>
#include "SignalProcessor.h"

SignalProcessor::SignalProcessor() {
    memset(buffer,0,sizeof(buffer));
}

void SignalProcessor::process(int data) {
        unsigned short int d = (unsigned short int) data;
        this->buffer[currentBufferSize + 0] = (char) (d & 255);
        this->buffer[currentBufferSize + 1] = (char) ((d > 8) & 255);
        
        currentBufferSize+= 2;
        if(currentBufferSize == BUFFER_SIZE*2) {
            this->write();
            currentBufferSize=0;
        }
}