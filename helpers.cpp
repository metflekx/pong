#include <SDL2/SDL.h>
#include <iostream>
#include "helpers.h"

//creates ptr to a sdl_window
SDL_Window *window = NULL;
//creates a ptr to a SDL_Renderer
SDL_Renderer *renderer = NULL;
//ball and racket's speed 
int ball_speed = 7;
int racket_speed = 50;
//if game is freezed or not
int freeze = 0;
//player one and two score counter
int p1_score = 0;
int p2_score = 0;

void game_over(int *flag)
{
	*flag = 1;
}
void restart_game(int *flag)
{
	*flag = 0;
}

void close()
{
    printf("closing\n");
    //desstroy window
    window = NULL;
    SDL_DestroyWindow(window);
    //destroy renderer
    SDL_DestroyRenderer(renderer);
    //clean up theinitialized subsystems
    SDL_Quit();
}

int init()
{
    //sets the functions flag
    int success = 1;
    //init sdl and checks if sdl could init successfully
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
	    printf("init failed\n");
            success = 0;
    }
    
    //creates window
    window = SDL_CreateWindow("pong",SDL_WINDOWPOS_UNDEFINED,
	    SDL_WINDOWPOS_UNDEFINED,
	    WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
	    printf("window could not be created\n");
	    success = 0;
    }
    
    
    //creates renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
	    printf("renderer could not be created\n");
	    success = 0;
}
//return flag
return success;
}

