
#include "Debugger.h"
#include <sys/ptrace.h>
#include <unistd.h>
#include "stdlib.h"

#include "stdio.h"
#include "assert.h"


enum OP{Add, Remove};

pid_t run_target(const char* program_name, char* program_arguments){
    
    pid_t pid = fork();
    if (pid >0){ ///Debugger
        return pid;
    }
    else if (pid == 0){ /// user program
        if (ptrace(PT_TRACE_ME, 0, NULL, NULL) < 0){
            exit(1);
        }
        execl(program_name, program_name, program_arguments, NULL);
    }
    
    return FORK_ERROR;
    
}

unsigned long AddBreakpoint(Elf64_Addr address){
    unsigned long data = ptrace(PTRACE_PEEKTEXT, child_pid, (void*)address, NULL);
    printf("DBG: Original data at 0x%x: 0x%x\n", address, data);
    
    unsigned long data_trap = (data & 0xFFFFFFFFFFFFFF00) | 0xCC;
    ptrace(PTRACE_POKETEXT, child_pid, (void*)address, (void*)data_trap);
    
    return data;
}
unsigned long RemoveBreakpoint(Elf64_Addr address, unsigned long data){
    unsigned long curr_data = ptrace(PTRACE_PEEKTEXT, child_pid, (void*)address, NULL);
    printf("DBG: restoring data at 0x%x from  0x%x to 0x%x\n", address, curr_data, data);
    assert((data&0xFFFFFFFFFFFFFF00) == (curr_data & 0xFFFFFFFFFFFFFF00));
    
    unsigned long data_trap = (curr_data & 0xFFFFFFFFFFFFFF00) | 0xCC;
    ptrace(PTRACE_POKETEXT, child_pid, (void*)address, (void*)data);
    
    
    return data;
}

int debug(const char* program_name, char* program_arguments){
    int waitstatus;
    unsigned int call_counter = 0;
    
    pid_t program_pid = run_target(program_name, program_arguments);
    if (program_pid == FORK_ERROR){
        return FORK_ERROR;
    }
    
    




    
}
































