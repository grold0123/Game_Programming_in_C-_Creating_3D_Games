#include"SDL3/SDL.h"

struct vec2D{
    double x,y;
    vec2D():x(0),y(0){};
    vec2D(double a,double b):x(a),y(b){}
    vec2D&operator+=(const vec2D&v){
        x += v.x;
        y += v.y;
        return *this;
    }
    vec2D&operator*=(const double&d){
        x *= d;
        y *= d;
        return *this;
    }
    vec2D operator+(const vec2D&v){
        return vec2D{x+v.x,y+v.y};        
    }
    vec2D operator*(const double&d){
        return vec2D{x*d,y*d};        
    }
    bool operator!()const{
        return (x == 0 && y == 0);
    }
    bool operator==(const vec2D&v){
        return (x == v.x && y == v.y);
    }
    bool operator!=(const vec2D&v){
        return (x != v.x || y != v.y);
    }
    void reset(){
        y = x = 0;
    }


};


class GameObject{
public:
    GameObject(SDL_FRect);
    void draw(SDL_Renderer&gameRenderer);
    void getDirection(const bool*);
    void physicsMovement(const double&deltaTime,const int&sizeWidth,const int&sizeHeight);    
    void displayPhysics();
    void ballMovement(const double&deltaTime,const double&speed,const int&sizeWidth,const int&sizeHeight);
private:
    SDL_FRect rect;
    SDL_Texture*texture = nullptr;
    vec2D position,acceleration,velocity,direction;
    float objectSpeed = 200, friction = .8;
};


