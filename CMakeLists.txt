cmake_minimum_required(VERSION 3.7)
project(cp)

set(CMAKE_CXX_STANDARD 11)

message(
    " *** This is cmake:" ${CMAKE_SYSTEM} 
    " version:" ${CMAKE_VERSION}
    " compiler:" ${CMAKE_CXX_COMPILER_ID}) 

set(EXECUTABLE_OUTPUT_PATH bin)

add_executable(mi prototype/mi.cpp)
add_executable(wav prototype/wav.cpp)

add_executable(listen 
    src/SerialReader.h src/SerialReader.cpp
    src/SerialReaderCallback.h src/SerialReaderCallback.cpp
    src/WavFile.h src/WavFile.cpp
    src/main.cpp)