#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>


// Variable that indicates if a snapshot was taken
extern char snapShotTaken; 

/**
 * @brief  Prints the registers of the CPU
 * @param registers The registers of the CPU
 * @return void
 */
void printRegisters(uint64_t * registers);

#endif


