#pragma once
#include"SDL3/SDL.h"
/*
1.  draw method need a reference of renderer and self rect
2.  update using deltaTime
*/

class Object{
public:
    Object();
    Object(SDL_FRect);    
    void draw(SDL_Renderer*)const;
    void update(const float&);
private:
    SDL_FRect rect;SDL_Texture*texture=nullptr;
    struct vec2D{
        vec2D():x(0),y(0){}
        vec2D(float a,float b):x(a),y(b){}
        float x,y;
    }
    direction,position,acceleration,velocity;
    struct color{
        color():r(0),g(0),b(0),a(255){}
        float r,g,b,a;
    }
    objectColor;
};