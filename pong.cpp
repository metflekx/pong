#include<iostream>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
#include"helpers.h"
#include"./racket/racket.h"
#include"./ball/ball.h"

//accesses global variables from helpers.o
extern SDL_Window* window; 
extern SDL_Renderer* renderer;
extern int racket_speed;
extern int ball_speed;
extern int freeze; 
extern int p1_score;
extern int p2_score;

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
	//event handler
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
