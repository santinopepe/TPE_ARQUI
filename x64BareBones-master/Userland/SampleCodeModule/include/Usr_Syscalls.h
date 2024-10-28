#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

void sysCall_write(int fd, char * c);

uint8_t sysCall_read(int fd, char * buff, int length);

void sysCall_clear();

void sysCall_seconds(int * sec);

void sysCall_minutes(int * min);

void sysCall_hours(int * hours);

void sysCall_sound(uint64_t freq, uint64_t time);

void sysCall_putRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint64_t color);

uint64_t sysCall_ticks();

void sysCall_wait(uint64_t time);

void sysCall_ColorWrite(int fd, char * c, uint64_t color);

void sysCall_writeRegs();

uint64_t sysCall_cursorX(); 

uint64_t sysCall_cursorY();

void sysCall_setSize(int size);

uint64_t sysCall_getScreenHeight();

void sysCall_getCharSize(int * width, int * height);

void sysCall_Cursor();

int getDate(int date);

int sysCall_snapshotState(); 

#endif