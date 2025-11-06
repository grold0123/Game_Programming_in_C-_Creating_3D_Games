#pragma once
#include"SDL3/SDL.h"
#include"SDL3_image/SDL_image.h"
#include<memory>


struct color{
    color(){}
    color(Uint8 r, Uint8 g ,Uint8 b,Uint8 a):r(r),g(g),b(b),a(a){}
    Uint8 r,g,b,a;
};
struct vector2D{
    vector2D():x(0),y(0){}
    vector2D(float x,float y):x(x),y(y){}
    float x,y;
    vector2D operator+(const vector2D&v)const{
        return vector2D{x+v.x,y+v.y};
    }
    vector2D&operator+=(const vector2D&v){
        x += v.x;
        y += v.y;
        return *this;
    }
    vector2D operator*(const float&f)const{
        return vector2D{x*f,y*f};
    }
    vector2D&operator*=(const float&f){
        x *= f;
        y *= f;
        return *this;
    }
    bool operator==(const vector2D&v)const{
        return (x == v.x && y == v.y);
    }
    
};

class Game{
public:
    Game();
    bool initialize();
    void run();
    void shutdown();

private:
    SDL_Window*window;
    SDL_Renderer*renderer;
    
    void updateGame();
    void render();

    SDL_Texture*spaceShip;
    SDL_FRect spaceShipRect;
    int spaceShipSpeed;

    vector2D acceleration;
    vector2D velocity;
    vector2D position;
    vector2D direction;
    float friction;
    Uint64 lastTime;

    color bgColor;
    int windowWidth;
    int windowHeight;


};


void clearRendererWithColor(SDL_Renderer*renderer,const color&rgba);
