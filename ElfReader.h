//
// Created by guy cohen on 22/06/2022.
//

#ifndef ATAM_WET4_ELFREADER_H
#define ATAM_WET4_ELFREADER_H

#include "elf64.h"
#define ET_EXEC 0x02
#define NAME_NOT_FOUND -1
#define SYM_FOUND 0
#define STB_GLOBAL 1
#define STB_UND 0

typedef char* ElfFile;

int isExecutable(Elf64_Ehdr elf_header);

Elf64_Ehdr getElfHeader(void* elf_file);

Elf64_Shdr get_section_header(const ElfFile elf_file, Elf64_Ehdr elf_header, char* sh_name, Elf64_Word sh_index);

int readSymtab(const ElfFile elf_file, Elf64_Shdr symtab_sh, char* sym_name, Elf64_Sym* func_sym);

Elf64_Addr getVirtualAddress(const ElfFile elf_file, Elf64_Off file_offset);


#endif //ATAM_WET4_ELFREADER_H
