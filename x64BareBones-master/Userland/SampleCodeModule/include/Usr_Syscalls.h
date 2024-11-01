#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>

/**
 * @brief Function that calls write syscall
 * @param fd The file descriptor
 * @param buffer The buffer to write
 * @returns void
*/

void sysCall_write(int fd, char * c);

/**
 * @brief Function that calls read syscall
 * @param fd The file descriptor
 * @param buffer The buffer to read
 * @param count The amount of bytes to read
*/

uint8_t sysCall_read(int fd, char * buff, int length);

/**
 * @brief Function that calls clear syscall
 * @param void
 * @returns void
*/

void sysCall_clear();

/**
 * @brief Function that calls seconds syscall
 * @param sec A pointer where the seconds will be stored
 * @returns void
*/
void sysCall_seconds(int * sec);

/**
 * @brief Function that calls minutes syscall
 * @param min A pointer where the minutes will be stored
 * @returns void
*/
void sysCall_minutes(int * min);

/**
 * @brief Function that calls hours syscall
 * @param hours A pointer where the hours will be stored
 * @returns void
*/

void sysCall_hours(int * hours);

/**
 * @brief Function that calls sound syscall
 * @param time The time the sound will last
 * @param freq The frequency of the sound
 * @returns void
*/

void sysCall_sound(uint64_t time, uint64_t freq);

/**
 * @brief Function that calls putRectangle syscall
 * @param x The x position of the rectangle
 * @param y The y position of the rectangle
 * @param height The height of the rectangle
 * @param width The width of the rectangle
 * @param color The color of the rectangle
 * @returns void
*/

void sysCall_putRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint64_t color);

/**
 * @brief Function that calls ticks syscall
 * @param void
 * @returns The ticks elapsed
*/
uint64_t sysCall_ticks();

/**
 * @brief Function that calls wait syscall
 * @param time The time to wait
 * @returns void
*/
void sysCall_wait(uint64_t time);

/**
 * @brief Function that calls ColorWrite syscall
 * @param fd The file descriptor
 * @param c The char to write
 * @param color The color of the char
 * @returns void
*/

void sysCall_ColorWrite(int fd, char * c, uint64_t color);

/**
 * @brief Function that calls writeReg syscall
 * @param void
 * @returns void
*/

void sysCall_writeRegs();

/**
 * @brief Function that calls cursorX syscall
 * @param void
 * @returns void
*/

uint64_t sysCall_cursorX(); 

/**
 * @brief Function that calls cursorY syscall
 * @param void
 * @returns void
*/

uint64_t sysCall_cursorY();

/**
 * @brief Function that calls setCursor syscall
 * @param x The x position of the cursor
 * @param y The y position of the cursor
 * @returns void
*/

void sysCall_setSize(int size);

/**
 * @brief Function that calls getScreenHeight syscall
 * @param void
 * @returns The screen width
*/

uint64_t sysCall_getScreenHeight();

/**
 * @brief Function that calls the charSize syscall
 * @param width Pointer where the width of the char will be stored
 * @param height Pointer where the height of the char will be stored
 * @returns void
*/

void sysCall_getCharSize(int * width, int * height);


/**
 * @brief Function that calls getDate syscall
 * @param date The date
 * @returns The date
*/
int getDate(int date);

/**
 * @brief Function that calls snapshotState syscall
 * @param void
 * @returns void
*/

int sysCall_snapshotState(); 

/**
 * @brief Function that calls setCursor syscall
 * @param x The x position of the cursor
 * @param y The y position of the cursor
 * @returns void
*/

void sysCall_setCursor(uint64_t x, uint64_t y);

#endif