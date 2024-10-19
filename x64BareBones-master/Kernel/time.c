#include <time.h>

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
	int called_int = 0;
	int last_seconds = 0;
	if(called_int < 3){
		if(seconds_elapsed() != last_seconds && seconds_elapsed() % seconds == 0){
			called_int++;
			last_seconds = seconds_elapsed();
		}
	}
}
