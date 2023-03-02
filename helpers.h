#ifndef helpers_h
#define helpers_h

#include <SDL2/SDL.h>
#include <iostream>

//height and width of the window
#define WIDTH 800
#define HEIGHT 600
const int BALL_HEIGHT = 10;
const int BALL_WIDTH = 10;
const int ROCKET_HEIGHT = 70;
const int ROCKET_WIDTH = 10;

//initialize the SDL2
int init();
void close();
//int check_collision(SDL_Rect a,SDL_Rect b);
//creates game over
void game_over(int *flag);
void restart_game(int *flag);

#endif
