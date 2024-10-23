#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y); // Puts a pixel in the screen

void putBackScreen(); // Puts a background in the screen

void newLine();

void clearScreen();

void clearRectagle(int x, int y, int height, int width);

void printf(char * str, uint32_t hexColor);

void putTab();

void putBackSpace();

void putSpace();

void putRectangle(int x, int y, int height, int width, uint32_t hexColor);

void putChar(char c, uint32_t hexColor);

