cmake_minimum_required(VERSION 3.24)
project(MSDscript)

set(CMAKE_CXX_STANDARD 17)

add_executable(MSDscript main.cpp commandLine.cpp expr.cpp)
