
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
    int buf_ix = 0;
    int buf_start = 0;
    int buf_end = 0;
    char buffer[20];

    int num_start = 0;
    char num[10];

    void setupPort(int fd);
    int openComPortFile(const char * deviceFile);
    void parseBuffer();
    void reset(int fp);

    bool isNumber();
    bool isEnd();
    void resetNum();
    void resetBuffer();
};

#endif /* SERIALREADER_H */

