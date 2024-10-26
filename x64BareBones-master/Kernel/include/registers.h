#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

/**
 * Struct that represents the registers of the CPU
 */

typedef struct registers_struct{
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
    uint64_t rip;
    uint64_t cs;
    uint64_t flags;
    uint64_t rsp;
    uint64_t ss;
} registers_struct; 

// Variable that indicates if a snapshot was taken
extern char snapShotTaken; 

/**
 * Prints the registers of the CPU
 * 
 * @param registers The registers of the CPU
 */
//void printRegisters(registers_struct * registers);
void printRegisters(uint64_t * registers);

#endif


