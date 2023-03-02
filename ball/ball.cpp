#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include"ball.h"

void Ball::move(SDL_Rect p1_collider,SDL_Rect p2_collider, int *ballv)
{
	//increse/decreases the x value of the ball
	if(xpos)
	{
		x += *ballv;
		shift_collider();//update collider's position each time ball moves
	}
	else
	{
		x -= *ballv;
		shift_collider();
	}
	//sets whether the x value of the ball should be increasing or decreasing
	if(check_collision(p1_collider, collider))
	{
		xpos = 1;
		*ballv += 1;
	}
	if(check_collision(p2_collider, collider))
	{
		*ballv += 1;
		xpos = 0;
	}
	if(x < 0)
	{
		game_over(&freeze);
		//creates 10*10 ball in the middle of screen
		x = WIDTH/2;
		y = HEIGHT/2;
		w = 10;
		h = 10;
		//sets collider to be just as big as ball
		collider.w = w;
		collider.h = h;

		//increments player2 score
		p2_score ++;
	}
	if(x > WIDTH)
	{
		game_over(&freeze);
		//creates 10*10 ball in the middle of screen
		x = WIDTH/2;
		y = HEIGHT/2;
		w = 10;
		h = 10;
		//sets collider to be just as big as ball
		collider.w = w;
		collider.h = h;

		p1_score ++;
	}

	//copy same motion along the y axis
	if(ypos)
	{
		y += ball_speed;
		shift_collider();
	}
	else
	{
		y -= ball_speed;
		shift_collider();
	}
	if(y >= HEIGHT)//+ goes down and - goes up :)
		ypos = 0;
	else if(y <= 0)
		ypos = 1;
}

void Ball::render()
{
	//draws ball on the screen
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, this);
}

int Ball::check_collision(SDL_Rect a, SDL_Rect b)
{
    //the sides of the rectangles
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;
    //calculates the sides of rect_a
    left_a = a.x;
    right_a = a.x + a.w;
    top_a = a.y;
    bottom_a = a.y + a.h;
    //calculates the sides of rect_b
    left_b = b.x;
    right_b = b.x + b.w;
    top_b = b.y;
    bottom_b = b.y + b.h;

    //if any of the sides from  A are outside of B
    if (bottom_a <= top_b || top_a >= bottom_b ||
        right_a <= left_b || left_a >= right_b)
        return 0;
    //if none of the sides from a are outside of b
    return 1;
}

void Ball::shift_collider()
{
	//updates ball's collider position
	collider.x = x;
	collider.y = y;
}

