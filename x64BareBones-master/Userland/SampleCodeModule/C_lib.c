#include "include/Usr_Syscalls.h"
#include <stdarg.h>


char read_char(char * buff){
    char buffer[1] = {0};
    sysCall_read(buff);
    return buffer[0];
}

void putChar(char c){
    sysCall_write(1,c);
}

void puts(const char * str){
    int i = 0;
    while(str[i] != 0){
        putChar(str[i]);
        i++;
    }
}

void printNchars(const char * str, int n){
    int i = 0;
    while(str[i] != 0 && i < n){
        putChar(str[i]);
        i++;
    }
}


//CHEQUEAR
int scanf(char * buff){
    char c;
    int i = 0;
    while((c = read_char(buff)) != '\n'){
        buff[i] = c;
        i++;
    }
    buff[i] = 0;
    return i;
}

int atoi(char * str){
    int res = 0;
    int i = 0;
    while(str[i] != 0){
        res = res * 10 + str[i] - '0';
        i++;
    }
    return res;
}

void clearScreen(){
    sysCall_clear();
}

int strcmp(const char * str1, const char * str2){
    int i = 0;
    while(str1[i] != 0 && str2[i] != 0){
        if(str1[i] != str2[i]){
            return 0;
        }
        i++;
    }
    return str1[i] == str2[i];
}

static void va_print(const char * str, va_list list){
    int i = 0;
    while(str[i] != 0){
        if(str[i] == '%'){
            i++;
            switch (str[i])
            {
            case 'd':
                printInt(va_arg(list, int));
                break;
            case 'c':
                putChar(va_arg(list, int));
                break;
            case 's':
                puts(va_arg(list, char *));
                break;
            default:
                break;
            }
        }else{
            putChar(str[i]);
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

void printInt(int num){
    if(num == 0){
        putChar('0');
        return;
    }
    if(num < 0){
        putChar('-');
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
        putChar(buffer[i]);
        i--;
    }
}





