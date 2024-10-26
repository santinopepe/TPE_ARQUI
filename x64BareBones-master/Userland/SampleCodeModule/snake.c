#include "include/C_lib.h"
#include "include/snake.h"
#include "include/Usr_Syscalls.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SQUARE_SIZE 32

#define OUT_OF_BOUNDS(x, y) ((x) >= SCREEN_WIDTH || (x) <= 0 || (y) >= (SCREEN_HEIGHT-100) || (y) <= 0) 

Player player1, player2;

void move2Player(){
    char c = read_char();
    switch(c){
        case 'w':
            player1.inc_x = 0;
            player1.inc_y = -1;
            break;
        case 's':
            player1.inc_x = 0;
            player1.inc_y = 1;
            break;
        case 'a':
            player1.inc_x = -1;
            player1.inc_y = 0;
            break;
        case 'd':
            player1.inc_x = 1;
            player1.inc_y = 0;
            break;
        case 'i': //player 2
            player2.inc_x = 0;
            player2.inc_y = -1;
            break;
        case 'k':
            player2.inc_x = 0;
            player2.inc_y = 1;
            break;
        case 'j':
            player2.inc_x = -1;
            player2.inc_y = 0;
            break;
        case 'l':
            player2.inc_x = 1;
            player2.inc_y = 0;
            break;
    }
}

void move1Player(){
    char c = read_char();
    switch(c){
        case 'w':
            player1.inc_x = 0;
            player1.inc_y = -1;
            break;
        case 's':
            player1.inc_x = 0;
            player1.inc_y = 1;
            break;
        case 'a':
            player1.inc_x = -1;
            player1.inc_y = 0;
            break;
        case 'd':
            player1.inc_x = 1;
            player1.inc_y = 0;
            break;
    }
}

int initialize(){
    printf("How many players? (1 or 2)\n");
    char nro_players='0';
    while(nro_players!= '0'){
        nro_players= read_char();
    }
    if(nro_players != 1 || nro_players != 2){
        printf("Invalid number of players\n");
        return -1;
    }

    player1.x = 10;
    player1.y = 10;
    player1.inc_x = 1;
    player1.inc_y = 0;
    player1.points = 0;

    if(nro_players > 1){
        player2.x = 20;
        player2.y = 20;
        player2.inc_x = 1;
        player2.inc_y = 0;
        player2.points = 0;
    }
    return nro_players;
    
}

void update(){
    player1.x += player1.inc_x;
    player1.y += player1.inc_y;

    player2.x += player2.inc_x;
    player2.y += player2.inc_y;

    if(OUT_OF_BOUNDS(player1.x, player1.y)){
        player1.points = -1;
    }

    if(OUT_OF_BOUNDS(player2.x, player2.y)){
        player2.points = -1;
    }
}

void putBackScreen(){//chequear
	int square = 0;
    sysCall_putRectangle(0, 0, 100,  SCREEN_WIDTH,0x00FFFFFF);
    for (int y = 100; y < SCREEN_HEIGHT; y += SQUARE_SIZE) {
        for (int x = 0; x < SCREEN_WIDTH; x += SQUARE_SIZE) {
            if (square % 2 == 0){
                sysCall_putRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, 0x007fd7fa);
            }else{
                sysCall_putRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, 0x0065adc9);
            }   
			square++;
        }    
		square++;
	}
}

void play(){
    clearScreen();
    char c=0;
    char players = initialize();
    putBackScreen();
    while(c!='q'){ //DESP SE PUEDE CAMBIAR POR ESC
        c = read_char();

        if(players == 1){
            move1Player();
        }else{
            move2Player();
        }

        update();

        if(player1.points == -1){
            printf("Player 1 lost\n");
            initialize();
        }
        if(player2.points == -1){
            printf("Player 2 lost\n");
            initialize();   
        }
    }
}


void drawLocomotive(int x, int y) {
    // Locomotora del tren 
    sysCall_putRectangle(x + 17, y, 11, 22, 0x00FFFFFF); // Cuerpo de la locomotora
    sysCall_putRectangle(x, y + 11, 11, 45, 0x00FFFFFF); // Frente de la locomotora
    sysCall_putRectangle(x + 3, y, 11, 6, 0x00FFFFFF); // Techo de la locomotora

    // Ventanas de la locomotora
    sysCall_putRectangle(x + 22, y + 3, 6, 6, 0x00000000);  // Ventana 3
    
    // Ruedas de la locomotora
    sysCall_putRectangle(x + 6, y + 22, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 28, y + 22, 6, 6, 0x00000000);  // Rueda derecha
} 

void drawWagon(int x, int y) {
    // Primer vagón del tren bala
    sysCall_putRectangle(x, y, 22, 45, 0x00FFFFFF); // Cuerpo del primer vagón

    // Ventanas del primer vagón
    sysCall_putRectangle(x + 6, y + 3, 6, 6, 0x00000000);  // Ventana 1
    sysCall_putRectangle(x + 14, y + 3, 6, 6, 0x00000000); // Ventana 2
    sysCall_putRectangle(x + 22, y + 3, 6, 6, 0x00000000); // Ventana 3
    

    // Ruedas del primer vagón
    sysCall_putRectangle(x + 6, y + 22, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 28, y + 22, 6, 6, 0x00000000);  // Rueda derecha
}


void drawTrain(int size, int x, int y) {
    putBackScreen();
  
    drawLocomotive(x, y+SQUARE_SIZE);
    for(int i = 1; i <= size; i++){
        drawWagon(x+i*SQUARE_SIZE, y+SQUARE_SIZE);
    }
}