
#include <cstdlib>
#include "SerialReader.h"
#include "SerialReaderCallback.h"
#include "WavFile.h"

using namespace std;

WavFile * wf;

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Invalid arguments!\nUsage : listen <seconds> <devicefile> <filename>\n\n");
        exit(1);
    }
    int seconds = atoi(argv[1]);
    string device = argv[2];
    string wavFile = argv[3];
    printf("Creating wav file : %s\n", wavFile.c_str());
    
    wf = new WavFile(argv[3]);
    
    class CB : public SerialReaderCallback {
        void onDataRead(int data) {
            string str = to_string(data);
            wf->writeData((char*)str.c_str());
        }
    };
    
    SerialReaderCallback * cb = new CB();
    
    printf("Opening device : %s\n", device.c_str());
    SerialReader * r = new SerialReader(seconds, device, cb);
    
    r->listen();
    wf->closeWavFile();
    
    return 0;
}

