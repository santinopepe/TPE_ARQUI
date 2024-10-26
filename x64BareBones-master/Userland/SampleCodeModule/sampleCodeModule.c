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
	
    while (1) {
        printf("user: ");
        
        int i = scanf(buffer);
        if (i > 0) {  // Procesa solo si se ingresa un comando
            scanCommand(buffer);
        }

        // Limpiar el buffer después de cada iteración
        for (int j = 0; j < 256; j++) {
            buffer[j] = 0;
        }
    }

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}