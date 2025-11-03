#pragma once
#include<SDL3/SDL.h>
#include<string>
//========================================================
struct dimension{
    int width ; int height;
};
struct position{
    int x ; int y;
};
struct color{
    int R;
    int G;
    int B;
    int A;
};
enum gamestate{
    IN_GAME,CLOSE_GAME
};
//========================================================
class Game{
public:
    Game();
    std::string gametitle;
    dimension dimensions;
    color bg;
    bool initialize();
    void run();
    void shutdown();
private:
    SDL_Window*window;
    SDL_Renderer*renderer;
    gamestate gamestate;
    void input();
    void update();
    void render();
    void draw_bg();
};
//========================================================
