#include "include/C_lib.h"
#include "include/Usr_Syscalls.h"

/* sampleCodeModule.c */

char * v = (char*)0xB8000;

static int var1 = 0;
static int var2 = 0;


int main() {
	
	
	//sysCall_square(0, 0, 50, 50, 0xFF00); 
	char c = 0;
	while (1)
	{c = read_char();
		sysCall_wait(5);
	
	}
	
		
	/*
	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;*/
}