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
    printf("Available commands: \n\ntime - Shows the current time\n\nregs - Shows the registers\n\nclear - Clears the screen\n\nset_letterSize - Changes the size of the letters\n\ngame - Starts the game\n\nhelp - Shows the available commands\n\n");
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
    // Encontrar el final del comando
    while (command[i] != ' ' && command[i] != '\0' && command[i] != '\n') {
        i++;
    }
    // Separar el comando de sus argumentos
    char *args = 0;
    if (command[i] == ' ') {
        command[i] = '\0';
        args = command + i + 1;
    } else {
        command[i] = '\0';
    }

    // Buscar el comando en la lista de comandos
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
                    if (args != 0) {
                        set_letterSize(atoi(args));
                    } else {
                        printf("Error: Missing argument for set_letterSize\n");
                    }
                    break;
                case 5:
                    game();
                    break;
                case 6:
                    help();
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