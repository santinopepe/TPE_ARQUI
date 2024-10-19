#include <registers.h>

//Vector con todos los registros 
static char * regs[] = {"RAX","RBX","RCX","RDX","RSI","RDI","RBP","R8","R9","R10","R11","R12","R13","R14","R15", "RSP","RIP", "RFLAGS"};
extern const uint64_t registers[18];

char snapShotTaken = 0; 

void printRegisters(){
	int i;
	for (i = 0; i < 18; i++) {
		printf("%d: %s: 0x%x\n", i, regs[i], registers[i]);
	}
}