//
// Created by guy cohen on 22/06/2022.
//

#ifndef ATAM_WET4_READLIB_H
#define ATAM_WET4_READLIB_H

#include "elf64.h"


#define FILE_NULL_ARG -2


int File_open(char* file);
void File_close(int fd);
Elf64_Xword File_getSize(int fd);
void* File_map(int fd);
void File_unmap(void* file, int fd);



#endif //ATAM_WET4_READLIB_H
