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
    puts("Welcome to the shell! Type 'help' to see the available commands");
}

void help(){
    printf("\n"); 
    puts("Available commands: ");
    puts("echo <string>: prints the string ");
    puts("time: prints the current time ");
    puts("regs: prints the registers ");
    puts("clear: clears the screen ");
    puts("set_letterSize <size>: sets the size of the letters ");
    puts("game: starts a game ");
    printf("\n");
}

void echo(char * str){
    puts(str);
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


void scanCommand(char * command){
    char * param = 0; // Initialize param to NULL
    int j = 0;
    int i = 0;
    if(command[i] == '\n'){
        return;
    }
    while(command[i] != ' '){
        i++;
    }
    command[i++] = '\0';
    while (command[i] != '\0' && command[i] != '\n'){ // Change condition to check for '\n'
        param[j] = command[i];
        i++;
        j++;
    }
    param[j] = '\0'; // Add null terminator to param
    
    for(int i = 0; i < cantCommands; i++){
        if(strcmp(command, commands[i]) == 0){
            switch (i)
            {
            case 0:
                echo(param);
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
                set_letterSize(atoi(param));
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
}