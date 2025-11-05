#pragma once 
#include"helpers.hpp"

/*declarations*/
class Game;

struct vector2D{
    float x,y;
    vector2D():x(0),y(0){}
    vector2D(float x, float y):x(x),y(y){}

    vector2D operator+(const vector2D&value)const{
        return vector2D (x + value.x , y + value.y);
    }
    vector2D operator-(const vector2D&value)const{
        return vector2D (x - value.x , y - value.y);
    }
    vector2D operator*(const vector2D&value)const{
        return vector2D (x * value.x , y * value.y);
    }
    vector2D operator/(const vector2D&value)const{
        return vector2D (x / value.x , y / value.y);
    }

    vector2D operator+(const float&value)const{
        return vector2D (x + value , y + value);
    }
    vector2D operator-(const float&value)const{
        return vector2D (x - value , y - value);
    }
    vector2D operator*(const float&value)const{
        return vector2D (x * value , y * value);
    }
    vector2D operator/(const float&value)const{
        return vector2D (x / value , y / value);
    }
    
    
    friend vector2D operator+(const float&f,const vector2D&value){
        return vector2D (value.x + f   , value.y + f);
    }
    friend vector2D operator-(const float&f,const vector2D&value){
        return vector2D (value.x - f   , value.y - f);
    }
    friend vector2D operator*(const float&f,const vector2D&value){
        return vector2D (value.x * f   , value.y * f);
    }
    friend vector2D operator/(const float&f,const vector2D&value){
        return vector2D (value.x / f   , value.y / f);
    }



};

struct PhysicsBody{
    PhysicsBody(){}
    PhysicsBody(float x, float y):position{x,y}{}
    vector2D position;
    vector2D velocity;
    vector2D acceleration;
};

struct SpriteBody{
    SpriteBody(){}
    SpriteBody(float x , float y):rect{x,y,0,0}{}
    SDL_Texture*image;
    SDL_FRect rect;
};

class SpaceShip:
    public SpriteBody , public PhysicsBody
{
    private:
        float speed = 2000;                        
        float size = 100;   
        float friction = .8f; 
        int animationFrameIndex;
        std::vector<SDL_Texture*> animationFrames;
                
    public:
        SpaceShip(){}
        SpaceShip(SDL_Renderer*,const char*,float x , float y);
        void Update(float deltaTime,const bool*keystate);            
        void Draw(SDL_Renderer*);
};

/*definition*/
SpaceShip::SpaceShip
(
    //parameters    
    SDL_Renderer*renderer,
    const char*animationFilesDir,
    float x, 
    float y
):
    //initialized variables      
    SpriteBody(x,y),
    PhysicsBody(x,y),    
    animationFrameIndex(0)
{        
    //member function calls at creation of instance
    rect.w = size; rect.h = size;
    this->animationFrames = getTextures(renderer,animationFilesDir);
}
void SpaceShip::Update(float deltaTime,const bool*keystate){    

    vector2D direction{0,0};
    bool flight = false;

    //(SDLK_W)
    if (keystate[SDL_SCANCODE_W]){
        direction.y = -1; 
        flight = true;
    } 
    //(SDLK_S)
    else if (keystate[SDL_SCANCODE_S]){
        direction.y = 1;
        flight = true;
    } 

    //(SDLK_A)
    if (keystate[SDL_SCANCODE_A]){
        direction.x = -1;
        flight = true;
    } 

    //(SDLK_D)
    else if (keystate[SDL_SCANCODE_D]){
        direction.x = 1;
        flight = true;
    } 

    acceleration = direction * speed ;
    velocity = (velocity + acceleration * deltaTime);

    if (!flight) velocity = velocity * friction;

    position = position + (velocity * deltaTime) ;

    rect.x = position.x;
    rect.y = position.y;

    
    std::cout << "\nAcceleration: " << "(" << acceleration.x << "," << acceleration.y << ")";
    std::cout << "\nVelocity: " << "(" << velocity.x << "," << velocity.y << ")";
    std::cout << "\nDelta Time: " << deltaTime;
    
}

void SpaceShip::Draw(SDL_Renderer*renderer){

    //get current frame
    SDL_Texture*currentFrame = animationFrames[animationFrameIndex];    

    //draw current frame at rect value
    SDL_RenderTexture(renderer,currentFrame,NULL,&rect);
}