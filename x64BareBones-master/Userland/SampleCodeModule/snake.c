

#include "include/C_lib.h"
#include "include/snake.h"
#include "include/Usr_Syscalls.h"

#include <stdint.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SQUARE_SIZE 32

#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x007fd7fa
#define DARK_BLUE 0x000000FF
#define PINK 0x00FF00FF
#define YELLOW 0x00FFFF00
#define ORANGE 0x00FFA500
#define PURPLE 0x008A2BE2
#define WHITE 0x00FFFFFF
#define LIGHT_BLUE 0x0065adc9

#define OUT_OF_BOUNDS(x, y) ((x) >= SCREEN_WIDTH || (x) <= 0 || (y) >= (SCREEN_HEIGHT) || (y) <= 100) 
#define NEAR_REWARD(x, y) ( (((x) <= rewardPos[0] + 10) && ((x) >= rewardPos[0] - 10)) && (((y) <= rewardPos[1] + 10) && ((y) >= rewardPos[1] - 10)) )


typedef struct Player{
    int x;
    int y;
    int inc_x;
    int inc_y;
    int points;
    int positions[100][2]; // Matriz para almacenar las posiciones de la serpiente
    uint64_t color;
} Player;

Player player1, player2;

static char board[SCREEN_WIDTH][SCREEN_HEIGHT] = {0}; //position table
static char reward = 1; //falg to know if there is a reward on the board

static int rewardPos[2] = {320,228 }; //reward position

static Player snakeP1 = {200, 200, 1, 0, 0, {{0}}};
static Player snakeP2 = {400, 400, 1, 0, 0, {{0}}};

void drawTrain(Player player);

void chooseColor(Player * player); 


void movePlayer(char c){
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
            if (player2.inc_y != 1 && player2.points > 0)
            {
                player2.inc_x = 0;
                player2.inc_y = -1;
            }
            break;
        case 'k':
            if (player2.inc_y != -1 && player2.points > 0)
            {
                player2.inc_x = 0;
                player2.inc_y = 1;
            }        
            break;
        case 'j':
            if(player2.inc_x != 1 && player2.points > 0){
                player2.inc_x = -1;
                player2.inc_y = 0;
            }
            break;
        case 'l':
            if(player2.inc_x != -1 && player2.points > 0){
                player2.inc_x = 1;
                player2.inc_y = 0;
            }
            break;
    }
}


void newRewardPos(){
    int x, y; 
    do{
        uint64_t ticks = sysCall_ticks();
        x = ticks % (SCREEN_WIDTH-SQUARE_SIZE);
        x = (x / SQUARE_SIZE) * SQUARE_SIZE;

        y = ticks % (SCREEN_HEIGHT);
        y = 100 + (y / SQUARE_SIZE) * SQUARE_SIZE;

    }while(OUT_OF_BOUNDS(x, y) || board[x][y] == 1);
    rewardPos[0] = x;
    rewardPos[1] = y;
    reward = 1;

}


void drawReward(){
    sysCall_putRectangle(rewardPos[0], rewardPos[1], SQUARE_SIZE, SQUARE_SIZE, RED);
}

void initializePlayer(Player * player, int nroPlayers){

    (*player).x =  5*SQUARE_SIZE;
    (*player).y = 5*SQUARE_SIZE;

    if(nroPlayers == 2){
        (*player).x = 7*SQUARE_SIZE;
        (*player).y = 7*SQUARE_SIZE;
    }

    (*player).inc_x = 1;
    (*player).inc_y = 0;
    (*player).points = 1;
    (*player).positions[0][0] = (*player).x;
    (*player).positions[0][1] = (*player).y;
}

int initialize(){
    printf("How many players? (1 or 2)\n");
    printf("Press 'q' to exit\n");
    int nro_players = 0;
    do{
        while(nro_players == 0){
            nro_players = read_char();
        }
        if(nro_players == 'q'){
            return -1;
        }
        if(nro_players != '1' && nro_players != '2'){
            printf("Invalid number of players\n");
        }
    }while(nro_players != '1' && nro_players != '2');
    nro_players -= '0';

    chooseColor(&player1);
    printf("Press 'w', 'a', 's', 'd' to move player 1\n");
    initializePlayer(&player1, 1);



    if(nro_players == 2){
        chooseColor(&player2);
        printf("Press 'i', 'j', 'k', 'l' to move player 2\n");
        initializePlayer(&player2, 2);
        wait();
    }    


    return nro_players;
}


void chooseColor(Player * player){
    printf("Chose the color for your train:\n Options: 1. Red 2. Green 3. Blue 4. Pink 5. Purple 6. Yellow 7. Orange\n");
    char color;
    do {
        color = 0; 
        while (color == 0) {
            color = read_char();
        }
        if(color == (*player).color){
            printf("Color already chosen\n");
            continue;
        }

        switch (color) {
            case '1':
                (*player).color = RED;
                break;
            case '2':
                (*player).color = GREEN;
                break;
            case '3':
                (*player).color = DARK_BLUE;
                break;
            case '4':
                (*player).color = PINK;
                break;
            case '5':
                (*player).color = PURPLE;
                break;
            case '6':
                (*player).color = YELLOW;
                break;
            case '7':
                (*player).color = ORANGE;
                break;
            case 'q':
                return;
            default:
                printf("Invalid color\n");
                break;     
        }
    } while (color != '1' && color != '2' && color != '3' && color != '4' && color != '5' && color != '6' && color != '7'); 
}

