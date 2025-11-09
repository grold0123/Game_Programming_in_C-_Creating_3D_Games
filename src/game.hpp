#include"SDL3/SDL.h"

class Game{
public:    
    bool setup();
    void run();
    void shutdown();    
private:
    SDL_Window*gameWindow = nullptr;
    SDL_Renderer*gameRenderer = nullptr;
    SDL_WindowFlags windowFlag = SDL_WINDOW_RESIZABLE;
    SDL_Event gameEvent;
    const char*gameTitle = "Pong";
    const bool*keyState = nullptr;
    int gameWidth = 700,gameHeight = 520;
    double currentTime=0.0,lastTime=0.0,deltaTime=0.0;
    enum Game_State{IN_GAME,CLOSE_GAME,PAUSE_GAME}gameState = IN_GAME;
};
