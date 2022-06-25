#include <stdio.h>
#include "elf64.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

#include "ReadLib.h"
#include "ElfReader.h"
#include "Debugger.h"


#define HEADERLENGTH sizeof(Elf64_Ehdr)
#define SECTIONHEADERLENGTH sizeof(Elf64_Shdr)
#define NEXT_SH(sh) (((char*)sh))
/// elf defines
#define SHT_SYMTAB 0x02
#define MAXLENGTH 128
#define SHT_STRTAB 0x03

void End(ElfFile file, int fd);

Elf64_Shdr get_section_str_table(Elf64_Ehdr elf_header,int fd){
    Elf64_Off offset = elf_header.e_shoff;
    Elf64_Half section_header_size = elf_header.e_shentsize;
    Elf64_Half section_header_num = elf_header.e_shnum;
    Elf64_Half index = elf_header.e_shstrndx;
    
    Elf64_Shdr* section_header_p = mmap(NULL,section_header_num*section_header_size,PROT_READ,MAP_PRIVATE,fd,offset);
    if (section_header_p < 0){
        exit(1);
    }
    
    section_header_p[index].sh_offset;
    
    
    Elf64_Shdr b = *section_header_p;
    munmap(section_header_p, SECTIONHEADERLENGTH);
    return b;
}



int main(int argc,char* argv[]) {
    char *symtab_name=".symtab";
    char *string_table_name=".strtab";
    
    char* function_name = argv[1];
    char* program_name = argv[2];
    char* program_arguments = argv[3];
    
    Elf64_Ehdr elf_header;
    //Elf64_Shdr section_header_table,symtab;
    
    void* elf_file = NULL;
    
    if (argc < 3){
        exit(1);
    }
    
    int fd = File_open(program_name);
    elf_file = File_map(fd);
    
    elf_header = getElfHeader(elf_file);
    if(!isExecutable(elf_header)){
        printf("PRF:: %s not an executable! :(\n)",program_name);
        End(elf_file, fd);
    }
    
    Elf64_Shdr symtab = get_section_header(elf_file, elf_header, ".symtab", 0);
    Elf64_Sym func_sym;
    int res = readSymtab(elf_file, symtab, "foo", &func_sym);
    if (res == NAME_NOT_FOUND){
        printf("PRF:: %s not found!\n", function_name);
        End(elf_file, fd);
    }
    if (ELF64_ST_BIND(func_sym.st_info) != STB_GLOBAL){
        printf("PRF:: %s not found!\n", function_name);
        End(elf_file, fd);
    }
    if (func_sym.st_shndx == STB_UND){
        printf("%s is Undefined! Need to determine on runtime\n", function_name);
    }
    
    debug(program_name, program_arguments, func_sym.st_value);
    
    printf("hello");
    /*
    Elf64_Shdr stringtable = get_section_header(elf_header,fd,string_table_name);
    
    symtab= get_section_header(elf_header,fd,symtab_name);
    
    for (int i=0;i<symtab.sh_size/symtab.sh_entsize;i++) {
        Elf64_Sym *temp =mmap(NULL,symtab.sh_entsize,PROT_READ,MAP_PRIVATE,fd,symtab.sh_offset+i*symtab.sh_entsize);
        Elf64_Off offset=temp->st_name+stringtable.sh_offset
        
        //unmap
    }
    //todo check if global
    
    */
    
    End(elf_file, fd);
    return 0;
}

void End(ElfFile file, int fd){
    File_unmap(file, fd);
    File_close(fd);
    exit(1);
}











