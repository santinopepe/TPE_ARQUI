#ifndef _TIME_H_
#define _TIME_H_


void timer_handler();
int ticks_elapsed();
int seconds_elapsed();

/**
 * @brief  Sleeps the current process for the given amount of seconds
 * @param seconds The amount of seconds to sleep
 * @return void
*/
void sleep(int seconds);

#endif
