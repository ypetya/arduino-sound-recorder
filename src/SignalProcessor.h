
#ifndef SIGNALPROCESSOR_H
#define SIGNALPROCESSOR_H

#include "SerialReaderCallback.h"

const int BUFFER_SIZE = 1024;

class SignalProcessor {
public:
    SignalProcessor();

    void process(int data);
    virtual void write() {};

    char buffer[BUFFER_SIZE];
    unsigned short int currentBufferSize;
private:
    int index;
};

#endif /* SIGNALPROCESSOR_H */

