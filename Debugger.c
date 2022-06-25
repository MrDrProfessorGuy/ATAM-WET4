
#include "Debugger.h"
#include <sys/ptrace.h>
#include <unistd.h>
#include "stdlib.h"
#include "stdio.h"
#include "sys/wait.h"
#include "sys/types.h"
#include <sys/user.h>

#include "assert.h"


enum OP{Add, Remove};

static pid_t program_pid = 0;

pid_t run_target(const char* program_name, char* program_arguments){
    
    pid_t pid = fork();
    if (pid >0){ ///Debugger
        return pid;
    }
    else if (pid == 0){ /// user program
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) < 0){
            exit(1);
        }
        execl(program_name, program_name, program_arguments, NULL);
    }
    
    return FORK_ERROR;
    
}

unsigned long AddBreakpoint(Elf64_Addr address){
    unsigned long data = ptrace(PTRACE_PEEKTEXT, program_pid, (void*)address, NULL);
    //printf("DBG: Original data at 0x%llx: 0x%lx\n", address, data);
    
    unsigned long data_trap = (data & 0xFFFFFFFFFFFFFF00) | 0xCC;
    ptrace(PTRACE_POKETEXT, program_pid, (void*)address, (void*)data_trap);
    
    return data;
}
unsigned long RemoveBreakpoint(Elf64_Addr address, unsigned long data){
    unsigned long curr_data = ptrace(PTRACE_PEEKTEXT, program_pid, (void*)address, NULL);
    //printf("DBG: restoring data at 0x%llx from  0x%lx to 0x%lx\n", address, curr_data, data);
    assert((data&0xFFFFFFFFFFFFFF00) == (curr_data & 0xFFFFFFFFFFFFFF00));
    
    //unsigned long data_trap = (curr_data & 0xFFFFFFFFFFFFFF00) | data;
    ptrace(PTRACE_POKETEXT, program_pid, (void*)address, (void*)data);
    
    
    return data;
}

ReturnVal Break(unsigned long address){
    assert(address > 0);
    int wait_status;
    
    unsigned long instruction = AddBreakpoint(address);
    ptrace(PTRACE_CONT, program_pid, NULL, NULL);
    
    waitpid(program_pid, &wait_status,0);
    if (WIFEXITED(wait_status)) {
        printf("DBG: Child exited\n");
        return ProgEnded;
    }
    if (ptrace(PTRACE_SINGLESTEP, program_pid, NULL, NULL) < 0) {
        perror("ptrace");
        return TraceError;
    }
    RemoveBreakpoint(address, instruction);
    
}

struct user_regs_struct Regs(){
    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, program_pid, 0, &regs);
    return regs;
}

int singleStep(){
    int wait_status;
    printf("singleStep:: brfore: 0x%lx", Regs().rip-1);
    
    if (ptrace(PTRACE_SINGLESTEP, program_pid, NULL, NULL) < 0) {
        perror("ptrace");
        exit(1);
    }
    printf("   after: 0x%lx\n", Regs().rip-1);
    waitpid(program_pid, &wait_status,0);
    return wait_status;
}


void waitFor(unsigned long addr){
    int wait_status;
    printf(" ========== waitFor ==========\n");
    
    ptrace(PTRACE_CONT, program_pid, NULL, NULL);
    waitpid(program_pid, &wait_status,0);
    unsigned long curr_addr = Regs().rip-1;
    printf("waitFor:: addr: 0x%lx curr_addr: 0x%lx\n", addr, curr_addr);
    while (curr_addr != addr){
        if (!WIFSTOPPED(wait_status)){
            printf("ENDED****************\n");
            exit(1);
        }
        ptrace(PTRACE_CONT, program_pid, NULL, NULL);
        waitpid(program_pid, &wait_status,0);
        curr_addr = Regs().rip-1;
        printf("waitFor:: addr: 0x%lx curr_addr: 0x%lx\n", addr, curr_addr);
    }
    printf(" ===========================\n");
    
}


ReturnVal debug(const char* program_name, char* program_arguments, unsigned long func_address){
    int wait_status;
    unsigned int call_counter = 0;
    unsigned long ret_address = 0;
    struct user_regs_struct regs;
    
    printf("debug:: program_name: %s,   func_address: %lx\n", program_name, func_address);
    
    program_pid = run_target(program_name, program_arguments);
    if (program_pid == ForkError){
        return ForkError;
    }
    printf("debug:: program_pid: %d\n", program_pid);
    waitpid(program_pid, &wait_status,0);
    
    /// Add breakPoint at function
    unsigned long ret_instruction = 0;
    unsigned long instruction = AddBreakpoint(func_address);
    printf("debug:: breaking at function: 0x%lx,  instruction: 0x%lx\n", func_address, instruction);
    //ptrace(PTRACE_CONT, program_pid, NULL, NULL);
    //waitpid(program_pid, &wait_status,0);
    waitFor(func_address);
    
    while (WIFSTOPPED(wait_status)){
        printf("debug:: ====== iteration %d ======\n", call_counter);
        
        /// add breakpoint at function return address
        ret_address = ptrace(PTRACE_PEEKTEXT, program_pid, Regs().rsp, NULL);
        ret_instruction = AddBreakpoint(ret_address);
        printf("debug:: ret_address: 0x%lx,   ret_instruction: 0x%lx\n", ret_address, ret_instruction);
        
        /// remove breakpoint from function
        wait_status = singleStep();
        //assert(!WIFEXITED(wait_status));
        RemoveBreakpoint(func_address, instruction);
        printf("debug:: function breakpoint removed\n");
    
    
        /// get return value of function
        //ptrace(PTRACE_CONT, program_pid, NULL, NULL);
        //waitpid(program_pid, &wait_status,0);
        waitFor(ret_address);
        //assert(!WIFEXITED(wait_status)); /// function should return to the calling address
        //ptrace(PTRACE_GETREGS, program_pid, 0, &regs);
        long ret_value = Regs().rax;
        printf("PRF:: call %u at 0x%lx returned with %d\n", call_counter, Regs().rip-1, (int)ret_value);
    
        /// Add breakPoint at function
        instruction = AddBreakpoint(func_address);
        printf("debug:: breaking at function: 0x%lx,  instruction: 0x%lx\n", func_address, instruction);
    
        wait_status = singleStep();
        //assert(!WIFEXITED(wait_status));
        RemoveBreakpoint(ret_address, ret_instruction);
        printf("debug:: ret breakpoint removed\n");
        
        //ptrace(PTRACE_CONT, program_pid, NULL, NULL);
        //waitpid(program_pid, &wait_status,0);
        waitFor(func_address);
        
        
        call_counter++;
    }
    
    
    
    
}
































