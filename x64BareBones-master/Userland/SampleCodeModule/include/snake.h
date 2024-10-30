#include <stdint.h>

void play();


typedef struct {
    int x;
    int y;
    int inc_x;
    int inc_y;
    int points;
    int positions[100][2]; // Matriz para almacenar las posiciones de la serpiente
} Player;
