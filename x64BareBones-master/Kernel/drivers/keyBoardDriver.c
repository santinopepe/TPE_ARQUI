#include <stdint.h>
#include "include/videoDriver.h"
#include <defs.h>
#include <lib.h>
#include "include/keyBoardDriver.h"
#include <registers.h>
#include <interrupts.h>

#define BUFFER_SIZE 1024

extern void saveState(void);


static char buffer[BUFFER_SIZE] = {0};
static int bufferIndex = 0;
static int capsLock = 0;
static int currentChar = 0; 
static int cantElems = 0;


#define KEYS 58
#define MAX_PRESS_KEY 0x70 // Superior values are the released keys
#define TAB_NUM 4

// Special keys
#define ESC 0x01
#define ENTER 0x1C
#define BACKSPACE 0x0E
#define TAB 0x0F

#define CAPS_LOCK_PRESS 0x3A

#define ALT_PRESS 0x3B
#define ALT_RELEASE 0xB8


#define CTRL_PRESS 0x1D
#define CTRL_RELEASE 0x9D

// Key values, the first value is the key pressed, the second is the key pressed with shift/caps lock
static unsigned char keyValues[KEYS][2] = {
	{0, 0},
	{27, 27},
	{'1', '!'},
	{'2', '@'},
	{'3', '#'},
	{'4', '$'},
	{'5', '%'},
	{'6', '^'},
	{'7', '&'},
	{'8', '*'},
	{'9', '('},
	{'0', ')'},
	{'-', '_'},
	{'=', '+'},
	{'\b', '\b'},
	{'\t', '\t'},
	{'q', 'Q'},
	{'w', 'W'},
	{'e', 'E'},
	{'r', 'R'},
	{'t', 'T'},
	{'y', 'Y'},
	{'u', 'U'},
	{'i', 'I'},
	{'o', 'O'},
	{'p', 'P'},
	{'[', '{'},
	{']', '}'},
	{'\n', '\n'},
	{0, 0},
	{'a', 'A'},
	{'s', 'S'},
	{'d', 'D'},
	{'f', 'F'},
	{'g', 'G'},
	{'h', 'H'},
	{'j', 'J'},
	{'k', 'K'},
	{'l', 'L'},
	{';', ':'},
	{39, 34},
	{'`', '~'},
	{0, 0},
	{'\\', '|'},
	{'z', 'Z'},
	{'x', 'X'},
	{'c', 'C'},
	{'v', 'V'},
	{'b', 'B'},
	{'n', 'N'},
	{'m', 'M'},
	{',', '<'},
	{'.', '>'},
	{'/', '?'},
	{0, 0},
	{0, 0},
	{0, 0},
	{' ', ' '},
};

char nextChar(){
    if(cantElems<=0){
        return -1;
    }
    if(currentChar == BUFFER_SIZE){
        currentChar = 0;
    }
    cantElems--;
    return buffer[currentChar++];
}


void keyBoardHandler(){
    uint64_t key = getKey();
    
    if(key == NULL){
        return; 
    }

    if((key >= 0 && key <= 256) || keyValues[key][0] != 0){ 
        switch (key) 
        {
        case BACKSPACE:
            buffer[bufferIndex++] = '\b';
            cantElems++;
            return;
        case ENTER:
            buffer[bufferIndex++] = '\n';
            cantElems++;
            return;
        case TAB:
            buffer[bufferIndex++] = '\t';
            cantElems++;
            return; 
        case ESC:
            snapShotTaken = 1;
            return;
        case CAPS_LOCK_PRESS:
            capsLock = 1-capsLock;
            break;   
        default:
            break;
       }

        if(key < MAX_PRESS_KEY){ 
            
            //Check so we don't have problems with the buffer
            if(bufferIndex == BUFFER_SIZE){
                bufferIndex = 0;
            }
            if(cantElems == BUFFER_SIZE){
                cantElems = 0;
            }
            if(currentChar == BUFFER_SIZE){
                currentChar = 0;
            }
            buffer[bufferIndex++] = keyValues[key][capsLock]; // We add the key to the buffer
            cantElems++;
       }
    }


    if(buffer[bufferIndex-1] == '!'){ // ! is the snapshot key, here we check if we took a snapshot
       saveState();
       snapShotTaken = 1; 
    }
    
}