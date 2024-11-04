

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
#define SILVER 0xC0C0C0

#define OUT_OF_BOUNDS(x, y) ((x) >= SCREEN_WIDTH || (x) <= 0 || (y) >= (SCREEN_HEIGHT) || (y) <= 100) 
#define NEAR_REWARD(x, y) ( (((x) <= rewardPos[0] + 10) && ((x) >= rewardPos[0] - 10)) && (((y) <= rewardPos[1] + 10) && ((y) >= rewardPos[1] - 10)) )

#define MAX_WAGONS 100

typedef struct Player{
    int x; //X coordinate of the head of the train
    int y; //Y coordinate of the head of the train
    int inc_x;
    int inc_y;
    int points; //Amounts of points the player has (Also the amount of wagons)
    int positions[MAX_WAGONS][2]; // Matrix to store the positions of the wagons
    uint64_t color; //Color of the train
    char lost; //Flag to know if the player lost
} Player;

Player player1, player2;

static char board[SCREEN_WIDTH][SCREEN_HEIGHT] = {0}; //positions of the players on the board
static char reward = 1; //flag to know if the reward is on the screen
static int difficulty = 7; //difficulty of the game
static int rewardPos[2] = {320,228}; //reward position

/**
 * @brief Draws the train of the player
 * @param player The player to draw
 * @return void
*/
static void  drawTrain(Player player);

/**
 * @brief Draws the reward
 * @param void
 * @return void
*/
static void drawReward();

/**
 * @brief Updates the game state
 * @param player The player to update
 * @return void
*/
static void update(Player * player);

/**
 * @brief Moves the player
 * @param c The key pressed
 * @return void
*/
static void movePlayer(char c);

/**
 * @brief Puts the back screen
 * @param void
 * @return void
*/
static void putBackScreen();

/**
 * @brief Waits, so the player can play the game (Without this the game is too fast)
 * @param void
 * @return void
*/
static void wait();

/**
 * @brief Draws the points of the player
 * @param player The player to draw
 * @return void
*/
static void drawPoints(int player);

/**
 * @brief Initializes the a player
 * @param player The player to initialize
 * @param nroPlayers The number of players in the game
 * @return void
*/
static void initializePlayer(Player * player, int nroPlayers);

/**
 * @brief Initializes the game
 * @param void
 * @return int The number of players
*/

static int initialize();

/**
 * @brief Generates a new position for the reward
 * @param void
 * @return void
*/
static void newRewardPos();

/**
 * @brief Chooses the color of the player
 * @param player The player to choose the color
 * @param playerNumber The number of the players
 * @return void
*/
static void chooseColor(Player * player, int playerNumber); 
/**
 * @brief Chooses the difficulty of the game
 * @param void
 * @return void
*/
static void chooseDificulty();

/**
 * @brief Initializes the vector of the player
 * @param player The player to initialize
 * @return void
*/
static void initializeVector(Player * player);


/**
 * @brief Cleans the board, we created this function as sometimes the board is not cleaned correctly
 * @param void
 * @return void
*/
static void cleanBoard(); 


/**
 * @brief This group of functions draw the different parts of the train, on different directions
 * @param x The x position of the train
 * @param y The y position of the train
 * @param color The color of the train
 * @return void
*/

static void drawLocomotiveLeft(int x, int y, uint64_t color);
static void drawLocomotiveRight(int x, int y, uint64_t color);
static void drawLocomotiveVerical(int x, int y, uint64_t color);
static void drawLocomotiveDown(int x, int y, uint64_t color); 
static void drawVericalWagon(int x, int y, uint64_t color); 
static void drawWagon(int x, int y, uint64_t color);




