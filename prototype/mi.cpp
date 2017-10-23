#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h> 
#include <fcntl.h>
#include <termios.h>
#include <string>

using namespace std;

int buf_ix = 0;
int buf_start = 0;
int buf_end = 0;
char buffer[20];

void setupPort(int fd);
int openComPortFile(const char * deviceFile);
void parseBuffer();
void reset(int fp);

string serialFile = "/dev/cu.usbmodem1411";

int main(int argc, char** argv) {
    int fp = openComPortFile(serialFile.c_str());

    setupPort(fp);

    reset(fp);
    
    for (int i = 0; i < 100; i++) {
        buf_end = read(fp, &buffer[buf_start], sizeof (buffer));

        parseBuffer();
    }

    close(fp);

    return 0;
}

int num_start = 0;
char num[10];

bool isNumber() {
    return (buffer[buf_ix] >= '0' && buffer[buf_ix] <= '9');
}

bool isEnd() {
    return buf_ix == buf_end;
}

void resetNum() {
    memset(num, 0, sizeof (num));
    num_start =0;
}

void resetBuffer() {
    memset(buffer, 0, sizeof (buffer));
    buf_start = 0;
}

void reset(int fp) {
    tcflush(fp, TCIFLUSH);
    resetNum();
    resetBuffer();
}

void parseBuffer() {
    int parsed;

    buf_ix = buf_start;

    while (!isEnd()) {
        // read numbers
        for (;
                isNumber() && !isEnd(); 
                num_start++, buf_ix++) {
            num[num_start] = buffer[buf_ix];
        }
        if (isEnd()) {
            break;
        }
        // get a parsed num
        if( (parsed = atoi(num))> 0) {
            printf("%d\n",parsed);
        }// else { printf("err\n"); }
        resetNum();
        // flush buf
        while (!isNumber() && !isEnd()) buf_ix++;
    }
    resetBuffer();
}

void setupPort(int fd) {
#ifndef _WIN32
    struct termios options;
    tcgetattr(fd, &options);
    cfsetspeed(&options, B115200);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    options.c_cflag |= ECHO | ECHONL;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);
#endif
}

int openComPortFile(const char * deviceFile) {
    int fp;

    if ((fp = open(deviceFile, O_RDWR | O_NOCTTY)) == -1) {
        printf("Serial open error.\n");
        exit(1);
    };

    return fp;
}