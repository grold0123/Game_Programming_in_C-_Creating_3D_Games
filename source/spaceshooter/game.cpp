#include"game.hpp"
#include<iostream>
Game::Game():
    windowWidth(700),
    windowHeight(520),
    bgColor{0,0,255,255},
    spaceShipSpeed(500),
    friction(.75)
{}
bool Game::initialize(){
    if (!SDL_Init(SDL_INIT_VIDEO)) return false;
    if (!SDL_CreateWindowAndRenderer(
        "Space Shooter",        //window title
        windowWidth,            //window width
        windowHeight,           //window height
        SDL_WINDOW_RESIZABLE,   //sdl window flag
        &this->window,          //sdl window
        &this->renderer         //sdl renderer
    )) return false;
    this->lastTime = SDL_GetTicks();
    return true;
}
void Game::run(){
    bool running = true;
    this->spaceShip = IMG_LoadTexture(renderer,R"(C:\projects\Game_Programming_in_C-_Creating_3D_Games\assets\spaceshooter\Blue\Animation\1.png)");
    this->spaceShipRect = {windowWidth/2.0f,windowHeight/2.0f,60,60} ;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;
        }
        this->updateGame();
        this->render();
    }
}
void Game::shutdown(){    
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
}
void Game::updateGame(){
    const bool*keystates = SDL_GetKeyboardState(nullptr);
    this->direction = {0,0};
    
    if (keystates[SDL_SCANCODE_W]) direction.y = -1;
    else if (keystates[SDL_SCANCODE_S]) direction.y = 1;

    if (keystates[SDL_SCANCODE_A]) direction.x = -1;
    else if (keystates[SDL_SCANCODE_D]) direction.x = 1;

    Uint64 now = SDL_GetTicks();
    float deltaTime = (now - lastTime)/1000.0f;   
    lastTime = now;

    acceleration = direction * spaceShipSpeed;
    velocity += acceleration * deltaTime;
    if (direction == vector2D{0,0}) velocity *= friction;
    position += velocity * deltaTime;

    spaceShipRect.x = position.x;
    spaceShipRect.y = position.y;

}
void Game::render(){
    clearRendererWithColor(renderer,bgColor);
    SDL_RenderTexture(renderer,spaceShip,NULL,&spaceShipRect);
    SDL_RenderPresent(renderer);
    std::cout << "Spaceship position: (" << spaceShipRect.x << "," << spaceShipRect.y << ")\n";
}

void clearRendererWithColor(SDL_Renderer*renderer,const color&rgba){
    SDL_SetRenderDrawColor(renderer,rgba.r,rgba.g,rgba.b,rgba.a);
    SDL_RenderClear(renderer);
}