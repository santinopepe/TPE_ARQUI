#include <registers.h>
#include "drivers/include/videoDriver.h"
#include <defs.h>
#include <interrupts.h>

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
	printf("Zero division exception\n", RED);
	printRegAsm();
	printf("\n Returning to shell...\n", RED);
}

static void invalid_op_code() {
	printf("Invalid op code exception\n", RED);
	printRegAsm();
	printf("\n Returning to shell...\n", RED);	
}
