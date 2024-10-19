#include <registers.h>
#include <videoDriver.h>
//#include <stdio.h>

#define ZERO_EXCEPTION_ID 0

static void zero_division();
static void invalid_op_code();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	else{
		invalid_op_code();
	}

}

static void zero_division() {
	printf("Zero division exception\n");
	printRegisters();
	printf("\n Regresando a la shell...\n");
}

static void invalid_op_code() {
	printf("Invalid op code exception\n");
	printRegisters();
	printf("\n Regresando a la shell...\n");	
}
