//====================================
//add_input_processesing
//====================================
#include<iostream>
#include<string>
#include<SDL3/SDL.h>
//====================================
std::string TITLE = "Basic input processing";
int WIDTH = 700;
int HEIGHT = 520;
//====================================
/*************************************
[Game class declaration]
1.	constructor
2.	initialize sdl
	-	create sdl window	
3.	game loop
	-	loop condition
	-	process input
	-	update game
	-	generate output
4.	close game
	-	destroy window
	-	quit sdl
*************************************/
class Game{
public:
	Game();
	bool initialize();
	void game_loop();
	void shutdown();
private:
	void process_input();
	void update_game();
	void generate_output();

	SDL_Window*game_window;
	bool is_running;
};
//====================================
//[Game class definition]
Game::Game():
	game_window(nullptr),
	is_running(true)
{}
bool Game::initialize(){
	//initialize sdl
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "Failed to initialize\n";
		return false;
	}
	//create game window
	this->game_window = SDL_CreateWindow(TITLE.c_str(),WIDTH,HEIGHT,0);
	if (!game_window) {
		std::cout << "Failed to create a game window\n";
		return false;
	}
	return true;
}
void Game::game_loop(){
	while (is_running) {
		this->process_input();
		this->update_game();
		this->generate_output();
	}
}
void Game::shutdown(){
	SDL_DestroyWindow(game_window);
	SDL_Quit();
}
void Game::process_input(){
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_QUIT: this->is_running = false; break;
			case SDL_EVENT_KEY_DOWN: switch (event.key.key) {
				case SDLK_W : std::cout << "Pressed W key\n"; break;
				case SDLK_S : std::cout << "Pressed S key\n"; break;
				case SDLK_D : std::cout << "Pressed D key\n"; break;
				case SDLK_A : std::cout << "Pressed A key\n"; break;
			}
		}
	}
}
void Game::update_game(){

}
void Game::generate_output(){

}
//====================================
int main(){
	Game game;
	bool success = game.initialize();
	if (success) {
		game.game_loop();
	}
	game.shutdown();
	return 0;
}
//====================================
