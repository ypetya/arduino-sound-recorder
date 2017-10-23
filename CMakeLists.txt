cmake_minimum_required(VERSION 3.7)
project(cp)

set(CMAKE_CXX_STANDARD 11)

message(
    " *** This is cmake:" ${CMAKE_SYSTEM} 
    " version:" ${CMAKE_VERSION}
    " compiler:" ${CMAKE_CXX_COMPILER_ID}) 

set(EXECUTABLE_OUTPUT_PATH bin)

add_executable(mi mi.cpp)
add_executable(wav wav.cpp)