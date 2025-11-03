/*====================================
initial_pong_setup
====================================*/
#include<iostream>
#include<string>
#include<vector>
#include<SDL3/SDL.h>
//====================================
std::string TITLE = "Basic input processing";
int WIDTH = 700;
int HEIGHT = 520;
int THICKNESS = 15;
struct Color{
	int R;
	int G;
	int B;
	int A;
};
enum gamestate{
	RUNNING,CLOSE_GAME
};
struct vector2{
	float x; float y;
};
/*====================================
1.	initialize sdl
2.	create window
3.	create renderer
4.	game loop
	-	get inputs
	-	update game
	-	render
5.	shutdown
=====================================*/
int main(){
	//=============================================
	if (!SDL_Init(SDL_INIT_VIDEO))return 1; 
	SDL_Window*window = SDL_CreateWindow(TITLE.c_str(),WIDTH,HEIGHT,0);
	if (!window) return 1;			
	SDL_Renderer*renderer = SDL_CreateRenderer(window,NULL);
	if (!renderer) return 1;
	//=============================================
	gamestate gamestate = RUNNING;
	Color BG({0,0,255,255});	
	Color wall({0,0,0,255});
	Color paddle({255,255,255,255});
	Color ball({255,255,255,255});
	SDL_FRect topwall{		
		static_cast<float>(0),
		static_cast<float>(0),
		static_cast<float>(WIDTH),
		static_cast<float>(THICKNESS)
	};
	SDL_FRect bottomwall{
		static_cast<float>(0),
		static_cast<float>(HEIGHT-THICKNESS),
		static_cast<float>(WIDTH),
		static_cast<float>(THICKNESS)
	};
	vector2 paddle_pos{
	static_cast<float>(0),
	static_cast<float>(HEIGHT/4)		
	};
	vector2 ball_pos{
		static_cast<float>(WIDTH/2),
		static_cast<float>(HEIGHT/2)
	};
	SDL_FRect ball_rect{
			static_cast<float>(ball_pos.x - THICKNESS/2),
			static_cast<float>(ball_pos.y - THICKNESS/2),
			static_cast<float>(THICKNESS),
			static_cast<float>(THICKNESS)
	};
	SDL_FRect paddle_rect{
		static_cast<float>(paddle_pos.x),
		static_cast<float>(paddle_pos.y),
		static_cast<float>(THICKNESS),
		static_cast<float>(HEIGHT/4)
	};
	bool pressed = false;
	Uint64 now = SDL_GetTicks();
	//=============================================
	while (gamestate != CLOSE_GAME) {
				
		Uint64 delta_time = SDL_GetTicks() - now;
		now = SDL_GetTicks();
		if (pressed) paddle_rect.y += paddle_pos.y * delta_time;

		//handle inputs
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_KEY_DOWN : 
					switch (event.key.key) { 					
						case SDLK_W : std::cout << "Pressed W key\n"; pressed = true; paddle_pos.y = -1; break;
						case SDLK_S : std::cout << "Pressed S key\n"; pressed = true; paddle_pos.y = 1; ;break;
						case SDLK_D : std::cout << "Pressed D key\n"; break;
						case SDLK_A : std::cout << "Pressed A key\n"; break;					
					}					
					break;				
				case SDL_EVENT_KEY_UP :
					switch (event.key.key) {
						case SDLK_W :  pressed = false;break;
						case SDLK_S :  pressed = false;break;
					}
					break;
				case SDL_EVENT_QUIT : 
					gamestate = CLOSE_GAME;
					break;
				
				default : 
					break;
			}
		}
		
		//update
		

		//draw bg
		SDL_SetRenderDrawColor(renderer,BG.R,BG.G,BG.B,BG.A);
		SDL_RenderClear(renderer);

		//draw topwall
		SDL_SetRenderDrawColor(renderer,wall.R,wall.G,wall.B,wall.A);
		SDL_RenderFillRect(renderer,&topwall);

		//draw bottomwall
		SDL_SetRenderDrawColor(renderer,wall.R,wall.G,wall.B,wall.A);
		SDL_RenderFillRect(renderer,&bottomwall);

		//draw paddle
		SDL_SetRenderDrawColor(renderer,paddle.R,paddle.G,paddle.B,paddle.A);
		SDL_RenderFillRect(renderer,&paddle_rect);

		//draw ball
		SDL_SetRenderDrawColor(renderer,ball.R,ball.G,ball.B,ball.A);
		SDL_RenderFillRect(renderer,&ball_rect);

		//display renderer
		SDL_RenderPresent(renderer);
	}
	//=============================================
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	//=============================================
	return 0;
}