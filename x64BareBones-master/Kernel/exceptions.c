#include <registers.h>
#include "drivers/include/videoDriver.h"
#include <defs.h>
#include <interrupts.h>
#include <registers.h>


#define ZERO_EXCEPTION_ID 0



/**
 * @brief Zero division exception
 * @param void
 * @returns void
 */
static void zero_division();

/**
 * @brief Invalid op code exception
 * @param void
 * @returns void
 */
static void invalid_op_code();


void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID){
		zero_division();
	}else{
		invalid_op_code();
	}

}

static void zero_division() {
	printf("Zero division exception\n", RED);
	snapShotTaken = 1; // Here we set the flag to 1, else the printRegisters function will not print the registers
	printRegAsm();
	printf("Returning to shell...\n", RED);
	return;
}

static void invalid_op_code() {
	printf("Invalid op code exception\n", RED);
	snapShotTaken = 1; // Here we set the flag to 1, else the printRegisters function will not print the registers
	printRegAsm();
	printf("Returning to shell...\n", RED);	
	return;
}
