#include"racket.h"
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

void Racket::move(SDL_Event e, int player)
{
	//if user presses key
	if(e.type == SDL_KEYDOWN)
	{
		//checks player's input and make racket move accordingly
		if(!player)//check if its player one
		{
			switch(e.key.keysym.sym)
			{
				//moves the player 1 racket
				case SDLK_UP:
					if(y > 0)
					{
						//this second condition x == 5 makes sure that key-up and ley-down
						//can only move the racket on the left side of the screen (player 1's)
						//and not the racket on the left. i'm not very proud of writing it this
						//way but this is the big flaw of inheritance. i belive 
						//there must be better ways around it but i just couldn't think of a better
						//one.
						y -= racket_speed;
						shift_collider();
					}
					break;
				case SDLK_DOWN:
					if(y < HEIGHT - h)
					{
						y += racket_speed;
						shift_collider();
					}	
					break;
			}
		}
		else
		{
			switch(e.key.keysym.sym)
			{
				//moves the player 2 racket
				case SDLK_w:
					if(y > 0)
						y -= racket_speed;
						shift_collider();
					break;
				case SDLK_s:
					if(y < HEIGHT - h)
						y += racket_speed;
						shift_collider();
					break;
			}
		}	
	}
}

void Racket::render()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, this);
}

void Racket::shift_collider()
{
	//set collider position equal to racket
	collider.x = x;
	collider.y = y;
}
