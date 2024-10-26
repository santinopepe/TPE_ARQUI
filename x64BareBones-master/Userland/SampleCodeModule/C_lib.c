#include "include/Usr_Syscalls.h"
#include <stdarg.h>
#include "include/C_lib.h"

char read_char(){
    char buffer[1] = {0};
    sysCall_read(0, buffer, 1);
    return buffer[0];
}

void putChar(char c, int fd){
    sysCall_write(1, &c);
}

void putColorChar(char c, int fd, uint64_t color){
    sysCall_ColorWrite(1, &c, color);
}

void colorPrint(char * str, uint64_t color){
    int i = 0;
    while(str[i] != '\0'){
        putColorChar(str[i], 1, color);
        i++;
    }
}

void puts(const char * str){
    int i = 0;
    while(str[i] != '\0'){
        putChar(str[i], 1);
        i++;
    }
    putChar('\n', 1);
}

void printNchars(const char * str, int n){
    int i = 0;
    while(str[i] != '\0' && i < n){
        putChar(str[i], 1);
        i++;
    }
}


//CHEQUEAR
// devuelvo la cantidad de caracteres leidos
int scanf(char * buffer) {
    int idx = 0;
    while (1) {
        char c = read_char();
        if (c != -1 && c != 0) {
            if (c == '\b' && idx > 0) {
                idx--;
            } else if (c == '\n') {
                buffer[idx] = '\0';
                return idx;
            } else if (c != '\t') {
                buffer[idx++] = c;
            }
        }
    }
    return -1;
}


int atoi(char * str){
    int res = 0;
    int i = 0;
    while(str[i] != '\0'){
        res = res * 10 + str[i] - '0';
        i++;
    }
    return res;
}

void clearScreen(){
    sysCall_clear();
}

int strcmp(const char * str1, const char * str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

int strlen(const char * str){
    int i = 0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}

void printInt(int num){
    if(num == 0){
        putChar('0',1);
        return;
    }
    if(num < 0){
        putChar('-',1);
        num = -num;
    }
    char buffer[10];
    int i = 0;
    while(num > 0){
        buffer[i] = num % 10 + '0';
        num /= 10;
        i++;
    }
    i--;
    while(i >= 0){
        putChar(buffer[i],1);
        i--;
    }
}


static void va_print(const char * str, va_list list) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '%' && str[i+1] != '\0') {
            i++;
            switch (str[i]) {
                case 'd':
                    printInt(va_arg(list, int));
                    break;
                case 'c':
                    putChar(va_arg(list, int), 1);
                    break;
                case 's':
                    puts(va_arg(list, char *));
                    break;
                default:
                    putChar('%', 1);
                    putChar(str[i], 1);
                    break;
            }
        } else {
            putChar(str[i], 1);
        }
        i++;
    }
}

void printf(const char * str, ...){
    va_list list;
    va_start(list, str);
    va_print(str, list);
    va_end(list);
}

