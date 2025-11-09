#include"object.hpp"
#include<iostream>
using namespace std;

GameObject::GameObject(SDL_FRect R):
    rect(R),position{R.x,R.y}{}
void GameObject::draw(SDL_Renderer&gameRenderer){
    if (!texture) {
        SDL_SetRenderDrawColor(&gameRenderer,255,0,0,255);
        SDL_RenderFillRect(&gameRenderer,&rect);
    }
    SDL_RenderTexture(&gameRenderer,texture,NULL,&rect);
}
void GameObject::getDirection(const bool*keyState){

    direction.reset();

    if (keyState[SDL_SCANCODE_W]) {
        direction.y = -1;
    }
    else if (keyState[SDL_SCANCODE_S]) {
        direction.y = 1;
    }

    if (keyState[SDL_SCANCODE_A]) {
        direction.x = -1;
    }
    else if (keyState[SDL_SCANCODE_D]) {
        direction.x = 1;
    }    
}
void GameObject::physicsMovement(const double&deltaTime,const int&sizeWidth,const int&sizeHeight){

    {//delta time based physics
        {//get directional acceleration
            acceleration = direction * objectSpeed;
        }
        {//update velocity
            if (!direction) velocity *= friction;//apply friction if no direction
            velocity += acceleration * deltaTime;//apply acceleration by delta time to velocity
        }        
        {//bound check set velocity 
            double 
            x = position.x + velocity.x * deltaTime,
            y = position.y + velocity.y * deltaTime;
            if (x < 0) {velocity.x = 0;position.x = 0;}
            if (x + rect.w > sizeWidth) {velocity.x = 0; position.x = sizeWidth - rect.w;}
            
            if (y < 0) {velocity.y = 0;position.y = 0;}
            if (y + rect.h > sizeHeight) {velocity.y = 0; position.y = sizeHeight - rect.h;}
        }                
        position += velocity * deltaTime;//update position        
    }
    
    rect.x = position.x;
    rect.y = position.y;

}
void GameObject::displayPhysics(){
    cout << "acceleration: " << acceleration.x << " , " << acceleration.y << endl;
    cout << "velocity: " << velocity.x << " , " << velocity.y << endl;        
    cout << "position: " << position.x << " , " << position.y << endl;        
}
void GameObject::ballMovement(const double&deltaTime,const double&speed,const int&sizeWidth,const int&sizeHeight){
    
    {
        double 
        x = position.x + velocity.x * deltaTime,
        y = position.y + velocity.y * deltaTime;
        if (x < 0) {direction.x *= -1;position.x = 0;}
        if (x + rect.w > sizeWidth) {direction.x *= -1; position.x = sizeWidth - rect.w;}
        
        if (y < 0) {direction.y *= -1;position.y = 0;}
        if (y + rect.h > sizeHeight) {direction.y *= -1; position.y = sizeHeight - rect.h;}
    }
    

    position += velocity * deltaTime;//update position        
            
}