#ifndef LIB_H
#define LIB_H

#include <stdint.h>

#define REGS 18 


void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

extern char * cpuVendor(char *result);
extern char getKey();
extern int getSec(); 
extern int getMin();
extern int getHour();
extern void beep(uint64_t freq);
extern void stop_beep();

#endif