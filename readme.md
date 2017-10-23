# Arduino sound experiment

Get some data out fro the sound sensor via arduino and serial interface.
Save it to a single channel wav file.
The sample rate should be very low ~ 1000Hz, which means
under 500Hz can be recorded this way.

## Build

Use cmake to create Makefile and build env.

## wav.cpp

Small utility to create an example wav
1 channel, 1000Hz, 16bit sample

## mi.cpp

Com port reader for sample

## microphone_test.ino

Arduino get data from microphone module.
