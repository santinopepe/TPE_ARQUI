#ifndef C_LIB_H
#define C_LIB_H

#include <stdint.h>

#define ELIMINATE_ERROR -2 //Error code  when the user trier to eliminate "user: " from the command line


/**
 * @brief  Reads a character from the keyboard
 * @param void
 * @return char
 */
char read_char();

/**
 * @brief  Writes a character to the screen
 * @param c The character to write
 * @param fd The file descriptor
 * @return void
*/
void putChar(char c, int fd);

/**
 * @brief  Writes a string to the screen, and adds a new line
 * @param str The string to write
 * @return void
*/

void puts(const char * str);


/**
 * @brief  Writes the first n characters of a string to the screen
 * @param str The string to write
 * @return void
*/
void printNchars(const char * str, int n);

/**
 * @brief  Reads a string from the keyboard
 * @param buff The buffer where the string will be stored
 * @return The number of characters read
*/
int scanf(char * buff);

/**
 * @brief  Converts a string to an integer
 * @param str The string to convert
 * @return The integer
*/
int atoi(char * str);

/**
 * @brief clears the screen
 * @param void
 * @return void
*/
void clearScreen();


/**
 * @brief  Compares two strings
 * @param str1 The first string
 * @param str2 The second string
 * @return 0 if the strings are equal, -1 if str1 is smaller, 1 if str2 is smaller
*/
int strcmp(const char * str1, const char * str2);

/**
 * @brief  Prints a formatted string
 * @param str The string to print
 * @param ... The arguments to replace the format specifiers
 * @return void
*/
void printf(const char * str, ...);

/**
 * @brief Prints a integer
 * @param num The integer to print
 * @return void
*/
void printInt(int num);

/**
 * @brief Prints a char with a specific color
 * @param c The char to print
 * @param fd The file descriptor
 * @param color The color of the char
*/
void putColorChar(char c, int fd, uint64_t color); 

/**
 * @brief Prints a string with a specific color
 * @param str The string to print
 * @param color The color of the string
*/

void colorPrint(char * str, uint64_t color); 

/**
 * @brief Counts the length of a string
 * @param str The string to count
 * @return The length of the string
*/

int strlen(const char * str); 

#endif // C_LIB_H