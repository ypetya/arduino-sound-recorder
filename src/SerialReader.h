
#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h> 
#include <fcntl.h>
#include <termios.h>
#include <string>

#include "SerialReaderCallback.h"

using namespace std;

class SerialReader {
public:
    SerialReader(int seconds, string serialFile, SerialReaderCallback* callback);
    //    SerialReader(const SerialReader& orig);
    virtual ~SerialReader();
    
    void listen();
private:
    SerialReaderCallback * cb;
    int seconds;
    int fp;
    char buffer[1024];
    size_t buf_len=0;

    void setupPort(int fd);
    int openComPortFile(const char * deviceFile);
    void parseBuffer();
    void reset(int fp);
};

#endif /* SERIALREADER_H */

