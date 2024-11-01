#include <stdint.h>
#include "drivers/include/videoDriver.h"
#include "drivers/include/keyBoardDriver.h"
#include <lib.h>
#include <time.h>
#include <defs.h>
#include <registers.h>
#include <interrupts.h>


#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define READ 0
#define WRITE 1
#define CLEAR 2
#define SECONDS 3
#define MINUTES 4
#define HOURS 5
#define SOUND 6
#define RECTANGLE 7 
#define TICKS 8
#define WAIT 9
#define COLORWRITE 10
#define REGISTERS 11
#define CURSORX 12
#define CURSORY 13
#define SET_SIZE 14
#define SCREEN_HEIGHT 15
#define GET_SIZE 16
#define SNAPSHOT_STATE 18
#define SET_CURSOR 19


/**
 * @brief Function that handles read syscall
 * @param fd The file descriptor
 * @param buffer The buffer to read
 * @param count The amount of bytes to read
*/
static void sys_read(uint64_t fd, char * buffer, uint64_t count);

/**
 * @brief Function that handles write syscall
 * @param fd The file descriptor
 * @param buffer The buffer to write
 * @returns void
*/
static void sys_write(uint32_t fd, char * buffer);

/**
 * @brief Function that handles clear syscall
 * @param void
 * @returns void
*/
static void sys_clear();

/**
 * @brief Function that handles seconds syscall
 * @param seconds A pointer where the seconds will be stored
 * @returns void
*/
static void sys_seconds(uint64_t * seconds);

/**
 * @brief Function that handles minutes syscall
 * @param minutes A pointer where the minutes will be stored
 * @returns void
*/
static void sys_minutes(uint64_t * minutes);

/**
 * @brief Function that handles hours syscall
 * @param hours A pointer where the hours will be stored
 * @returns void
*/
static void sys_hours(uint64_t * hours);

/**
 * @brief Function that handles sound syscall
 * @param void
 * @returns void
*/
static void sys_sound();

/**
 * @brief Function that handles rectangle syscall
 * @param x The x position of the rectangle
 * @param y The y position of the rectangle
 * @param height The height of the rectangle
 * @param width The width of the rectangle
 * @param hexColor The color of the rectangle
 * @returns void
*/
static void sys_putRectangle(int x, int y, int height, int width, uint32_t hexColor);

/**
 * @brief Function that handles ticks syscall
 * @param void
 * @returns The ticks elapsed
*/
static uint64_t sys_ticks();

/**
 * @brief Function that handles wait syscall
 * @param time The time to wait
 * @returns void
*/

static void sys_wait(uint64_t time);

/**
 * @brief Function that handles colorwrite syscall
 * @param fd The file descriptor
 * @param buffer String to write
 * @param color The color of the string
*/
static void sys_ColorWrite(uint32_t fd, char * buffer, uint32_t color)

/**
 * @brief Function that handles registers syscall
 * @param void
 * @returns void
*/; 
static void sys_writeReg(); 

uint64_t syscallDispatcher(uint64_t nr, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5){
    switch (nr){
        case READ:
            sys_read(arg0, (char *)arg1, arg2);
            return 0; 
        case WRITE:
            sys_write((uint32_t)arg0, (char *)arg1);
            return 0;
        case CLEAR:
            sys_clear();
            return 0;
        case SECONDS:
            sys_seconds((uint64_t *)arg0);
            return 0;
        case MINUTES:
            sys_minutes((uint64_t *)arg0);
            return 0;
        case HOURS:
            sys_hours((uint64_t *)arg0);
            return 0;
        case SOUND:
            sys_sound(arg0, arg1);
            return 0;
        case RECTANGLE:
            sys_putRectangle(arg0, arg1, arg2, arg3, arg4);
            return 0;
        case TICKS:
            return sys_ticks();
        case WAIT:
            sys_wait(arg0);
            return 0;
        case COLORWRITE:
            sys_ColorWrite(arg0, (char *)arg1, arg2);
            return 0;
        case REGISTERS:
            sys_writeReg();
            return 0; 
        case CURSORX:
            return getCursorX();   
        case CURSORY:
            return getCursorY();
        case SET_SIZE:
            setLetterSize((int)arg0);
            return 0;
        case SCREEN_HEIGHT:
            return getScreenHeight(); 
        case GET_SIZE:
            getCharSize((int *)arg0, (int *)arg1);
            return 0;
        case SNAPSHOT_STATE:
            return snapShotTaken;  
        case SET_CURSOR:
            setCursor(arg0, arg1);
            return 0;  
        default:
            return 0;
    }
}


static void sys_read(uint64_t fd, char * buffer, uint64_t count){
    if(fd == STDIN){ //Check if the file descriptor is STDIN
        while(count > 0){
            char val = nextChar();
            if (val == -1){
                return;
            }
            *buffer = val;
            buffer++;
            count--;
        }
    }else if (fd == STDERR){
        printf("Error: Invalid file descriptor\n", RED);
    }

}
static void sys_write(uint32_t fd, char * buffer){
    putChar(*buffer, WHITE);
}

static void sys_clear(){
    clearScreen();
}

static void sys_seconds(uint64_t * seconds){
    *seconds = getSec();

}
static void sys_minutes(uint64_t * minutes){
    *minutes = getMin();
}
static void sys_hours(uint64_t * hours){
    *hours = getHour();
}

static void sys_sound(uint64_t time, uint64_t freq){
    if(freq <= 0 || time == 0){
        return;
    }

    beep(freq);
    sleep(time);
    stop_beep();
}

static void sys_putRectangle(int x, int y, int height, int width, uint32_t hexColor){
    putRectangle(x, y, height, width, hexColor);
}
static uint64_t sys_ticks(){
    return ticks_elapsed();
}
static void sys_wait(uint64_t time){
    sleep(time);
}

static void sys_ColorWrite(uint32_t fd, char * buffer, uint32_t color){
    putChar(*buffer, color);
}

static void sys_writeReg(){
    printRegAsm();
}

















