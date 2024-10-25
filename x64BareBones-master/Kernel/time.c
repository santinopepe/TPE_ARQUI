#include <time.h>
#include <interrupts.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void sleep(int seconds) {
	
	int currentTicks = ticks;
	while(ticks - currentTicks < seconds * 18) {
		_hlt();
	}
}
