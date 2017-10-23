#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h> 
#include <fcntl.h>
#include <termios.h>

using namespace std;

char buffer[20];

void setupPort(int fd) {
#ifndef _WIN32
    struct termios options;
    tcgetattr(fd, &options);
    cfsetspeed(&options, B115200);
    options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);
#endif
}

int openComPortFile(char * deviceFile) {
    int fp;

    if ((fp = open(deviceFile, O_RDWR | O_NOCTTY)) == -1) {
        printf("Serial open error.\n");
        exit(1);
    };

    return fp;
}

int main(int argc, char** argv) {
    int fp = openComPortFile("/dev/cu.usbmodem1411");

    setupPort(fp);

    tcflush(fp, TCIFLUSH);
    
    for (int i = 0; i < 100; i++) {    
        memset(buffer, 0, sizeof (buffer));
        printf("read %d\n", read(fp, buffer, 20));
        printf("%s\n", &buffer);
    }

    close(fp);

    return 0;
}

