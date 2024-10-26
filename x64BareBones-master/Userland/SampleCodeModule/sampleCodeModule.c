#include "include/C_lib.h"
#include "include/Usr_Syscalls.h"
#include "include/shell.h"

/* sampleCodeModule.c */

char * v = (char*)0xB8000;

static int var1 = 0;
static int var2 = 0;



int main() {
	char buffer[256] = {0};
	welcome();
	printf("user: "); 

	while(1){
		int i = scanf(buffer);
		if(i != 0 && i != -1){
			scanCommand(buffer);
			for(int j = 0; j < 256; j++){
				buffer[j] = 0;
			}
		}

		if(i != ELIMINATE_ERROR){
			printf("user: "); 
		}
	}

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}