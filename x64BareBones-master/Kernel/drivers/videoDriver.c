#include "include/videoDriver.h"
#include <font.h>
#include <defs.h>
#include <time.h>

#define DEFAULT_HEIGTH 32
#define DEFAULT_WIDTH 10

static int CHAR_WIDTH = 10; 
static int CHAR_HEIGHT = 32;

static int SIZE= 1; 

uint32_t cursorX = 0; 
uint32_t cursorY = 0;


/**
 * @brief Functions that changes a number that has a string format to a number, with a given base 
 * @param value The number to change
 * @param buffer The buffer where the number is stored
 * @param base The base of the number
 * @returns The number
*/
static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base); 

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
 
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
 
	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

typedef struct vbe_mode_info_structure * VBEInfoPtr;

VBEInfoPtr VBE_mode_info = (VBEInfoPtr) 0x0000000000005C00;


void putPixel(uint32_t hexColor, uint64_t x, uint64_t y) {
    uint8_t * framebuffer = (uint8_t *)(uintptr_t) VBE_mode_info->framebuffer; //Preguntar como sacar este warning
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}


void newLine(){
	cursorX = 0;
	cursorY += CHAR_HEIGHT;
	return; 
}

void clearScreen(){
	for (int i = 0; i < VBE_mode_info->width; i++){
		for (int j = 0; j < VBE_mode_info->height; j++){
			putPixel(BLACK, i, j);
		}
	}
	cursorX = 0;
	cursorY = 0;
}

void clearRectangle(int x, int y, int height, int width){
	putRectangle(x, y, height, width, BLACK);
}

void printf(char * str, uint32_t hexColor){
	int i = 0;
	while(str[i] != '\0'){
		putChar(str[i], hexColor);
		i++;
	}
}

void putTab(){
	if(cursorX + 4 * CHAR_WIDTH >= VBE_mode_info->width){
		newLine();
		return; 
	}
	cursorX += 4 * CHAR_WIDTH;
}

void putBackSpace(){
	if(cursorY == 0 && cursorX == 0){
		return;
	}
	if(cursorX - CHAR_WIDTH < 0){
		cursorX = VBE_mode_info->width - CHAR_WIDTH;
		cursorY -= CHAR_HEIGHT;
		clearRectangle(cursorX, cursorY, CHAR_HEIGHT,CHAR_WIDTH);
		return; 
	}
	if(cursorX==0){
		cursorY -= CHAR_HEIGHT;
		cursorX = VBE_mode_info->width-CHAR_WIDTH/2;
		clearRectangle(cursorX, cursorY, CHAR_HEIGHT,CHAR_WIDTH);
		return;
	}
	cursorX -= CHAR_WIDTH;
	clearRectangle(cursorX, cursorY, CHAR_HEIGHT,CHAR_WIDTH);
}

void putSpace(){
	if(cursorX + CHAR_WIDTH >= VBE_mode_info->width){
		newLine();
		return; 
	}
	cursorX += CHAR_WIDTH;
}

void putRectangle(int x, int y, int height, int width, uint32_t hexColor){
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			putPixel(hexColor, x + i, y + j);
		}
	}
}

void putChar(char c, uint32_t hexColor) {
	int start = c - FIRST_CHAR;
	
    switch (c) {
        case '\n':
			newLine();
            return;
        case '\t':
            putTab();
            return;
        case '\b':
			putBackSpace();			
            return;
        case ' ':
            putSpace();
            return;
        default:
            if (c >= FIRST_CHAR && c <= LAST_CHAR) {
                if (cursorX + CHAR_WIDTH >= VBE_mode_info->width) {
                    newLine();
                }
                // Dibujar el carácter en la posición actual del cursor (letras invertidas)
                for (int i = 0; i < DEFAULT_HEIGTH ; i++) {
                    for (int j = 0; j < DEFAULT_WIDTH; j++) {
                        // Cambiar el orden de los bits, dibujándolos de derecha a izquierda
                        if ((uint8_t)font[i + ((start) * 32)] & (1 << j)) {
							putRectangle(cursorX + j, cursorY + i, SIZE, SIZE, hexColor);
                        	//putPixel(hexColor, cursorX + j, cursorY + i);
                    	}
                    }
                }
                // Incrementar la posición del cursor horizontalmente
                cursorX += CHAR_WIDTH;
            }
            return;
    }
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

void printRegister(uint64_t value){
	char buffer[65];
	uintToBase(value, buffer, 16);
	printf(buffer, WHITE);
}

uint64_t getCursorX(){
	return cursorX/CHAR_WIDTH;
}

void setLetterSize(int size){
	CHAR_WIDTH =  size + DEFAULT_WIDTH;
	CHAR_HEIGHT = size + DEFAULT_HEIGTH;
	SIZE = size;
}

void getCharSize(int * width, int * height){
	*width = CHAR_WIDTH;
	*height = CHAR_HEIGHT;
}

uint64_t getCursorY(){
	return cursorY/CHAR_HEIGHT;
}

uint64_t getScreenHeight(){
	return VBE_mode_info->height/CHAR_HEIGHT;
}

void cursor(){
	putRectangle(cursorX, cursorY, 32, 5, 0x000000);
	sleep(1);
	putRectangle(cursorX, cursorY, 32, 5, 0xFFFFFF);
}

void setCursor(uint64_t x, uint64_t y){
	cursorX = x * CHAR_WIDTH;
	cursorY = y * CHAR_HEIGHT;
}