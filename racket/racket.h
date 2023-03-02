#include<SDL2/SDL.h>
#include"../helpers.h"

extern SDL_Renderer* renderer;
extern int racket_speed;
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

