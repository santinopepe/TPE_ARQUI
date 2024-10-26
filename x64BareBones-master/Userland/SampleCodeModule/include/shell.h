#ifndef _SHELL_H
#define _SHELL_H

#define COLOR_BLACK 0x000000
#define COLOR_WHITE 0xFFFFFF
#define COLOR_RED 0xFF0000
#define COLOR_GREEN 0x00FF00
#define COLOR_BLUE 0x0000FF
#define COLOR_YELLOW 0xFFFF00
#define COLOR_PURPLE 0xFF00FF
#define COLOR_CYAN 0x00FFFF
#define COLOR_ORANGE 0xFFA500
#define COLOR_PINK 0xFFC0CB





void welcome(); 

void help();

void echo(char * str);

void time();

void regs();

void clear();

void set_letterSize(float size);

void game();

void scanCommand(char * command);

void commandLine();
#endif // _SHELL_H


