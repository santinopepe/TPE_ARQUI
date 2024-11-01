

#include "shell.h"
#include "C_lib.h"
#include "Usr_Syscalls.h"
#include <exceptions.h>
#include "snake.h"

char * commands[] = {"echo", "time", "regs", "clear", "size", "game", "help", "divideBy0", "invalidOp"};
static int cantCommands = 9;

char dateStr[9] = {0};
char timeStr[9] = {0};

/**
 * @brief Decodes the time, as it isn't stored in a human readable format
 * @param time The time to decode
 * @returns The decoded time
*/
static unsigned int decode(unsigned int time); 

/**
 * @brief Converts an integer on string format to a  number with given base
 * @param value The value to convert
 * @param buffer The buffer where the value will be stored
 * @param base The base of the number
 * @returns The number of digits of the number
*/

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base); 


/**
 * @brief Builds the time string
 * @returns The time in the format hh:mm
*/
static char * getTime(); 

/**
 * @brief Builds the date string
 * @returns The date in the format dd/mm/yyyy
*/
static char  * date(); 

/**
 * @brief Calls an invalid operation exception
 * @param void
 * @returns void
*/
static void invalidOpException();

/**
 * @brief Calls a divide by zero exception
 * @param void
 * @returns void
*/
static void divideByZeroException();




void commandLine(){
    colorPrint("$User", COLOR_GREEN);
    colorPrint(": ", COLOR_PURPLE);
}

void welcome(){
    printf("Welcome to the shell! Type 'help' to see the available commands\n");
}

void help(){
    if(sysCall_getScreenHeight() < sysCall_cursorY() + 9){
        clear();
        commandLine();
        printf("help\n");
    }
    printf("Available commands: \ntime - Shows the current time\nregs - Shows the registers\nclear - Clears the screen\nsize - Changes the size of the letters\ngame - Starts the game\nhelp - Shows the available commands\ndivideBy0 - Throws a divide by zero exception\ninvalidOp - Throws an invalid operation exception\necho - Prints the given string\n");
}

void echo(char * str){
    if(sysCall_getScreenHeight() < sysCall_cursorY() - 1){
        clear();
        commandLine();
        printf("echo", str);
    }
    puts(str);
}

void time(){
    if(sysCall_getScreenHeight() <  sysCall_cursorY() + 2){
        clear();
        commandLine();
        printf("time\n");
        
    }
    printf("Current time: %s", getTime());
    printf("Current date: %s", date());
    
}

void regs(){
    if((sysCall_getScreenHeight() < sysCall_cursorY() + 18 && sysCall_snapshotState() == 1) || (sysCall_snapshotState() == 0 && sysCall_getScreenHeight() < sysCall_cursorY())){
        clear();
        commandLine();
        printf("regs\n");
        
        
    }
    sysCall_writeRegs();
}
 
void clear(){
    sysCall_clear();
}

void set_letterSize(float size){
    sysCall_setSize(size);
}

void game(){
    play();
}


void scanLine(){
    char buffer[1024] = {0};
    commandLine();
    while (1) {
        int i = scanf(buffer);
        if (i > 0 && buffer[0] != '\n') {  
            scanCommand(buffer);
        }
        if(sysCall_cursorY() > sysCall_getScreenHeight() - 1){
            clear();
        }
        commandLine();  
        for (int j = 0; j < 1024; j++) {
            buffer[j] = 0;
    }  
    }  
}

void scanCommand(char * command) {
    int i = 0;
    if (command[i] == '\n') {
        return;
    }
    // Find the end of the command  
    while (command[i] != ' ' && command[i] != '\0' && command[i] != '\n') {
        i++;
    }
    // Split the command and the arguments
    char *args = 0;
    if (command[i] == ' ') {
        command[i] = '\0';
        args = command + i + 1;
    } else {
        command[i] = '\0';
    }
    if(command[0] == '!'){ 
        printf("Taking snapshot...\n");
        return; 
    }
    // Check if the command is valid
    for (int j = 0; j < cantCommands; j++) {
        if (strcmp(command, commands[j]) == 0) {
            switch (j) {
                case 0:
                    echo(args);
                    break;
                case 1: 
                    time();
                    break;
                case 2:
                    regs();
                    break;
                case 3:
                    clear();
                    break;
                case 4:
                    int value = atoi(args);
                    if (args != 0 && value > 0 && value < 5) {
                        printf("Setting letter size to %d\n", value);
                        set_letterSize(value); 
                    } else {
                        printf("Error: Invalid Argument\n");
                    }
                    break;
                case 5:
                    game();
                    break;
                case 6:
                    help();
                    break;
                case 7:
                    divideByZeroException();
                    break;
                case 8:
                    invalidOpException();
                    break;
                default:
                    printf("Error: Command not recognized\n");
                    break;
            }
            return;
        }
    }
    printf("Error: Command not recognized\n");
}

void buildDateStr(char * dateStr, int data){
    if(data < 10){
        dateStr[0] = '0';
        uintToBase(data, dateStr + 1, 10);
    } else{
        uintToBase(data, dateStr, 10);
    }
}


static char * getTime(){
    int hours = decode(getDate(HOURS));
    int minutes = decode(getDate(MINUTES));

    buildDateStr(timeStr, hours);
    timeStr[2] = ':';
    buildDateStr(timeStr + 3, minutes);

    return timeStr;
}

static char * date(){
    int day = decode(getDate(DAY));
    int month = decode(getDate(MONTH));
    int year = decode(getDate(YEAR));

    buildDateStr(dateStr, day);
    dateStr[2] = '/';
    buildDateStr(dateStr + 3, month);
    dateStr[5] = '/';
    buildDateStr(dateStr + 6, year);
    return dateStr;
}

static unsigned int decode(unsigned int time){
    return (time >> 4) * 10 + (time & 0xF);
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}


static void invalidOpException(){
    if(sysCall_getScreenHeight() <= sysCall_cursorY() + 24){
        clear();
        commandLine();
        printf("invalidOp\n");
    }
    invalidOpCode();
}

static void divideByZeroException(){
    if(sysCall_getScreenHeight() <= sysCall_cursorY() + 24){
        clear();
        commandLine();
        printf("divideBy0\n");
    }
    divideByZero();
}
