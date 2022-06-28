#include <stdio.h>
#include "elf64.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

#include "ReadLib.h"
#include "ElfReader.h"
#include "Debugger.h"



void End(ElfFile file, int fd);


int main(int argc,char* argv[]) {
    char* function_name = argv[1];
    char* program_name = argv[2];
    char* program_arguments[argc-2];
    for (int i = 0; i < argc-3; i++) {
        program_arguments[i] = argv[i+3];
    }
    program_arguments[argc-3];
    
    Redirection redirection = Normal;
    Elf64_Ehdr elf_header;
    void* elf_file = NULL;
    
    if (argc < 3){
        exit(1);
    }
    int fd = File_open(program_name);
    elf_file = File_map(fd);
    
    elf_header = getElfHeader(elf_file);
    if(!isExecutable(elf_header)){
        printf("PRF:: %s not an executable! :(\n",program_name);
        End(elf_file, fd);
    }
    
    Elf64_Shdr symtab = get_section_header(elf_file, elf_header, ".symtab", 0);
    Elf64_Sym func_sym;
    Elf64_Addr func_address = 0;
    
    int res = readSymtab(elf_file, symtab, function_name, &func_sym);
    if (res == NAME_NOT_FOUND){
        printf("PRF:: %s not found!\n", function_name);
        End(elf_file, fd);
    }
    if (ELF64_ST_BIND(func_sym.st_info) != STB_GLOBAL){
        printf("PRF:: %s is not a global symbol! :(\n", function_name);
        End(elf_file, fd);
    }
    if (func_sym.st_shndx == STB_UND){
        //printf("%s is Undefined! Need to determine on runtime\n", function_name);
        Elf64_Shdr sh_rela_plt = get_section_header(elf_file, elf_header, ".rela.plt", 0);
        res = readRelaSym(elf_file, sh_rela_plt, function_name, &func_address);
        if (res == NAME_NOT_FOUND){
            End(elf_file, fd);
        }
        redirection = PLT;
        //printf("debug:: Dynamic - %s plt is at address: 0x%llx\n", function_name, func_address);
    }
    else{
        func_address = func_sym.st_value;
    }

    debug(program_name, argv+2, func_address, redirection);
    End(elf_file, fd);
    return 0;
}

void End(ElfFile file, int fd){
    File_unmap(file, fd);
    File_close(fd);
    exit(1);
}











