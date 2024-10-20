#include "videoDriver.h"
#include <font.h>
#include <defs.h>

#define CHAR_WIDTH 9
#define CHAR_HEIGHT 16




uint32_t cursorX = 0; 
uint32_t cursorY = 0;



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
    uint8_t * framebuffer = (uint8_t *) VBE_mode_info->framebuffer;
    uint64_t offset = (x * ((VBE_mode_info->bpp)/8)) + (y * VBE_mode_info->pitch);
    framebuffer[offset]     =  (hexColor) & 0xFF;
    framebuffer[offset+1]   =  (hexColor >> 8) & 0xFF; 
    framebuffer[offset+2]   =  (hexColor >> 16) & 0xFF;
}


void putBackScreen(){

	/* CAMBIAR SCREEN WIDTH Y SCREEN HEIGHT POR LOS VALORES REALES
	*  HACER LAS FUNCIONES GETWIDTH Y GETHEIGHT PARA OBTENERLOS
	*/
	int screenWidth = 1000;
	int screenHeight = 1000;
	int square = 0;
	
    for (int y = 0; y < screenHeight; y += 30) {
        for (int x = 0; x < screenWidth; x += 30) {
            for (int i = 0; i < 30; i++) {
                for (int j = 0; j < 30; j++) {
                    if (square % 2 == 0)
                        putPixel(0x007fd7fa, x + i, y + j);
                    else
                        putPixel(0x0065adc9, x + i, y + j);
                }
            }
			square++;
        }    
		square++;
	}
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
}

void clearSquare(int x, int y, int size){
	putSquare(x, y, size, BLACK);
}

void printf(char * str, uint32_t hexColor){
	int i = 0;
	while(str[i] != 0){
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
	if(cursorX - CHAR_WIDTH < 0){
		cursorX = VBE_mode_info->width - CHAR_WIDTH;
		cursorY -= CHAR_HEIGHT;
		return; 
	}
	cursorX -= CHAR_WIDTH;
}

void putSpace(){
	if(cursorX + CHAR_WIDTH >= VBE_mode_info->width){
		newLine();
		return; 
	}
	cursorX += CHAR_WIDTH;
}

void putSquare(int x, int y, int size, uint32_t hexColor){
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			putPixel(hexColor, x + i, y + j);
		}
	}
}

void putChar (char c, uint32_t hexColor){
	int start = c - 33; //Despues sacar Magic num
	switch (c)
	{
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
		if ( c >= FIRST_CHAR && c <= LAST_CHAR){
			if(cursorX + CHAR_WIDTH >= VBE_mode_info->width){
			newLine();
			}
			for (int i = 0; i < 32; i++) {
        		if (i % 2 == 0 && i != 0) {
           			cursorY += CHAR_HEIGHT;  // Salto a la siguiente fila de píxeles
            		cursorX = 0;  // Reinicia la posición horizontal al inicio
        		}
        
        	// Comprueba el bit correspondiente en la fuente para determinar si se debe dibujar un píxel
        	font[i + (start * 32)] & (char)0x01 ? putSquare(cursorX, cursorY, CHAR_WIDTH, hexColor) : 0;
        
        	cursorX += CHAR_WIDTH;  // Avanza a la siguiente posición horizontal
        
       		 uint8_t aux = 0x02;
       		 for (int j = 0; j < 8; j++) {
            // Comprueba cada bit de la fuente y dibuja un píxel si está activo
            	((uint8_t)font[i + (start * 32)] & (uint8_t)aux) >> j ? putSquare(cursorX, cursorY, CHAR_WIDTH, hexColor) : 0;
           		cursorX += CHAR_WIDTH;  // Avanza a la siguiente posición horizontal
            	aux <<= 1;  // Desplaza el bit auxiliar hacia la izquierda
       		}
   		}

		cursorX += CHAR_WIDTH;
	}
		return; 
	}

	

}



