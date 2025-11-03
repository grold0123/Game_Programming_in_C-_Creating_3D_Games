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
struct BGCOLOR{
	int R = 255;
	int G = 255;
	int B = 255;
	int A = 255;
};
enum gamestate{
	RUNNING,CLOSE_GAME
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
	BGCOLOR BG;	
	SDL_Rect paddle{
		0,0
	};
	//=============================================
	while (gamestate != CLOSE_GAME) {
		//handle inputs
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_KEY_DOWN : 
					switch (event.key.key) { 					
						case SDLK_W : std::cout << "Pressed W key\n"; break;
						case SDLK_S : std::cout << "Pressed S key\n"; break;
						case SDLK_D : std::cout << "Pressed D key\n"; break;
						case SDLK_A : std::cout << "Pressed A key\n"; break;					
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