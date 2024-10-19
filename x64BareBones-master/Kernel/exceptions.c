#include <registers.h>


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
	// Handler para manejar excepcíon
}

static void invalid_op_code() {
	// Handler para manejar excepcíon
}
