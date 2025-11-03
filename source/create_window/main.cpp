//============================================================
//create_window
//============================================================
#include<iostream>
#include<string>
#include<SDL3/SDL.h>
//============================================================
std::string TITLE = "Game Programming in C++ (Chapter 1)";
int WINDOW_HEIGHT = 520;
int WINDOW_WEIGHT = 700;
//============================================================
//class Game declarations
class Game {
public:
    Game();
    bool initialize();
    void run_loop();
    void shutdown();
private:
    void process_input();
    void update_game();
    void generate_output();

    SDL_Window*game_window;
    bool is_running;
};
//============================================================
//class Game definitions
Game::Game():
    game_window(nullptr),
    is_running(true)
{}
bool Game::initialize(){
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Unable to initialize SDL: %s",SDL_GetError());
        return false;
    }
    this->game_window = SDL_CreateWindow(TITLE.c_str(),WINDOW_WEIGHT,WINDOW_HEIGHT,0);
    if (!this->game_window){
        SDL_Log("Failed to create window: %s",SDL_GetError());
        return false;
    }    
    return true;
}
void Game::shutdown(){
    SDL_DestroyWindow(game_window);
    SDL_Quit();
}
void Game::run_loop(){
    while (is_running) {
        this->process_input();
        this->update_game();
        this->generate_output();
    }
}
void Game::process_input(){}
void Game::update_game(){}
void Game::generate_output(){}
//============================================================
int main(){
    Game game;
    bool success = game.initialize();
    if (success) {
        game.run_loop();
    }
    game.shutdown();
}
