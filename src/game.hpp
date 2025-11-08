#pragma once

#include<iostream>
#include"SDL3/SDL.h"
#include<vector>
#include"object.hpp"

class Game{
public:
    Game();    
    bool setup();void run();void shutdown();    
private:
    SDL_Renderer*renderer=nullptr;SDL_Window*window=nullptr;SDL_WindowFlags flag = SDL_WINDOW_RESIZABLE;SDL_Event gameEvent;
    int gameHeight=520,gameWidth=700;
    const char*gameTitle = "initial window";const bool*keystate=nullptr;
    struct color{
        color():
        r(0),
        g(0),
        b(0),
        a(0)
        {}
        color(float r,float g,float b,float a):
        r(r),
        g(g),
        b(b),
        a(a)
        {}
        float r,g,b,a;}
    bgColor{0,0,200,255};
    enum gamestate{IN_GAME,CLOSE_GAME,PAUSE_GAME}gameState=IN_GAME;
    float currentTime=0,lastTime=0,deltaTime=0;

    void pollEvent();
    void getInput();
    void update();
    void render();

    std::vector<Object>objects;
};

