#include "SerialReader.h"

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
    int limit = seconds * 1000 / 3;
    for (int i = 0; i < limit; i++) {
        buf_end = read(fp, &buffer[buf_start], sizeof (buffer));

        parseBuffer();
    }

    close(fp);
}

bool SerialReader::isNumber() {
    return (buffer[buf_ix] >= '0' && buffer[buf_ix] <= '9');
}

bool SerialReader::isEnd() {
    return buf_ix == buf_end;
}

void SerialReader::resetNum() {
    memset(num, 0, sizeof (num));
    num_start = 0;
}

void SerialReader::resetBuffer() {
    memset(buffer, 0, sizeof (buffer));
    buf_start = 0;
}

void SerialReader::reset(int fp) {
    tcflush(fp, TCIFLUSH);
    resetNum();
    resetBuffer();
}

void SerialReader::parseBuffer() {
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
        if ((parsed = atoi(num)) > 0) {
            printf("%d\n",parsed);
            cb->onDataRead(parsed);
        }// else { printf("err\n"); }
        resetNum();
        // flush buf
        while (!isNumber() && !isEnd()) buf_ix++;
    }
    resetBuffer();
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