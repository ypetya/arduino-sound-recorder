
#include <cstdlib>
#include "SerialReader.h"
#include "SerialReaderCallback.h"
#include "SignalProcessor.h"
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

    class CB : public SignalProcessor, public SerialReaderCallback {
    public:
        CB():SignalProcessor(),SerialReaderCallback(){}
        void onDataRead(int data) {
            this->process(data);
        }
        void write() {
            wf->writeData(buffer, currentBufferSize);
        }
    };

    CB * cb = new CB();

    printf("Opening device : %s\n", device.c_str());
    SerialReader * r = new SerialReader(seconds, device, cb);

    r->listen();
    cb->write();
    wf->closeWavFile();

    return 0;
}

