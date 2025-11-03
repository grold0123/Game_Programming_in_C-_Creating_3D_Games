#include<game/game.h>
//========================================================
Game::Game():
    renderer(nullptr),
    window(nullptr),
    gamestate(IN_GAME),
    dimensions({700,520}),
    bg({0,0,200,255}),
    gametitle("Pong")
{}
bool Game::initialize(){
    if (!SDL_Init(SDL_INIT_VIDEO)) return false;
    this->window = SDL_CreateWindow(gametitle.c_str(),dimensions.x,dimensions.y,0);
    if (!window) return false;
    this->renderer = SDL_CreateRenderer(window,nullptr);
    if (!renderer) return false;
    return true;
}
void Game::run(){
    while (gamestate != CLOSE_GAME) {
        this->input();
        this->update();
        this->render();
    }
}
void Game::input(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if (event.type == SDL_EVENT_QUIT) gamestate = CLOSE_GAME;
    }
}
void Game::update(){}
void Game::render(){
    this->draw_bg();
    SDL_RenderPresent(renderer);
}
void Game::shutdown(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Game::draw_bg(){
    SDL_SetRenderDrawColor(renderer,bg.R,bg.G,bg.B,bg.A);
    SDL_RenderClear(renderer);
}
//========================================================
Shape::Shape(color color,SDL_Rect rect):
    shape_color({color.R,color.G,color.B,color.A}),
    shape_rect({rect.x,rect.y,rect.w,rect.h}),
    shape_speed(SPEED)
{}

