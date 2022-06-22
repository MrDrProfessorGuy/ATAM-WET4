cmake_minimum_required(VERSION 3.19)
project(ATAM_WET4 C)

set(CMAKE_C_STANDARD 99)

add_executable(ATAM_WET4 main.c
                ReadLib.c ReadLib.h
                ElfReader.c ElfReader.h
                Debugger.c Debugger.h)


