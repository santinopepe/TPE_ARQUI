/* sampleCodeModule.c */

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {
	//All the following code may be removed
	char * str = "Arquitectura de Computadoras";
    for(int i = 0; str[i] != 0; i++){
        *v = str[i];
        *(v+1) = 0xF2;
        v += 2;
    }


	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}