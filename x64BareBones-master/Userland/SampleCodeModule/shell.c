#include "shell.h"
#include "C_lib.h"
#include "Usr_Syscalls.h"

char * commands[] = {"echo", "time", "regs", "clear", "set_letterSize", "game", "help"};
static int cantCommands = 7;
static int limit = 6; 


void commandLine(){
    colorPrint("$User", COLOR_GREEN);
    colorPrint(": ", COLOR_PURPLE);
}

void welcome(){
    printf("Welcome to the shell! Type 'help' to see the available commands\n");
}

void help(){
    printf("\n"); 
    printf("Available commands:\ntime - Shows the current time\n regs - Shows the registers\n  clear - Clears the screen\n set_letterSize - Changes the size of the letters\n game - Starts the game\n help - Shows the available commands\n");
}

void echo(char * str){
    printf(str);
    putChar('\n', 1);
}

void time(){
    int sec = 0;
    int min = 0;
    int hours = 0;
    sysCall_seconds(&sec);
    sysCall_minutes(&min);
    sysCall_hours(&hours);
    printf("Current time: %d:%d:%d\n", sec, min, hours);
}

void regs(){
    sysCall_writeRegs();
}

void clear(){
    sysCall_clear();
}

void set_letterSize(float size){

}

void game(){

}


void scanCommand(char * command) {
    int i = 0;
    if (command[i] == '\n') {
        return;
    }
    while (command[i] != ' ' && command[i] != '\0') {
        i++;
    }
    command[i++] = '\0';
    for (int j = 0; j < cantCommands; j++) {
        if (strcmp(command, commands[j]) == 0) {
            switch (j) {
                case 0:
                    echo(command + i);
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
                    set_letterSize(atoi(command + i));
                    break;
                case 5:
                    game();
                    break;
                case 6:
                    help();
                    break;
                default:
                    printf("Invalid command\n");
                    printf("Type 'help' to see the available commands\n");
                    break;
            }
            return;
        }
    }
    printf("Command not found\n");
}