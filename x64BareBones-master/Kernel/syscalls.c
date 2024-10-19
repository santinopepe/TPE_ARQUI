#include <stdint.h>
#include <videoDriver.h>
#include "drivers/include/keyBoardDriver.h"
#include <lib.h>
#include <time.h>
#include<defs.h>


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
#define SQUARE 7 
#define TICKS 8
#define WAIT 9

extern void beep();
extern stop_beep();

static void sys_read(uint64_t fd, char * buffer, uint64_t count);
static void sys_write(uint64_t fd, char * buffer, uint64_t count);
static void sys_clear();
static void sys_seconds(uint64_t * seconds);
static void sys_minutes(uint64_t * minutes);
static void sys_hours(uint64_t * hours);
static void sys_sound();
static void sys_square(int x, int y, int size, uint32_t hexColor);
static uint64_t sys_ticks();
static void sys_wait();


uint64_t syscallDispatcher(uint64_t nr, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5){
    switch (nr){
        case READ:
            sys_read(arg0, (char *)arg1, arg2);
        case WRITE:
            sys_write(arg0, (char *)arg1, arg2);
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
        case SQUARE:
            sys_square(arg0, arg1, arg2, arg3);
            return 0;
        case TICKS:
            return getTicks();
        case WAIT:
            sys_wait(arg0);
            return 0;
        default:
            return 0;
    }
}


static void sys_read(uint64_t fd, char * buffer, uint64_t count){
    if(fd == STDIN){
        while(count > 0){
            char val = next();
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
static void sys_write(uint64_t fd, char * buffer, uint64_t count){
    if(fd == STDOUT){
       printf(buffer, WHITE);
    }else if (fd == STDERR){
       printf("Error: Invalid file descriptor\n", RED);
    }
}

static void sys_clear(){
    clearScreen();
}

static void sys_seconds(uint64_t * seconds){
    *seconds = getSeconds();

}
static void sys_minutes(uint64_t * minutes){
    *minutes = getMinutes();
}
static void sys_hours(uint64_t * hours){
    *hours = getHours();
}

static void sys_sound(uint64_t time, uint64_t freq){
    if(freq <= 0 || time == 0){
        return;
    }

    beep(freq);
    sleep(time);
    stop_beep();
}

static void sys_square(int x, int y, int size, uint32_t hexColor){
    putSquare(x, y, size, hexColor);
}
static uint64_t sys_ticks(){
    return ticks_elapsed();
}
static void sys_wait(uint64_t time){
    sleep(time);
}




