static void movePlayer(char c){
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



static void newRewardPos(){

    int x, y; 
    
        uint64_t ticks = sysCall_ticks();
        x = ticks % (SCREEN_WIDTH-SQUARE_SIZE);
        x = (x / SQUARE_SIZE) * SQUARE_SIZE;

        y = ticks % (SCREEN_HEIGHT);
        y = 100 + (y / SQUARE_SIZE) * SQUARE_SIZE;
    
        //This conditions makes is so the game doesn't halt while is looking for a new position
        if((OUT_OF_BOUNDS(x, y) || board[x][y] == 1) && board[5*SQUARE_SIZE][7*SQUARE_SIZE] != 1){
            x = 5*SQUARE_SIZE;
            y = 7*SQUARE_SIZE;
            
        } else if ((OUT_OF_BOUNDS(x, y) || board[x][y] == 1) && board[7*SQUARE_SIZE][5*SQUARE_SIZE] != 1){
            x = 7*SQUARE_SIZE;
            y = 5*SQUARE_SIZE;
        }else{ //This will halt the game until it finds a new position, it will only happen if the board is almost full full
            do{
                uint64_t ticks = sysCall_ticks();
                x = ticks % (SCREEN_WIDTH-SQUARE_SIZE);
                x = (x / SQUARE_SIZE) * SQUARE_SIZE;

                y = ticks % (SCREEN_HEIGHT);
                y = 100 + (y / SQUARE_SIZE) * SQUARE_SIZE;
            }while (OUT_OF_BOUNDS(x, y) || board[x][y] == 1);
        }

    rewardPos[0] = x;
    rewardPos[1] = y;
    reward = 1;

}


static void drawReward(){
    sysCall_putRectangle(rewardPos[0], rewardPos[1], SQUARE_SIZE, SQUARE_SIZE, RED);
}

static void initializeVector(Player * player){
    for (int i = 0; i < MAX_WAGONS; i++) {
        (*player).positions[i][0] = 0;
        (*player).positions[i][1] = 0;
    }
}

static void initializePlayer(Player * player, int nroPlayers){

    (*player).x =  5*SQUARE_SIZE;
    (*player).y = 5*SQUARE_SIZE;

    if(nroPlayers == 2){
        (*player).x = 7*SQUARE_SIZE;
        (*player).y = 7*SQUARE_SIZE;
    }

    (*player).inc_x = 1;
    (*player).inc_y = 0;
    (*player).points = 1;
    (*player).lost = 0;
    initializeVector(player);
    (*player).positions[0][0] = (*player).x;
    (*player).positions[0][1] = (*player).y;
}

static int initialize(){
    printf("How many players? (1 or 2)\n");
    printf("Press 'q' to exit\n");
    int nro_players = 0;
    do{
        while(nro_players == 0){
            nro_players = read_char();
        }
        if(nro_players != '1' && nro_players != '2'){
            printf("Invalid number of players\n");
            nro_players = 0;
        }
        if(nro_players == 'q'){
            return -1;
        }
    }while(nro_players != '1' && nro_players != '2');
    nro_players -= '0';

    chooseColor(&player1,1);
    printf("Press 'w', 'a', 's', 'd' to move player 1\n");
    initializePlayer(&player1, 1);



    if(nro_players == 2){
        chooseColor(&player2, 2);
        printf("Press 'i', 'j', 'k', 'l' to move player 2\n");
        initializePlayer(&player2, 2);
        wait();
    }    

    cleanBoard();
    chooseDificulty();
    return nro_players;
}

static void chooseDificulty(){
    printf("Choose the difficulty of the game:\n Options: 1. Easy 2. Medium 3. Hard\n");
    char dif;
    do {
        dif = 0; 
        while (dif == 0) {
            dif = read_char();
        }
        switch (dif) {
            case '1':
                difficulty = 5;
                break;
            case '2':
                difficulty = 4;
                break;
            case '3':
                difficulty = 2;
                break;
            case 'q':
                return;
            default:
                printf("Invalid difficulty\n");
                break;     
        }
    } while (dif != '1' && dif != '2' && dif != '3'); 
}


static void chooseColor(Player * player, int player_number){
    printf("Choose the color for your train:\n Options: 1. Red 2. Green 3. Blue 4. Pink 5. Purple 6. Yellow 7. Orange\n");
    char color;
    do {
        color = 0; 
        while (color == 0) {
            color = read_char();
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

        //Check if the color is already choosen
        if(player->color == player1.color && player_number == 2){
            printf("Color already chosen\n");
            color = 0;
        }

    } while (color != '1' && color != '2' && color != '3' && color != '4' && color != '5' && color != '6' && color != '7'); 
}

static void update(Player * player){
    int tail_x = (*player).positions[(*player).points - 1][0];
    int tail_y = (*player).positions[(*player).points - 1][1];

    // Move the wagons
    for (int i = (*player).points - 1; i > 0; i--) {
        (*player).positions[i][0] = (*player).positions[i - 1][0];
        (*player).positions[i][1] = (*player).positions[i - 1][1];
    }

    // Update the head of the train
    (*player).x += (*player).inc_x*SQUARE_SIZE;
    (*player).y += (*player).inc_y*SQUARE_SIZE;
    (*player).positions[0][0] = (*player).x;
    (*player).positions[0][1] = (*player).y;

    // Check if the player got the reward
    if (reward && NEAR_REWARD((*player).x, (*player).y)) {
        sysCall_sound(1, 500);
        (*player).points++;
        reward = 0;
    } 
        // Put on the board the tail of the train 0, as it is not part of the train anymore
        board[tail_x][tail_y] = 0;
    

    // Check if the player lost
    if (OUT_OF_BOUNDS((*player).x, (*player).y) || board[(*player).x][(*player).y] == 1 ) {
        (*player).lost =1;
    }

    // Put on the board the new position of the player
    for (int i = 0; i < (*player).points; i++) {
        board[(*player).positions[i][0]][(*player).positions[i][1]] = 1;
    }
}

static void putBackScreen(){
	int square = 0;
    sysCall_putRectangle(0, 0, 100,  SCREEN_WIDTH, SILVER);
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

static void wait(){
    uint64_t ticks = sysCall_ticks();
    while(sysCall_ticks() - ticks < difficulty);
}

static void drawPoints(int player){
    if (player == 1){
        sysCall_setCursor(0, 0);
        printf("                Player 1\n");
        printf("                Points: %d", player1.points-1);
    }else if (player == 2){
       sysCall_setCursor(0, 0);
        printf("                Player 1                Player 2\n");
        printf("                Points: %d              Points: %d", player1.points-1, player2.points-1);
    } 
    
}

void play(){
    sysCall_setSize(1);
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

            drawPoints(1);   

            if(reward == 0){
                newRewardPos();
                drawReward();
            }
            if(player1.lost == 1){
                clearScreen();
                if (player1.lost == 1 || players == -1)
                {
                    printf("You lost\n");
                    printf("Points: %d\n", player1.points-1);
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
            drawPoints(2);
            drawReward();
            if(reward == 0){
                newRewardPos();
                drawReward();
            }
            if(player1.lost == 1 || player2.lost == 1){
                clearScreen();
                if (player1.lost == 1)
                {
                    printf("Player 1 lost\n");
                } else{
                    printf("Player 2 lost\n");
                }
                printf("Player 1 points : %d\n", player1.points-1);
                printf("Player 2 points : %d\n", player2.points-1);
                printf("Game exited\n");
                return;
            }
        }
    }
    clearScreen();
    printf("Game exited\n");
    return;
}


static void cleanBoard(){
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            board[i][j] = 0;
        }
    }
}

static void drawLocomotiveLeft(int x, int y, uint64_t color) {
    // Locomotive of the train
    sysCall_putRectangle(x + 17, y, 11, SQUARE_SIZE-17, color); // Cuerpo de la locomotora
    sysCall_putRectangle(x, y + 11, 11, SQUARE_SIZE, color); // Frente de la locomotora
    sysCall_putRectangle(x + 3, y, 11, 6, color); // Techo de la locomotora

    // Windows of the locomotive
    sysCall_putRectangle(x + 20, y + 3, 6, 6, 0x00000000);  // Ventana 3
    
    // Wheels of the locomotive
    sysCall_putRectangle(x + 6, y + 22, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 24, y + 22, 6, 6, 0x00000000);  // Rueda derecha
} 

static void drawLocomotiveRight(int x, int y, uint64_t color) {
    // Locomotive of the train
    sysCall_putRectangle(x, y, 11, SQUARE_SIZE - 17, color); // Cuerpo
    sysCall_putRectangle(x , y + 11, 11, SQUARE_SIZE, color); // Frente
    sysCall_putRectangle(x + 22, y, 11, 6, color); // Techo

    // Windows of the locomotive
    sysCall_putRectangle(x + 7, y + 3, 6, 6, 0x00000000); // Ventana

    // Wheels of the locomotive
    sysCall_putRectangle(x + 6, y + 22, 6, 6, 0x00000000); // Rueda izquierda
    sysCall_putRectangle(x + 24, y + 22, 6, 6, 0x00000000); // Rueda derecha
}


static void drawLocomotiveVerical(int x, int y, uint64_t color){
    // Locomotive of the train
    sysCall_putRectangle(x, y + 17, SQUARE_SIZE - 17, 11, color); // Cuerpo de la locomotora
    sysCall_putRectangle(x + 11, y, SQUARE_SIZE, 11, color); // Frente de la locomotora
    sysCall_putRectangle(x, y + 3, 6, 11, color); // Techo de la locomotora

    // Windows of the locomotive
    sysCall_putRectangle(x + 3, y + 20, 6, 6, 0x00000000);  // Ventana 3
    
    // Wheels of the locomotive
    sysCall_putRectangle(x + 22, y + 6, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 22, y + 24, 6, 6, 0x00000000);  // Rueda derecha
}

static void drawLocomotiveDown(int x, int y, uint64_t color){
    // Locomotive of the train
    sysCall_putRectangle(x, y, SQUARE_SIZE - 17, 11, color); // Cuerpo de la locomotora
    sysCall_putRectangle(x+11, y, SQUARE_SIZE, 11, color); // Frente de la locomotora
    sysCall_putRectangle(x, y + 22, 6, 11, color); // Techo de la locomotora

    // Windows of the locomotive
    sysCall_putRectangle(x + 3, y + 5, 6, 6, 0x00000000);  // Ventana 3
    
    // Wheels of the locomotive
    sysCall_putRectangle(x + 22, y + 6, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 22, y + 24, 6, 6, 0x00000000);  // Rueda derecha
}


static void drawWagon(int x, int y, uint64_t color) {

    // Wagon
    sysCall_putRectangle(x, y, 22, SQUARE_SIZE, color); // Cuerpo del primer vagón

    // Windows of the wagon
    sysCall_putRectangle(x + 6, y + 3, 6, 6, 0x00000000);  // Ventana 1
    sysCall_putRectangle(x + 14, y + 3, 6, 6, 0x00000000); // Ventana 2
    sysCall_putRectangle(x + 22, y + 3, 6, 6, 0x00000000); // Ventana 3
    

    // Wheels of the wagon
    sysCall_putRectangle(x + 6, y + 22, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 24, y + 22, 6, 6, 0x00000000);  // Rueda derecha
}

static void drawVericalWagon(int x, int y, uint64_t color) {
    // Wagon (On a vertical position)
    sysCall_putRectangle(x, y, SQUARE_SIZE, 22, color); // Cuerpo del primer vagón

    // Windows of the wagon
    sysCall_putRectangle(x + 3, y + 6, 6, 6, 0x00000000);  // Ventana 1
    sysCall_putRectangle(x + 3, y + 14, 6, 6, 0x00000000); // Ventana 2
    sysCall_putRectangle(x + 3, y + 22, 6, 6, 0x00000000); // Ventana 3

    // Wheels of the wagon
    sysCall_putRectangle(x + 22, y + 6, 6, 6, 0x00000000);  // Rueda izquierda
    sysCall_putRectangle(x + 22, y + 24, 6, 6, 0x00000000);  // Rueda derecha
    
}


static void drawTrain(Player player) {
    sysCall_putRectangle(rewardPos[0], rewardPos[1],SQUARE_SIZE, SQUARE_SIZE, RED);
    if (player.inc_x == 0 && player.inc_y == -1){
        
        drawLocomotiveVerical(player.x, player.y, player.color);
    }else if (player.inc_y == 0 && player.inc_x == -1){ 
        
        drawLocomotiveLeft(player.x, player.y, player.color);
    } else if(player.inc_x == 1 && player.inc_y == 0){
       
        drawLocomotiveRight(player.x, player.y, player.color);
    } else {
        
        drawLocomotiveDown(player.x, player.y, player.color);
    }
    
    
    for(int i = 1; i < player.points; i++){
        if(!OUT_OF_BOUNDS(player.positions[i][0], player.positions[i][1])){
            if (player.inc_x == 0)
            {
                drawVericalWagon(player.positions[i][0], player.positions[i][1], player.color);
            }else{
                drawWagon(player.positions[i][0], player.positions[i][1], player.color);
            }   
        }
    }
}


