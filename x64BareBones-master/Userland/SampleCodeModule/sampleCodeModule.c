#include "include/C_lib.h"
#include "include/Usr_Syscalls.h"
#include "include/shell.h"

/* sampleCodeModule.c */

char * v = (char*)0xB8000;

static int var1 = 0;
static int var2 = 0;



int main() {
	char buffer[1024] = {0};
    welcome();
	scanLine();

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}