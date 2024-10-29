#include <stdint.h>

void drawTrain(int size, int x, int y);
void play();

typedef struct wagon{
    int x;
    int y;
    struct wagon* next;
} Wagon;

typedef struct {
    int x;
    int y;
    int inc_x;
    int inc_y;
    int points;
    Wagon* wagons; // Lista dinámica de vagones
} Player;
