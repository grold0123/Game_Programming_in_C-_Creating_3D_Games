#include"game.hpp"

Game::Game(){}
bool Game::setup(){
    if (!SDL_Init(SDL_INIT_VIDEO)) return false;
    {//create window and renderer
        if (!SDL_CreateWindowAndRenderer(
        gameTitle,gameWidth,gameHeight,flag,&window,&renderer)
        ) return false;
    }
    return true;
}
void Game::run(){
    this->objects.push_back(Object(SDL_FRect{0,0,50,50}));
    while (gameState != CLOSE_GAME){
        this->pollEvent();
        this->getInput();
        this->update();
        this->render();    
    }
}
void Game::pollEvent(){
    while(SDL_PollEvent(&gameEvent)){
        switch(gameEvent.type) {
            case SDL_EVENT_QUIT : gameState = CLOSE_GAME;break;
        }
    }
}
void Game::getInput(){
    keystate = SDL_GetKeyboardState(nullptr);
}
void Game::update(){
    {//delta time
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime-lastTime)/1000.0f;
        lastTime = currentTime;
    }    
    for (auto&obj:objects) obj.update(deltaTime);
}
void Game::render(){
    {//renderer clear with bgColor
        SDL_SetRenderDrawColor(renderer,
            static_cast<Uint8>(bgColor.r),
            static_cast<Uint8>(bgColor.g),
            static_cast<Uint8>(bgColor.b),
            static_cast<Uint8>(bgColor.a)
        );
        SDL_RenderClear(renderer);
    }
    for (auto&obj:objects) obj.draw(renderer);
    SDL_RenderPresent(renderer);
}
void Game::shutdown(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}