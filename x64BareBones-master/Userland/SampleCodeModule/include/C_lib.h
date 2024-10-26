#ifndef C_LIB_H
#define C_LIB_H

#include <stdint.h>

#define ELIMINATE_ERROR -2 //Error code  when the user trier to eliminate "user: " from the command line

char read_char();

void putChar(char c, int fd);

void puts(const char * str);

void printNchars(const char * str, int n);

int scanf(char * buff);

int atoi(char * str);

void clearScreen();

int strcmp(const char * str1, const char * str2);

void printf(const char * str, ...);

void printInt(int num);

void putColorChar(char c, int fd, uint64_t color); 

void colorPrint(char * str, uint64_t color); 

int strlen(const char * str); 

#endif // C_LIB_H