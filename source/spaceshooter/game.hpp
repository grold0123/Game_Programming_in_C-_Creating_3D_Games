#pragma once
#include"helpers.hpp"
#include"spaceship.hpp"
/*structs*/
struct Color{
    int R;
    int G;
    int B;
    int A;
};

/*enumerators*/
enum GameState{
    INGAME,
    CLOSEGAME
};

/*declarations*/
class Game{
public:

    Game();
    
    SpaceShip spaceShip;

    bool Initialize();
    
    void Run();

    void Shutdown();

private:

    void HandleEvents();
    void Update();
    void Render();    

    void draw_bg();
        
    SDL_Window*window = nullptr;
    SDL_Renderer*renderer = nullptr;

    GameState gameState;

    const char*gameTitle = "Space Shooter";
    int gameWidth = 700;
    int gameHeight = 520;

    Color Bg = {0,0,255,255};

    Uint64 lastTime;
};
//=====================================//
/*definitions*/
Game::Game():
    window(nullptr),
    renderer(nullptr),
    gameState(INGAME)    
{}
bool Game::Initialize(){    
    if (!SDL_CreateWindowAndRenderer(
        gameTitle,
        gameWidth,
        gameHeight,
        SDL_WINDOW_RESIZABLE,
        &window,
        &renderer
    )) return false;
    
    spaceShip = SpaceShip(            
            renderer,
            R"(C:\projects\Game_Programming_in_C-_Creating_3D_Games\assets\Blue\Animation)",
            gameWidth/2,
            gameHeight/2
        );
    
    lastTime = SDL_GetTicks();
    
    return true;
}
void Game::Run(){
    while (gameState != CLOSEGAME){
        HandleEvents();
        Update();
        Render();
    }
}
void Game::HandleEvents(){
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
        if (Event.type == SDL_EVENT_QUIT) gameState = CLOSEGAME;
    }
}
void Game::Update(){

    Uint64 now = SDL_GetTicks();
    float deltaTime = (now - lastTime)/1000.0f;
    lastTime = now;

    const bool* keyState = SDL_GetKeyboardState(nullptr);
    spaceShip.Update(deltaTime,keyState);

}
void Game::Render(){
    draw_bg();
    spaceShip.Draw(renderer);
    SDL_RenderPresent(renderer);
}
void Game::Shutdown(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Game::draw_bg(){
    SDL_SetRenderDrawColor(renderer,Bg.R,Bg.G,Bg.B,Bg.A);
    SDL_RenderClear(renderer);
}

