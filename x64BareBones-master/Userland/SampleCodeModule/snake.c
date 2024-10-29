#include "include/C_lib.h"
#include "include/snake.h"
#include "include/Usr_Syscalls.h"

#include <stdint.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SQUARE_SIZE 32

#define OUT_OF_BOUNDS(x, y) ((x) >= SCREEN_WIDTH || (x) <= 0 || (y) >= (SCREEN_HEIGHT-100) || (y) <= 0) 

Player player1, player2;

static char board[SCREEN_WIDTH][SCREEN_HEIGHT] = {0}; //position table
static char reward = 1; //falg to know if there is a reward on the board

void drawTrain(Player player);

void move2Player(char c){
    switch(c){
        case 'w':
            if(player1.inc_y != 1){
                player1.inc_x = 0;
                player1.inc_y = -1;
            }
            break;
        case 's':
            if(player1.inc_y != -1){
                player1.inc_x = 0;
                player1.inc_y = 1;
            }
            break;
        case 'a':
            if(player1.inc_x != 1){
                player1.inc_x = -1;
                player1.inc_y = 0;
            }
            break;
        case 'd':
            if(player1.inc_x != -1){
                player1.inc_x = 1;
                player1.inc_y = 0;
            }
            break;
        case 'i': //player 2
            if (player2.inc_y != 1)
            {
                player2.inc_x = 0;
                player2.inc_y = -1;
            }
            break;
        case 'k':
            if (player2.inc_y != -1)
            {
                player2.inc_x = 0;
                player2.inc_y = 1;
            }        
            break;
        case 'j':
            if(player2.inc_x != 1){
                player2.inc_x = -1;
                player2.inc_y = 0;
            }
            break;
        case 'l':
            if(player2.inc_x != -1){
                player2.inc_x = 1;
                player2.inc_y = 0;
            }
            break;
    }
}

void move1Player(char c){
    switch(c){
         case 'w':
            if(player1.inc_y != 1){
                player1.inc_x = 0;
                player1.inc_y = -1;
            }
            break;
        case 's':
            if(player1.inc_y != -1){
                player1.inc_x = 0;
                player1.inc_y = 1;
            }
            break;
        case 'a':
            if(player1.inc_x != 1){
                player1.inc_x = -1;
                player1.inc_y = 0;
            }
            break;
        case 'd':
            if(player1.inc_x != -1){
                player1.inc_x = 1;
                player1.inc_y = 0;
            }
            break;
    }
}

void drawReward(){
    uint64_t ticks = sysCall_ticks();
    int x = ticks % (SCREEN_WIDTH-SQUARE_SIZE);
    int y = ticks % (SCREEN_HEIGHT-100);
    board[x][y] = 3;
    sysCall_putRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, 0x00FF0000);
    reward = 1;
}

int initialize(){
    printf("How many players? (1 or 2)\n");
    printf("Press 'q' to exit\n");
    char nro_players=0;
    while(nro_players == 0){
        nro_players= read_char();
    }
    if(nro_players == 'q'){
        return -1;
    }
    nro_players -= '0';
    if(nro_players != 1 && nro_players != 2){
        printf("Invalid number of players\n");
        return -1;
    }

    player1.x = 200;
    player1.y = 200;
    player1.inc_x = 1;
    player1.inc_y = 0;
    player1.points = 4;
    player1.positions[0][0] = player1.x;
    player1.positions[0][1] = player1.y;

    if(nro_players > 1){
        player2.x = 400;
        player2.y = 200;
        player2.inc_x = 1;
        player2.inc_y = 0;
        player2.points = 0;
        player2.positions[0][0] = player2.x;
        player2.positions[0][1] = player2.y;
    }
    return nro_players;
    
}
/*
void searchWagon(int x, int y, char * vec){
    // Direcciones relativas para los 8 cuadrados adyacentes
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},         {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (int i = 0; i < 8; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];

        // Verificar si la nueva posición está dentro de los límites
        if (!OUT_OF_BOUNDS(new_x, new_y)) {
            if (board[new_x][new_y] == 1) { 
                vec[0] = new_x;
                vec[1] = new_y;
                return;
            }
        }
    }
    
}*/



