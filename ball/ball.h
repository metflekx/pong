#include<SDL2/SDL.h>
#include"../helpers.h"

extern int freeze;  
extern int ball_speed;
extern SDL_Renderer* renderer;
extern int p1_score;
extern int p2_score;

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
