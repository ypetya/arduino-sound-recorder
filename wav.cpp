#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h> 
#include <fcntl.h>
#include <string>

using namespace std;

int openWavFile(std::string file);
void closeWavFile(int fp);
void writeData(int fp);

char myData[10000];

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Invalid arguments!\nUsage : wav <filename>\n\n");
        exit(1);
    }
    int fp = openWavFile(argv[1]);

    memset(myData, 0, sizeof (myData));
    for (int i = 1; i<sizeof (myData); i += 4) {
        myData[i] = 180; // 16 bit for one data
        myData[i + 1] = 0;
        myData[i + 2] = 50; // 16 bit for the other data
        myData[i + 3] = 0;
    }

    writeData(fp);

    closeWavFile(fp);
    return 0;
}

uint32_t totalLength = 0;

void writeHeader(int fp);

int openWavFile(std::string file) {
    int fp;

    if ((fp = open(file.c_str(), O_CREAT | O_RDWR, S_IWRITE | S_IREAD)) == -1) {
        printf("Open error.\n");
        exit(1);
    };

    totalLength = 0;

    writeHeader(fp);

    return fp;
}

char header[44];

void writeHeader(int fp) {
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
    uint32_t sampleRate = 1000;
    memcpy(&header[24], &sampleRate, 4);
    uint32_t rate_x_sample_x_channels8 = 2000; // 1000 * 16 / 8
    memcpy(&header[28], &rate_x_sample_x_channels8, 4);
    uint16_t bpschper8 = 2; // 2 = 16bit mono ( bitPerSample* Channels)/8
    memcpy(&header[32], &bpschper8, 2);
    uint16_t bps = 16;
    memcpy(&header[34], &bps, 2);
    strcpy(&header[36], "data");

    write(fp, header, (size_t) 44);
};

/* set file size and counts in header */
void updateHeader(int fp, uint32_t dataSize) {
    uint32_t dSize = dataSize + 36;
    memcpy(&header[4], &dSize, 4);
    if (pwrite(fp, &header[4], sizeof (dataSize), 4) != 4) {
        printf(" Broken header. (1)\n");
        exit(1);
    };
    memcpy(&header[40], &dataSize, 4);
    if (pwrite(fp, &header[40], sizeof (dataSize), 40) != 4) {
        printf(" Broken header. (2)\n");
        exit(1);
    };
}

void writeData(int fp) {
    totalLength += sizeof (myData);
    write(fp, myData, sizeof (myData));
}

void closeWavFile(int fp) {
    updateHeader(fp, totalLength);
    close(fp);
}