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
    Game(){}
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
    void input () {}
    void update () {
        {//get delta time
            currentTime = SDL_GetTicks();
            deltaTime = (currentTime - lastTime)/1000.0f ;
            lastTime = currentTime;
        }
        ball.move(deltaTime,gameWidth,gameHeight);
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
        {//renderball
            this->ball.draw(renderer);
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
*/