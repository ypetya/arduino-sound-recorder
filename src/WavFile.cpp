#include "WavFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h> 
#include <fcntl.h>
#include <string>

WavFile::WavFile(string file) {
    openWavFile(file);
}

WavFile::~WavFile() {
    closeWavFile();
}

int WavFile::openWavFile(string file) {
    totalLength = 0;

    if ((fp = open(file.c_str(), O_CREAT | O_RDWR, S_IWRITE | S_IREAD)) == -1) {
        printf("Open error.\n");
        exit(1);
    };

    writeHeader();

    return fp;
}

void WavFile::writeData(char *myData, unsigned long len) {
    totalLength += len;
    write(fp, myData, len);
}

/* set file size and counts in header */
void WavFile::updateHeader() {
    uint32_t dSize = totalLength + 36;
    memcpy(&header[4], &dSize, 4);
    if (pwrite(fp, &header[4], sizeof (totalLength), 4) != 4) {
        printf(" Broken header. (1)\n");
        exit(1);
    };
    memcpy(&header[40], &totalLength, 4);
    if (pwrite(fp, &header[40], sizeof (totalLength), 40) != 4) {
        printf(" Broken header. (2)\n");
        exit(1);
    };
}

void WavFile::closeWavFile() {
    updateHeader();
    close(fp);
}

void WavFile::writeHeader() {
    memset(header, 0, sizeof (header));

    string riff = "RIFF";
    strcpy(header, riff.c_str());
    string wave = "WAVE";
    strcpy(&header[8], wave.c_str());
    string fmt = "fmt ";
    strcpy(&header[12], fmt.c_str());
    uint32_t lengthOfFormatData = 16;
    memcpy(&header[16], &lengthOfFormatData, 4);
    uint16_t type = 1; // 1 is PCM
    memcpy(&header[20], &type, 2);
    uint16_t channels = 1;
    memcpy(&header[22], &channels, 2);
    uint32_t sampleRate = 1000; //4410; //= 1000;
    memcpy(&header[24], &sampleRate, 4);
    uint32_t rate_x_sample_x_channels8 = 2000; //8820; //= 2000; // 1000 * 16 / 8
    memcpy(&header[28], &rate_x_sample_x_channels8, 4);
    uint16_t bpschper8 = 2; // 2 = 16bit mono ( bitPerSample* Channels)/8
    memcpy(&header[32], &bpschper8, 2);
    uint16_t bps = 16;
    memcpy(&header[34], &bps, 2);
    strcpy(&header[36], "data");

    write(fp, header, (size_t) 44);
}