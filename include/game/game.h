#pragma once
#include<SDL3/SDL.h>
#include<string>
//========================================================
struct vector2d{
    int x; int y;
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
class Shape{
public:
    Shape(color,SDL_Rect);
    void draw(SDL_Renderer*);
    void move(Uint64);    
private:
    color shape_color;
    SDL_Rect shape_rect;
    vector2d shape_pos;
    vector2d shape_vel;
    int shape_speed;    
};
//========================================================
class Game{
public:
    Game();
    std::string gametitle;
    vector2d dimensions;
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
    Shape ball;
    Uint64 last_time = 0;
};
//========================================================
