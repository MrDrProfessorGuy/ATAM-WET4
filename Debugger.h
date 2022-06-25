//
// Created by guy cohen on 22/06/2022.
//

#ifndef ATAM_WET4_DEBUGGER_H
#define ATAM_WET4_DEBUGGER_H


#include "elf64.h"



#define FORK_ERROR -1
typedef enum ReturnVal {Success, ProgEnded, TraceError, ForkError} ReturnVal;


ReturnVal debug(const char* program_name, char* program_arguments[], unsigned long func_address);





#endif //ATAM_WET4_DEBUGGER_H
