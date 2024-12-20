#include <registers.h>
#include "drivers/include/videoDriver.h"
#include <defs.h>

//Vector con todos los registros 
static char * regs[] = {"RAX","RBX","RCX","RDX","RSI","RDI","RBP","R8","R9","R10","R11","R12","R13","R14","R15", "RSP","RIP", "RFLAGS"};


char snapShotTaken = 0; 


void printRegisters(uint64_t * registers){
	if(snapShotTaken == 0){
		printf("Snapshot wasn't taken, to take a snapshot press ! (use caps lock)", RED);
		newLine();
		return;
	}
	for (int i = 0; i < 18; i++){
		printf(regs[i], WHITE);
		printf(" = 0x", WHITE);
		printRegister(registers[i]);
		newLine();
	}
	snapShotTaken = 0; // We reset the flag
}