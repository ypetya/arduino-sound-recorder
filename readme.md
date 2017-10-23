# Arduino sound experiment

Get some data out from the sound sensor of arduino via serial interface.
Save it to a single channel wav file.
The sample rate will be very low ~ 1000Hz, which means under 500Hz can be
 recorded this way.

## Build

Use cmake to create Makefile and build env.

## Prototype implementation in the prototype folder

### prototype/wav.cpp

Small utility to create an example wav
1 channel, 1000Hz, 16bit sample

### prototype/mi.cpp

Com port reader for sample

### prototype/microphone_test.ino

Arduino get data from microphone module.

## Minimal cpp solution

Run it with run.sh