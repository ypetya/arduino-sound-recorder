#include "SerialReader.h"
#include <string>

SerialReader::SerialReader(int seconds,
        string serialFile, SerialReaderCallback *callback) {
    this->seconds = seconds;
    cb = callback;
    fp = openComPortFile(serialFile.c_str());

    setupPort(fp);

    reset(fp);
}

SerialReader::~SerialReader() {
    close(fp);
}

void SerialReader::listen() {
    unsigned long limit = seconds * 7500;
    int j = 0;
    size_t buf_size = sizeof (buffer);
    for (unsigned long i = 0; i < limit; i += buf_len) {
        //memset(buffer, 0, buf_size);
        buf_len = read(fp, &buffer[0], buf_size);
        j += buf_len;
        if (j > 1000) {
            printf(".");
            fflush(stdout);
            j = 0;
        }
        parseBuffer();
    }
    printf("\n");

    close(fp);
}

void SerialReader::parseBuffer() {
    cb->onDataRead(buffer, buf_len);
}

void SerialReader::setupPort(int fd) {
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

int SerialReader::openComPortFile(const char * deviceFile) {
    if ((fp = open(deviceFile, O_RDWR | O_NOCTTY)) == -1) {
        printf("Serial open error.\n");
        exit(1);
    };

    return fp;
}

void SerialReader::reset(int fp) {
    tcflush(fp, TCIFLUSH);
    buf_len = 0;
}