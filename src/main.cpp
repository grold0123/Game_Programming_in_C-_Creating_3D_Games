#include<iostream>
#include"SDL3/SDL.h"
using namespace std;



int main () {
    
    struct color{
        color():r(255),g(255),b(255),a(255){}
        color(float r,float g,float b,float a):r(r),g(g),b(b),a(a){}
        float r,g,b,a;
    }
    bgColor{0,0,255,255};   
    struct vec2D{
        vec2D():x(0),y(0){}
        vec2D(float a,float b):x(a),y(b){}
        float x,y;
    }
    direction,position,velocity,acceleration;
    const char
    *title = "initial window";
    const bool
    *keystate;
    int 
    width = 700 , height = 520, colorIncrement = 150;
    bool 
    running = true;
    float 
    lastTime = 0,currentTime = 0,deltaTime = 0;
    SDL_Window
    *window = nullptr;
    SDL_Renderer
    *renderer = nullptr;
    SDL_Event 
    event;
    SDL_FRect 
    rect{0,0,50,50};

    {//initialize SDL
        if (!SDL_Init(SDL_INIT_VIDEO)) return -1;
        if (!SDL_CreateWindowAndRenderer(title,width,height,SDL_WINDOW_RESIZABLE,&window,&renderer)) return -1;        
    }

    while (running) {//game loop
        
        {//poll events
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_EVENT_QUIT : running = false;
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
        
        {//inputs
            direction = {0,0};
            keystate = SDL_GetKeyboardState(nullptr);
            if (keystate[SDL_SCANCODE_S]) direction.y = 1;
            else if (keystate[SDL_SCANCODE_W]) direction.y = -1;

            if (keystate[SDL_SCANCODE_D]) direction.x = 1;
            else if (keystate[SDL_SCANCODE_A]) direction.x = -1;
        }
        
        {//update

            currentTime = SDL_GetTicks();
            deltaTime = currentTime - lastTime;
            lastTime = currentTime; 

            acceleration.x = direction.x;
            acceleration.y = direction.y;            

            velocity.x = acceleration.x * deltaTime;
            velocity.y = acceleration.y * deltaTime;

            vec2D next = {
                position.x + velocity.x * deltaTime,
                position.y + velocity.y * deltaTime
            };

            if  (next.x < 0 || next.x + rect.w > width) {
                    velocity.x = 0;
                }
            if  (next.y < 0 || next.y + rect.h > height) {
                    velocity.y = 0;
                }
            
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;

            rect.x = position.x;
            rect.y = position.y;

            if (bgColor.b <= 0.0f) {
                bgColor.b = 0.0f;
                colorIncrement *= -1;
            }

            if (bgColor.b >= 255.0f){
                bgColor.b = 255.0f;
                colorIncrement *= -1;
            }
            
            bgColor.b += colorIncrement * (deltaTime/1000.0f);
            
        }
        
        {//render
            SDL_SetRenderDrawColor(renderer,static_cast<Uint8>(bgColor.r),static_cast<Uint8>(bgColor.g),static_cast<Uint8>(bgColor.b),static_cast<Uint8>(bgColor.a));
            cout << bgColor.r << " " << bgColor.g << " " << bgColor.b << endl;
            SDL_RenderClear(renderer);

            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderFillRect(renderer,&rect);

            SDL_RenderPresent(renderer);
            cout << rect.x << "," << rect.y<< "\n";
        }
    
    }

    {//cleanup SDL
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    return 0;
}



/*
--hello world
g++ src\*.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\hello_world.exe

--initial window
g++ src\*.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\initial_window.exe

--inputs
g++ src\*.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\inputs.exe

*/