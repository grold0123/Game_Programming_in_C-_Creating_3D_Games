#include<iostream>
#include"SDL3/SDL.h"
using namespace std;

//-------------------------------------------------------------
//structs
struct color{
        color():r(255),g(255),b(255),a(255){}
        color(float r,float g,float b,float a):r(r),g(g),b(b),a(a){}
        float r,g,b,a;
};
struct vec2D{
        vec2D():x(0),y(0){}
        vec2D(float a,float b):x(a),y(b){}
        float x,y;
};
//-------------------------------------------------------------
//classes
enum paddleSide{LEFT,RIGHT};
class Paddle{
public:
    Paddle(paddleSide p,const int&gameWidth,const int&gameHeight):
        paddleColor(0,0,0,255),
        side(p)
    {
        if (side == LEFT){
            rect.x = 0;
            rect.y = gameHeight/8.0f;
            rect.w = 15;
            rect.h = gameHeight/4.0f;
            position.x = rect.x;
            position.y = rect.y;
        }
        else if (side == RIGHT){
            rect.x = gameWidth - 15;
            rect.y = gameHeight/8.0f;
            rect.w = 15;
            rect.h = gameHeight/4.0f;
            position.x = rect.x;
            position.y = rect.y;
        }
    }
    void control(const bool*keystate){
        direction = {0,0};
        if (side == LEFT){
            if (keystate[SDL_SCANCODE_W]) direction.y = -1;
            else if (keystate[SDL_SCANCODE_S]) direction.y = 1;
        }
        if (side == RIGHT){
            if (keystate[SDL_SCANCODE_UP]) direction.y = -1;
            else if (keystate[SDL_SCANCODE_DOWN]) direction.y = 1;
        }        
    }
    void move(const float&deltaTime,const int&gameWidth,const int&gameHeight){

        // velocity.x += acceleration.x * deltaTime;
        velocity.y = direction.y * deltaTime * speed;

        {//clamp
            vec2D next {
                position.x + velocity.x , 
                position.y + velocity.y
            };
            // if (next.x <= 0) {
            //     velocity.x = 0;
            //     position.x = 0;
            // }
            // if (next.x + rect.w >= gameWidth){
            //     velocity.x = 0;
            //     position.x = gameWidth - rect.w;
            // }
            if (next.y <= 0) {
                velocity.y = 0;
                position.y = 0;
            }
            if (next.y + rect.h >= gameHeight){
                velocity.y = 0;
                position.y = gameHeight - rect.h;
            }
        }
        
        // position.x += velocity.x * deltaTime;
        position.y += velocity.y ;                

        // rect.x = position.x;
        rect.y = position.y;
    }
    void draw(SDL_Renderer*rend)const{
        SDL_SetRenderDrawColor(
            rend,
            static_cast<Uint8>(paddleColor.r),
            static_cast<Uint8>(paddleColor.g),
            static_cast<Uint8>(paddleColor.b),
            static_cast<Uint8>(paddleColor.a)
        );
        SDL_RenderFillRect(rend,&rect);
    }
private:
    float speed = 1400;
    SDL_FRect rect;
    vec2D direction,position,velocity,acceleration;
    color paddleColor;
    paddleSide side;
};
class Ball{
public:
    void move(const float&deltaTime,const int&gameWidth,const int&gameHeight){                
        {//bounce effect if hitting bounds
            vec2D nextPosition = {
                position.x + (direction.x * speed * deltaTime),
                position.y + (direction.y * speed * deltaTime),
            };
            {//for 0 value x , y  
                if (nextPosition.x < 0 && direction.x < 0) {
                    direction.x *= -1;   
                    position.x = 0;
                }
                if (nextPosition.y < 0 && direction.y < 0){
                    direction.y *= -1;   
                    position.y = 0;
                }
            }
            {//for gameWidth and gameHeight 
                if (nextPosition.x + rect.w > gameWidth  && direction.x > 0){
                    direction.x *= -1;   
                    position.x = gameWidth - rect.w;
                }
                if (nextPosition.y + rect.h > gameHeight && direction.y > 0){
                    direction.y *= -1;   
                    position.y = gameHeight - rect.h;
                }
            }
        }
        {//apply delta time to velocity and assign to position
            position.x += deltaTime * direction.x * speed;
            position.y += deltaTime * direction.y * speed;
        }
        {//assign position to rect
            rect.x = position.x ; 
            rect.y = position.y ;
        }                        
        {//temp check
            if (direction.x > 0) ballColor.r += 10 * deltaTime;
            if (direction.x < 0) ballColor.r -= 10 * deltaTime;

            if (direction.y > 0) ballColor.g += 10 * deltaTime;
            if (direction.y < 0) ballColor.g -= 10 * deltaTime;
        }
    }
    
