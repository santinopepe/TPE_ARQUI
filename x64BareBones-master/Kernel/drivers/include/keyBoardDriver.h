#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

/**
 * @brief Function code in assembly that get the key pressed (code at libasm.asm)
 * @param void
 * @returns char
*/
extern char getKey();

/**
 * @brief Function that handles the keyboard
 * @param void
 * @returns void
 * 
*/
void keyBoardHandler();

/**
 * @brief Function that returns the next char in the buffer
 * @param void
 * @returns char
 * 
*/
char nextChar();

#endif // KEYBOARDDRIVER_H
