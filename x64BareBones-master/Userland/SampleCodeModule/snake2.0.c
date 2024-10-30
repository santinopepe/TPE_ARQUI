/*#include "include/C_lib.h"
#include "include/snake2.0.h"
#include "include/Usr_Syscalls.h"

#define BLACK 0x00000000
#define RED 0x00FF0000
#define GREEN 0x0000FF00

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SQUARE_SIZE 32


#define IN_BOUNDS(x, y) ((x) >= 0 && (x) < SCREEN_WIDTH && (y) >= 100 && (y) < SCREEN_HEIGHT)




typedef struct Player{ 
    int x;
    int y;
    int inc_x;
    int inc_y;
    int points;
    int position[100][2]; 
}Player;

void wait();
void drawReward();
void drawTrain(Player player);
void update(Player player);
void movePlayer(char c);
void welcomeScreen();
void putBackScreen();

static Player snakeP1 = {200, 200, 1, 0, 0, {{0}}};
static Player snakeP2 = {400, 400, 1, 0, 0, {{0}}};

static char board[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};
static int reward = 1;
static int rewardPos[2] = {0};

static char players = 0; //  0 = no players, 1 = 1 player, 2 = 2 players

void welcomeScreen(){
    printf("Welcome to the snake game!\n");
    printf("Press 'q' to exit\n");
    printf("How many players? (1 or 2)\n");
    do{
        players = read_char();
        while(players == 0){
            players = read_char();
        }
        if(players == 'q'){
            return;
        }
        if(players != '1' && players != '2'){
            printf("Invalid number of players\n");
        }
    } while(players != '1' && players != '2');
    clearScreen();
}




void movePlayer(char c){
    switch (c)
    {
    case 'w':
        if(snakeP1.inc_y != 1){
            snakeP1.inc_x = 0;
            snakeP1.inc_y = -1;
        }
        break;
    case 's':
        if(snakeP1.inc_y != -1){
            snakeP1.inc_x = 0;
            snakeP1.inc_y = 1;
        }
        break;
    case 'a':
        if(snakeP1.inc_x != 1){
            snakeP1.inc_x = -1;
            snakeP1.inc_y = 0;
        }
        break;
    case 'd':
        if(snakeP1.inc_x != -1){
            snakeP1.inc_x = 1;
            snakeP1.inc_y = 0;
        }
        break;
    case 'i':
        if(snakeP2.inc_y != 1 && snakeP2.points > 0){
            snakeP2.inc_x = 0;
            snakeP2.inc_y = -1;
        }
        break;
    case 'k':
        if(snakeP2.inc_y != -1 && snakeP2.points > 0){
            snakeP2.inc_x = 0;
            snakeP2.inc_y = 1;
        }
        break;
    case 'j':
        if(snakeP2.inc_x != 1 && snakeP2.points > 0){
            snakeP2.inc_x = -1;
            snakeP2.inc_y = 0;
        }
        break;
    case 'l':
        if(snakeP2.inc_x != -1 && snakeP2.points > 0){
            snakeP2.inc_x = 1;
            snakeP2.inc_y = 0;
        }
        break;
    default:
        break;
    }
}

void update(Player player){

    for(int i = player.points; i > 0; i--){
        player.position[i][0] = player.position[i-1][0];
        player.position[i][1] = player.position[i-1][1];
        board[player.position[i][0]][player.position[i][1]] = 1;
    }  

    player.position[0][0] += player.inc_x * SQUARE_SIZE;
    player.position[0][1] += player.inc_y * SQUARE_SIZE;

    board[player.position[0][0]][player.position[0][1]] = 1;

    if(!IN_BOUNDS(player.position[0][0], player.position[0][1]) || board[player.position[0][0]][player.position[0][1]] == 1){
        player.points = -1;
        return; 
    }

    if(reward && player.position[0][0] == rewardPos[0] && player.position[0][1] == rewardPos[1]){
        reward = 0;
        player.points++;
    } else {
        board[player.position[player.points][0]][player.position[player.points][1]] = 0;
    }

    return;
}

void drawTrain(Player player, uint64_t color){
    for(int i = 0; i < player.points; i++){
        sysCall_putRectangle(player.position[i][0], player.position[i][1], SQUARE_SIZE, SQUARE_SIZE, color);
    }

void drawReward(){
    uint64_t ticks = sysCall_ticks();
    int x = ticks % (SCREEN_WIDTH-SQUARE_SIZE);
    int y = ticks % (SCREEN_HEIGHT-100);
    rewardPos[0] = x;
    rewardPos[1] = y;
    sysCall_putRectangle(x, y, SQUARE_SIZE, SQUARE_SIZE, 0x00FF0000);
    reward = 1;
}

void wait(){
    uint64_t ticks = sysCall_ticks();
    while(sysCall_ticks() - ticks < 10);
}


void play(){
    welcomeScreen(); 
    putBackScreen();
    if(players == '1'){
        snakeP1.position[0][0] = 200;
        snakeP1.position[0][1] = 200;
        while(1){
            char c = read_char();
            if(c == 'q'){
                return;
            }
            update(snakeP1);
            if(snakeP1.points == -1){
                return;
            }
            movePlayer(c);
            wait();
            drawTrain(snakeP1);
            if(reward == 0){
                drawReward();
            }
        }

    } else if(players == '2'){

    }
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
    sysCall_putRectangle(rewardPos[0], rewardPos[1],SQUARE_SIZE, SQUARE_SIZE, 0x00FF0000);
    drawLocomotive(player.position[0][0], player.position[0][1]);
    for(int i = 1; i < player.points; i++){
        drawWagon(player.position[i][0], player.position[i][1]);
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

}*/