#ifndef LIB_H
#define LIB_H

#include <stdint.h>

#define REGS 18 


void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char * cpuVendor(char *result);
char getKey();
int getSec(); 
int getMin();
int getHour();
void beep(uint64_t freq);
void stop_beep();
void htl_lib();

#endif