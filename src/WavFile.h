
#ifndef WAVFILE_H
#define WAVFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h> 
#include <fcntl.h>
#include <termios.h>
#include <string>

using namespace std;

class WavFile {
public:
    WavFile(string file);
    ~WavFile();
    
    void writeData(char * myData, unsigned long len);
    void closeWavFile();
private:
    uint32_t totalLength = 0;
    int fp;
    char header[44];
    int openWavFile(string file);
    
    void writeHeader();
    void updateHeader();
};

#endif /* WAVFILE_H */