    void draw(SDL_Renderer*renderer)const{
        SDL_SetRenderDrawColor(
            renderer,
            static_cast<Uint8>(ballColor.r),
            static_cast<Uint8>(ballColor.g),
            static_cast<Uint8>(ballColor.b),
            static_cast<Uint8>(ballColor.a)
        );
        SDL_RenderFillRect(renderer,&rect);        
    }
private:    
    color ballColor;
    SDL_FRect rect{0,0,50,50};
    vec2D direction{1,1},position{rect.x,rect.y},velocity,acceleration;
    float speed = 1000;
};
class Game{
public:
    Game():
        leftPaddle(LEFT,gameWidth,gameHeight),rightPaddle(RIGHT,gameWidth,gameHeight){}
    bool initialize(){
        if (!SDL_Init(SDL_INIT_VIDEO)) return false;
        if (!SDL_CreateWindowAndRenderer(title,gameWidth,gameHeight,SDL_WINDOW_RESIZABLE,&window,&renderer)) return false;        
        return true;
    }
    void run(){        
        while (running) {            
            this->pollEvent();
            this->input();
            this->update();
            this->render();
        }
    }
    void shutdown () {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
private:
    const char*title = "Ball class";
    int gameWidth = 720, gameHeight = 520;
    color bgColor{255,255,255,255};       
    const bool*keystate = nullptr;    
    int  bgColorIncrement = 150;
    bool running = true;
    float lastTime = 0,currentTime = 0,deltaTime = 0;
    SDL_Window*window = nullptr;
    SDL_Renderer*renderer = nullptr;
    SDL_Event event;
    
    Ball ball;
    Paddle leftPaddle, rightPaddle;

    void pollEvent () {        
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_EVENT_QUIT : running = false;break;
                case SDL_EVENT_KEY_UP: switch (event.key.key) {
                    case SDLK_W : cout << "Pressed W key\n";break;
                    case SDLK_S : cout << "Pressed S key\n";break;
                    case SDLK_D : cout << "Pressed D key\n";break;
                    case SDLK_A : cout << "Pressed A key\n";break;
                    default: break;
                }
            }
        }
    }
    void input () {
        keystate = SDL_GetKeyboardState(nullptr);
        {//paddle controls
            leftPaddle.control(keystate);
            rightPaddle.control(keystate);
        }        
    }
    void update () {
        {//get delta time
            currentTime = SDL_GetTicks();
            deltaTime = (currentTime - lastTime)/1000.0f ;
            lastTime = currentTime;
        }
        {//move ball
            ball.move(deltaTime,gameWidth,gameHeight);
        }
        {//move paddle 
            leftPaddle.move(deltaTime,gameWidth,gameHeight);
            rightPaddle.move(deltaTime,gameWidth,gameHeight);
        }
        
    }
    void render () {
        {//clear renderer with bgColor
            SDL_SetRenderDrawColor(
                renderer,
                static_cast<Uint8>(bgColor.r),
                static_cast<Uint8>(bgColor.g),
                static_cast<Uint8>(bgColor.b),
                static_cast<Uint8>(bgColor.a)
            );
            SDL_RenderClear(renderer);
        }
        {//render ball
            this->ball.draw(renderer);
        }
        {//render paddles
            leftPaddle.draw(renderer);
            rightPaddle.draw(renderer);
        }
        SDL_RenderPresent(renderer);
    }  
};
//-------------------------------------------------------------
//main function
int main () {                                                
    Game game;
    if (!game.initialize()) return -1;
    game.run();
    game.shutdown();
}



/*
--hello world
g++ src\main.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\hello_world.exe

--initial window
g++ src\main.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\initial_window.exe

--inputs
g++ src\main.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\inputs.exe

--ball class
g++ src\main.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\ball_class.exe

--paddle class
g++ src\main.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\paddle_class.exe
*/