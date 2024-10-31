#include "include/C_lib.h"
#include "include/Usr_Syscalls.h"
#include "include/shell.h"
#include "include/exceptions.h"

/* sampleCodeModule.c */

char * v = (char*)0xB8000;

static int var1 = 0;
static int var2 = 0;



int main() {
    welcome();
	//sysCall_sound(1, 500);
	
	while (1)
	{
		scanLine();
	}
	
	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}