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


static void sys_read(uint64_t fd, char * buffer, uint64_t count);
static void sys_write(uint32_t fd, char * buffer);
static void sys_clear();
static void sys_seconds(uint64_t * seconds);
static void sys_minutes(uint64_t * minutes);
static void sys_hours(uint64_t * hours);
static void sys_sound();
static void sys_putRectangle(int x, int y, int height, int width, uint32_t hexColor);
static uint64_t sys_ticks();
static void sys_wait();
static void sys_ColorWrite(uint32_t fd, char * buffer, uint32_t color); 
static void sys_writeReg(); 

uint64_t syscallDispatcher(uint64_t nr, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5){
    switch (nr){
        case READ:
            sys_read(arg0, (char *)arg1, arg2);
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
        case SOUND:
            sys_sound(arg0, arg1);
            return 0;
        case RECTANGLE:
            sys_putRectangle(arg0, arg1, arg2, arg3, arg4);
            return 0;
        case TICKS:
            return ticks_elapsed();
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
        default:
            return 0;
    }
}


static void sys_read(uint64_t fd, char * buffer, uint64_t count){
    if(fd == STDIN){
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

