void update(Player * player){
    int tail_x = (*player).positions[(*player).points - 1][0];
    int tail_y = (*player).positions[(*player).points - 1][1];

    // Mover las posiciones de la serpiente
    for (int i = (*player).points - 1; i > 0; i--) {
        (*player).positions[i][0] = (*player).positions[i - 1][0];
        (*player).positions[i][1] = (*player).positions[i - 1][1];
    }

    // Actualizar la posición de la cabeza
    (*player).x += (*player).inc_x*SQUARE_SIZE;
    (*player).y += (*player).inc_y*SQUARE_SIZE;
    (*player).positions[0][0] = (*player).x;
    (*player).positions[0][1] = (*player).y;

    // Verificar si la serpiente ha comido una recompensa
    if (reward && NEAR_REWARD((*player).x, (*player).y)) {
        sysCall_sound(1, 500);
        (*player).points++;
        reward = 0;
    } else {
        // Poner en 0 la posición anterior de la cola
        board[tail_x][tail_y] = 0;
    }

    // Verificar si está fuera de los límites
    if (OUT_OF_BOUNDS((*player).x, (*player).y) || board[(*player).x][(*player).y] == 1 ) {
        (*player).points = -1;
    }

    // Actualizar el tablero con la nueva posición de la serpiente
    for (int i = 0; i < (*player).points; i++) {
        board[(*player).positions[i][0]][(*player).positions[i][1]] = 1;
    }
}

void putBackScreen(){
	int square = 0;
    sysCall_putRectangle(0, 0, 100,  SCREEN_WIDTH,0x00FFFFFF);
    for (int y = 100; y < SCREEN_HEIGHT; y += SQUARE_SIZE) {
        for (int x = 0; x < SCREEN_WIDTH; x += SQUARE_SIZE) {
            if (square % 2 == 0){
                sysCall_putRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, BLUE);
            }else{
                sysCall_putRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, LIGHT_BLUE);
            }   
			square++;
        }  
		square++;
	}
}

void wait(){
    uint64_t ticks = sysCall_ticks();
    while(sysCall_ticks() - ticks < 7);
}

void putPoints(int points){
    //colorPrint("Points: ", BLACK);
    sysCall_putRectangle(0, 0, 100, 100, BLACK);
    printf("Points: ");
    printInt(points);
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

    while(c!='q'){ 
        c = read_char();
        if (players == 1){
            movePlayer(c);
            update(&player1);
            wait();
            putBackScreen();
            drawTrain(player1);
            drawReward(); 
            putPoints(player1.points);            
            if(reward == 0){
                newRewardPos();
                drawReward();
            }
            if(player1.points == -1){
                clearScreen();
                if (player1.points == -1 || players == -1)
                {
                    printf("You lost\n");
                    printf("Game exited\n");
                    return; 
                }    
            }
        } else{
            movePlayer(c);
            update(&player1);
            update(&player2);
            wait();
            putBackScreen();
            drawTrain(player1);
            drawTrain(player2);
            drawReward();
            if(reward == 0){
                newRewardPos();
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
                printf("Game exited\n");
                return;
            }
        }
    }
    clearScreen();
    printf("Game exited\n");
    return;
}







void drawLocomotive(int x, int y, uint64_t color) {
    // Locomotora del tren 
    sysCall_putRectangle(x + 17, y, 11, SQUARE_SIZE-17, color); // Cuerpo de la locomotora
    sysCall_putRectangle(x, y + 11, 11, SQUARE_SIZE, color); // Frente de la locomotora
    sysCall_putRectangle(x + 3, y, 11, 6, color); // Techo de la locomotora

    // Ventanas de la locomotora
    sysCall_putRectangle(x + 20, y + 3, 6, 6, 0x00000000);  // Ventana 3
    
    // Ruedas de la locomotora
    sysCall_putRectangle(x + 6, y + 22, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 24, y + 22, 6, 6, 0x00000000);  // Rueda derecha
} 

void drawWagon(int x, int y, uint64_t color) {
    // Primer vagón del tren bala
    sysCall_putRectangle(x, y, 22, SQUARE_SIZE, color); // Cuerpo del primer vagón

    // Ventanas del primer vagón
    sysCall_putRectangle(x + 6, y + 3, 6, 6, 0x00000000);  // Ventana 1
    sysCall_putRectangle(x + 14, y + 3, 6, 6, 0x00000000); // Ventana 2
    sysCall_putRectangle(x + 22, y + 3, 6, 6, 0x00000000); // Ventana 3
    

    // Ruedas del primer vagón
    sysCall_putRectangle(x + 6, y + 22, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 24, y + 22, 6, 6, 0x00000000);  // Rueda derecha
}


void drawTrain(Player player) {
    sysCall_putRectangle(rewardPos[0], rewardPos[1],SQUARE_SIZE, SQUARE_SIZE, RED);
    drawLocomotive(player.x, player.y, player.color);
    for(int i = 1; i < player.points; i++){
        if(!OUT_OF_BOUNDS(player.positions[i][0], player.positions[i][1])){
            drawWagon(player.positions[i][0], player.positions[i][1], player.color);
        } 
    }
}