void update(char players){
     int tail_x = player1.positions[player1.points - 1][0];
    int tail_y = player1.positions[player1.points - 1][1];

    // Mover las posiciones de la serpiente
    for (int i = player1.points - 1; i > 0; i--) {
        player1.positions[i][0] = player1.positions[i - 1][0];
        player1.positions[i][1] = player1.positions[i - 1][1];
    }

    // Actualizar la posición de la cabeza
    player1.x += player1.inc_x*SQUARE_SIZE;
    player1.y += player1.inc_y*SQUARE_SIZE;
    player1.positions[0][0] = player1.x;
    player1.positions[0][1] = player1.y;

    // Verificar si la serpiente ha comido una recompensa
    if (board[player1.x][player1.y] == 3) {
        player1.points++;
        reward = 0;
    } else {
        // Poner en 0 la posición anterior de la cola
        board[tail_x][tail_y] = 0;
    }

    // Verificar si está fuera de los límites
    if (OUT_OF_BOUNDS(player1.x, player1.y)) {
        player1.points = -1;
    }

    // Actualizar el tablero con la nueva posición de la serpiente
    for (int i = 0; i < player1.points; i++) {
        board[player1.positions[i][0]][player1.positions[i][1]] = 1;
    }



    // FALTA HACER TODO PARA 2 JUGADORES
    if(players == 2){
        player2.x += player2.inc_x;
        player2.y += player2.inc_y;

        if (board[player2.x][player2.y] == 1)
        {
            player2.points++;
            reward = 0;
        }
        
        if(OUT_OF_BOUNDS(player2.x, player2.y)){
        player2.points = -1;
        }
        board[player2.x][player2.y] = 2;
    }  
}

void putBackScreen(){
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


void wait(){
    uint64_t ticks = sysCall_ticks();
    while(sysCall_ticks() - ticks < 10);
}


void play(){
    clearScreen();
    char c=0;
    char players = initialize();
    clearScreen();
    if (players == -1)
    {
        printf("Game exited\n");
        return;
    }
    putBackScreen();
    while(c!='q'){ //DESP SE PUEDE CAMBIAR POR ESC
        c = read_char();

        if(players == 1){
            move1Player(c);
        }else{
            move2Player(c);
        }

        update(players);
        wait();
        drawTrain(player1);
        if(players == 2){
            drawTrain(player2);
        }
        if(reward == 0){
            drawReward();
        }

        

        if(player1.points == -1 || player2.points == -1){
            clearScreen();
            if (player1.points == -1)
            {
                printf("Player 1 lost\n");
            } else{
                printf("Player 2 lost\n");
            }
            
            players = initialize();
            if (players == -1)
            {
                clearScreen();
                printf("Game exited\n");
                return;
            }   
        }
    }
    clearScreen();
    printf("Game exited\n");
    return;
}


void drawLocomotive(int x, int y)  {
    // Locomotora del tren 
    sysCall_putRectangle(x + 17, y, 11, SQUARE_SIZE-17, 0x00FFFFFF); // Cuerpo de la locomotora
    sysCall_putRectangle(x, y + 11, 11, SQUARE_SIZE, 0x00FFFFFF); // Frente de la locomotora
    sysCall_putRectangle(x + 3, y, 11, 6, 0x00FFFFFF); // Techo de la locomotora

    // Ventanas de la locomotora
    sysCall_putRectangle(x + 20, y + 3, 6, 6, 0x00000000);  // Ventana 3
    
    // Ruedas de la locomotora
    sysCall_putRectangle(x + 6, y + 22, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 24, y + 22, 6, 6, 0x00000000);  // Rueda derecha
} 

void drawWagon(int x, int y) {
    // Primer vagón del tren bala
    sysCall_putRectangle(x, y, 22, SQUARE_SIZE, 0x00FFFFFF); // Cuerpo del primer vagón

    // Ventanas del primer vagón
    sysCall_putRectangle(x + 6, y + 3, 6, 6, 0x00000000);  // Ventana 1
    sysCall_putRectangle(x + 14, y + 3, 6, 6, 0x00000000); // Ventana 2
    sysCall_putRectangle(x + 22, y + 3, 6, 6, 0x00000000); // Ventana 3
    

    // Ruedas del primer vagón
    sysCall_putRectangle(x + 6, y + 22, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 24, y + 22, 6, 6, 0x00000000);  // Rueda derecha
}


void drawTrain(Player player) {
    putBackScreen();

    drawLocomotive(player.x, player.y+SQUARE_SIZE);
    for(int i = 1; i < player.points; i++){
        drawWagon(player.positions[i][0]+i*SQUARE_SIZE, player.positions[i][1]+SQUARE_SIZE);
    }
}