#include <stdint.h>
#include "videoDriver.h"
#include "include/defs.h"
#include "include/lib.h"
#include "include/interrupts.h"

#define BUFFER_SIZE 256

extern void saveState(void);

static char isKey(uint8_t key);

static char buffer[BUFFER_SIZE];
static int bufferIndex = 0;
static char shiftPressed = 0;
static char snapShotTaken = 0;
static char capsLock = 0;
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
#define L_SHIFT_PRESS 0x2A
#define L_SHIFT_RELEASE 0xAA
#define R_SHIFT_PRESS 0x36
#define R_SHIFT_RELEASE 0xB6
#define CAPS_LOCK_PRESS 0x3A
#define ALT_PRESS 0x3B
#define ALT_RELEASE 0xB8

#define CTRL_PRESS 0x1D
#define CTRL_RELEASE 0x9D

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
    if(currentChar == cantElems){
        return -1;
    }
    cantElems--;
    return buffer[currentChar++];
}

static char isKey(uint8_t key){
    return (key >= 0x3B && key <= 0x44) || key == 0x57 || key == 0x58;
}

void keyBoardHandler(){
    uint64_t key = getKey();
    
   if(key == NULL){
      return; 
   }

    if(key >= 0 && key <= 256 && keyValues[key][0] != 0){
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
            break;
        case L_SHIFT_PRESS:
        case R_SHIFT_PRESS:
            shiftPressed = 1;
            break;
        case L_SHIFT_RELEASE:
        case R_SHIFT_RELEASE:
            shiftPressed = 0;
            break;
        case CAPS_LOCK_PRESS:
            capsLock = 1 - capsLock;
            break;    
        default:
            break;
       }

        if(key < MAX_PRESS_KEY){
            if(bufferIndex == BUFFER_SIZE){
                bufferIndex = 0;
            }
            if(cantElems == BUFFER_SIZE){
                cantElems = 0;
            }
            if(currentChar == BUFFER_SIZE){
                currentChar = 0;
            }
            buffer[bufferIndex++] = keyValues[key][shiftPressed || capsLock];
            cantElems++;
       }
    }

   // printf(keyValues[key][shiftPressed || capsLock], WHITE);
    

    if(snapShotTaken){
       saveState();
       snapShotTaken = 0; 
    }
    
}