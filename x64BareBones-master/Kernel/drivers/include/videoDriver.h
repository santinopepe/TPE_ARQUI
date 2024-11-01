#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>

/**
 * @brief Function that puts a pixel in the screen
 * @param hexColor The color of the pixel
 * @param x The x position of the pixel
 * @param y The y position of the pixel
 * @returns void
*/
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y); 


/**
 * @brief Function that puts a new line in the screen
 * @param void
 * @returns void
*/
void newLine();

/**
 * @brief Function that clears the screen
 * @param void
 * @returns void
*/
void clearScreen();

/**
 * @brief Function that clears a rectangle in the screen
 * @param x The x position of the rectangle
 * @param y The y position of the rectangle
 * @param height The height of the rectangle
 * @param width The width of the rectangle
 * @returns void
*/
void clearRectagle(int x, int y, int height, int width);

/**
 * @brief Function that prints a string in the screen
 * @param str The string to print
 * @param hexColor The color of the string
 * @returns void
*/

void printf(char * str, uint32_t hexColor);

/**
 * @brief Function that puts a tab in the screen
 * @param void
 * @returns void
*/

void putTab();

/**
 * @brief Function that puts a backspace in the screen
 * @param void
 * @returns void
*/

void putBackSpace();

/**
 * @brief Function that puts a space in the screen
 * @param void
 * @returns void
*/

void putSpace();

/**
 * @brief Function that puts a rectangle in the screen
 * @param x The x position of the rectangle
 * @param y The y position of the rectangle
 * @param height The height of the rectangle
 * @param width The width of the rectangle
 * @param hexColor The color of the rectangle
 * @returns void
*/

void putRectangle(int x, int y, int height, int width, uint32_t hexColor);

/**
 * @brief Function that puts a char in the screen
 * @param c The char to print
 * @param hexColor The color of the char
 * @returns void
*/

void putChar(char c, uint32_t hexColor);

/**
 * @brief Function that prints a register
 * @param value The value of the register
 * @returns void
*/

void printRegister(uint64_t value); 

/**
 * @brief Function that gets the x position of the cursor
 * @param void
 * @returns The x position of the cursor
*/

uint64_t getCursorX(); 

/**
 * @brief Function that gets the y position of the cursor
 * @param void
 * @returns The y position of the cursor
*/

uint64_t getCursorY();

/**
 * @brief Function that sets the size of the letters
 * @param size The size of the letters
 * @returns void
*/

void setLetterSize(int size);

/**
 * @brief Function that gets the height of the screen
 * @param void
 * @returns The height of the screen
*/
uint64_t getScreenHeight(); 


/**
 * @brief Function that gets the size of the letters
 * @param width The width of the letters
 * @param height The height of the letters
 * @returns void
*/
void getCharSize(int * width, int * height);

/**
 * @brief Function that sets the cursor in a position
 * @param x The x position of the cursor
 * @param y The y position of the cursor
 * @returns void
*/
void setCursor(uint64_t x, uint64_t y);

#endif // VIDEO_DRIVER_H