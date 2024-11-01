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

#define SECONDS 0X0
#define MINUTES 0X2
#define HOURS 0X4
#define DAY 0X7
#define MONTH 0X8
#define YEAR 0X9

/**
 * @brief  Prints the welcome message
 * @param void  
 * @return void
*/
void welcome(); 

/**
 * @brief  Prints the help message
 * @param void  
 * @return void
*/

void help();

/**
 * @brief Prints the echo message
 * @param str The string to print
 * @return void
*/

void echo(char * str);

/**
 * @brief Prints the time and date(UTC)
 * @param void
 * @return void
*/

void time();

/**
 * @brief Prints the registers of the CPU
 * @param void
 * @return void
*/
void regs();


/**
 * @brief Clears the screen
 * @param void
 * @return void
*/
void clear();

/**
 * @brief Sets the size of the letters
 * @param size The size of the letters
 * @return void
*/

void set_letterSize(float size);


/**
 * @brief Boots the game 
 * @param void
 * @return void
*/
void game();

/**
 * @brief Handles the commands written on the terminal
 * @param command The command to scan
 * @return void
*/

void scanCommand(char * command);

/**
 * @brief Scans the line on the terminal
 * @param void
 * @return void
*/

void scanLine();

/**
 * @brief Prints the command line on the terminal "$User: "
 * @param void
 * @return void
*/
void commandLine();
#endif // _SHELL_H


