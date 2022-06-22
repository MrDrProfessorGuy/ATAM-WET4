#include "ReadLib.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "unistd.h"


int File_open(char* file){
    chdir("/Users/guycohen/Library/CloudStorage/OneDrive-Technion/1 Courses/Computer Organization And Programming/Homework/HW4/Wet/ATAM-WET4");
    if (file == NULL){
        return FILE_NULL_ARG;
    }
    int fd = open(file, O_RDONLY);
    if(fd<=0){
        exit(1);     //file doesnt exist
    }
    
    return fd;
}

void* File_map(int fd){
    Elf64_Xword file_size = File_getSize(fd);
    void* elf_file = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(elf_file==(void*)-1){
        File_close(fd);
        exit(1);
    }
    return elf_file;
}


void File_unmap(void* file, int fd){
    Elf64_Xword file_size = File_getSize(fd);
    munmap(file, file_size);
}

void File_close(int fd){
    close(fd);
}

Elf64_Xword File_getSize(int fd){
    return lseek(fd, 0, SEEK_END);
}
















