#ifndef GAME_H
#define GAME_H

#define WIDTH 20
#define HEIGHT 20
#define MAX_SANKE_LENGTH 100

typedef enum
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
} Direction;

void setup();
void draw();
void input();
void logic();

extern int game_over;
extern int score;

#endif