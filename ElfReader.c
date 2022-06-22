
#include "ElfReader.h"
#include "stdlib.h"
#include "string.h"

#include "assert.h"

#define NextSH(sh, size) ((Elf64_Shdr*) ((char*)sh + size))
#define NextSym(sym, size) ((Elf64_Sym*) ((char*)sym + size))
#define FileOffset(cast, file, offset) ((cast) ((char*)file + offset))

int isExecutable(Elf64_Ehdr elf_header){
    return elf_header.e_type == ET_EXEC;
}

Elf64_Ehdr getElfHeader(void* elf_file){
    return *(Elf64_Ehdr*)elf_file;
}


Elf64_Word next_str(char* string_array, Elf64_Word iter){
    if (!string_array[iter]){
        return iter;
    }
    
    while (string_array[iter]){
        iter++;
    }
    return iter+1;
}
Elf64_Word get_str_index(ElfFile file, Elf64_Off offset, Elf64_Xword size, char* name){
    char* str_tbl = file + offset;
    if (str_tbl < 0){
        exit(1);
    }
    
    Elf64_Word index = 0;
    Elf64_Word iter = 1;
    while (iter < size && strcmp(&str_tbl[iter], name)){
        iter = next_str(str_tbl, iter);
        index++;
    };
    
    if (iter > size){
        return NAME_NOT_FOUND;
    }
    return iter;
}


Elf64_Shdr get_section_header(const ElfFile elf_file, Elf64_Ehdr elf_header, char* sh_name, Elf64_Word sh_index){
    Elf64_Off sh_offset = elf_header.e_shoff;
    Elf64_Half sh_size = elf_header.e_shentsize;
    Elf64_Half sh_num = elf_header.e_shnum;
    Elf64_Half sh_strtbl_idx = elf_header.e_shstrndx;
    
    Elf64_Shdr* sh_table_start = elf_file + sh_offset;

    
    Elf64_Off sh_strtbl_off = sh_table_start[sh_strtbl_idx].sh_offset;
    Elf64_Xword sh_strtbl_size = sh_table_start[sh_strtbl_idx].sh_size;
    
    if (sh_name == NULL){
        Elf64_Shdr a = sh_table_start[sh_index];
        return a;
    }
    
    sh_index = get_str_index(elf_file, sh_strtbl_off, sh_strtbl_size, sh_name);
    Elf64_Shdr* section_header = sh_table_start;
    for (Elf64_Half index = 0; index <= sh_num; index++) {
        if (section_header->sh_name == sh_index){
            break;
        }
        section_header = NextSH(section_header, sh_size);
    }
    
    Elf64_Shdr b = *section_header;
    
     return b;
     
}

int readSymtab(const ElfFile elf_file, Elf64_Shdr symtab_sh, char* sym_name, Elf64_Sym* func_sym){
    Elf64_Xword symtable_size = symtab_sh.sh_size;
    Elf64_Xword sym_size = symtab_sh.sh_entsize;
    Elf64_Xword sym_num = symtable_size/sym_size;
    
    assert(symtable_size%sym_size == 0);
    
    Elf64_Shdr sh_strtab = get_section_header(elf_file, getElfHeader(elf_file), NULL, symtab_sh.sh_link);
    
    
    
    Elf64_Word sym_name_index = get_str_index(elf_file, sh_strtab.sh_offset, sh_strtab.sh_size, sym_name);;
    if (sym_name_index == NAME_NOT_FOUND){
        return NAME_NOT_FOUND;
    }
    
    Elf64_Sym* symbol = FileOffset(Elf64_Sym*, elf_file, symtab_sh.sh_offset);
    for (Elf64_Xword index = 0; index < sym_num; index++) {
        
        if (sym_name_index == symbol->st_name){
            *func_sym = *symbol;
            return SYM_FOUND;
        }
        
        symbol = NextSym(symbol, sym_size);
    }
    
    return NAME_NOT_FOUND;
}












