/*
	hellooo people . unlike the previous tutorial(snake game)
	this program is object oriented.
	a lot of the structure is given to us by the SDL_library
	for example the SDL_Rect is just a class which have a height
	and width value.in this program we make classes which 
	inherites from these classes and add a new functionality
	to them.
	LETS GOOOOOOOO
*/

#include<iostream>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include"pong.h"

//creates a class which inherits SDL_Rect public members
class Racket:public SDL_Rect{
	public:
		//handle those events which can effect racket
		void move(SDL_Event e, int player);
		//draws the racket on the screen
		void render();
		//an invisible rectangle which it's area and position
		//are always equal to racket's area and position
		SDL_Rect collider;
		//updates the colliders position
		void shift_collider();
};

class Ball:public SDL_Rect{
	public:
		void move(SDL_Rect p1_collider, SDL_Rect p2_collider, int *ballv);
		//collider for this ball
		//draws ball
		void render();
		//check collision
		int check_collision(SDL_Rect a, SDL_Rect b);
		//moves the ball
		SDL_Rect collider;
		void shift_collider();

	private:
		int xpos = 0;
		//initializing binary flags, these to variables determine
		//wheather ball should move positive or negative along x-axis
		//same for the yaxis
		int ypos = 0;
};

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

//creates a SDL_Rect to store ball later
Ball ball;
//creates two Racket to store rackets for each player
Racket racket;
Racket racket2;

int main()
{
	//starts up SDL
	if(!init())
	{
		printf("Failed to initialize.\n");
		close();
		return 1;
	}
  //creates 10*10 ball in the middle of screen
	ball.x = WIDTH/2;
	ball.y = HEIGHT/2;
	ball.w = BALL_WIDTH;
	ball.h = BALL_HEIGHT; 
	//sets collider to be just as big as ball
	ball.collider.w = ball.w;
	ball.collider.h = ball.h;
	//creates racket at left side of the screen
	racket.x = 5;
	racket.y = HEIGHT/2;
	racket.w = ROCKET_WIDTH; 
	racket.h = ROCKET_HEIGHT;
	racket.collider.w = racket.w + 5;
	racket.collider.h = racket.h;
	//creates a racket at the right of the screen
	racket2.x = WIDTH - 14;
	racket2.y = HEIGHT/2; // just initial height
	racket2.w = ROCKET_WIDTH;
	racket2.h = ROCKET_HEIGHT;
	racket2.collider.w = racket2.w + 5;
	racket2.collider.h = racket2.h;
	//=========
	//GAME LOOP
	//=========
	//game loop flag
	int quit = 0;	
	//binary(boolean) flag to freeze the game
	//if game_over() is called freezes the game by setting this to true
	//int *freeze = 0;//initialy false
	//event 
	SDL_Event e;
	//while application is running
	while(!quit)
	{
		if(p1_score >= 5)
			{
				printf("PLAYER 1 WINS\n");
				quit = 1;
			}
			else if(p2_score >= 5)
			{
				printf("PLAYER 2 WINS\n");
				quit = 1;
			}

		if(!freeze)//if game is not freezed
		{
			
			//handles events on quene
			while(SDL_PollEvent(&e) != 0)
			{
				//stops game loop if user tries to quit
				if(e.type == SDL_QUIT){quit = 1;}
				switch(e.key.keysym.sym)
				{
					case SDLK_t:
						game_over(&freeze);
						break;
				}
				//moves the racket 
				racket.move(e, 0);//0 represents player1
				racket2.move(e, 1);//1 represents player2
			}
			//moves the ball
			ball.move(racket.collider, racket2.collider, &ball_speed);
			//====
			//DRAW
			//====
			//clear screen
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(renderer);
			//draws the ball
			ball.render();
			//draws rackets
			racket.render();
			racket2.render();
			//update screen
			SDL_RenderPresent( renderer );
			//adds delay
			SDL_Delay(30);
		}
		else{
			//handles events on quene
			while(SDL_PollEvent(&e) != 0)
			{
				//stops game loop if user tries to quit
				if(e.type == SDL_QUIT){quit = 1;}
				switch(e.key.keysym.sym)
				{
					case SDLK_r:
						restart_game(&freeze);
							ball_speed = 7;
						  //creates 10*10 ball in the middle of screen
							ball.x = WIDTH/2;
							ball.y = HEIGHT/2;
							ball.w = 10;
							ball.h = 10;
							//sets collider to be just as big as ball
							ball.collider.w = ball.w;
							ball.collider.h = ball.h;
							break;
				}
			}		
			//also keep rendering everything while freeze
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(renderer);
			ball.render();
			racket.render();
			racket2.render();
			SDL_RenderPresent( renderer );
		}
	}
	close();
	return 0;
}
