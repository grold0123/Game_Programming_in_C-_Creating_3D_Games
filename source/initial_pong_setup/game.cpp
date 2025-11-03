#include<game/game.h>
//========================================================
Shape::Shape(color color,SDL_Rect rect):
    shape_color({color.R,color.G,color.B,color.A}),    
    shape_speed(1000),
    shape_pos({rect.x,rect.y}),
    shape_vel({0,0}),
    shape_rect({shape_pos.x,shape_pos.y,rect.w,rect.h})
{}
void Shape::draw(SDL_Renderer*renderer){
    SDL_SetRenderDrawColor(
        renderer,
        static_cast<Uint8>(shape_color.R),
        static_cast<Uint8>(shape_color.G),
        static_cast<Uint8>(shape_color.B),
        static_cast<Uint8>(shape_color.A)
    );
    SDL_FRect r{
        static_cast<float>(shape_rect.x),
        static_cast<float>(shape_rect.y),
        static_cast<float>(shape_rect.w),
        static_cast<float>(shape_rect.h)
    };
    SDL_RenderFillRect(renderer,&r);
};
void Shape::move(Uint64 delta_time){
    const bool*key_states = SDL_GetKeyboardState(nullptr);
    vector2d direction{0,0};

    if (key_states[SDL_SCANCODE_W]) direction.y = -this->shape_speed ;
    else if (key_states[SDL_SCANCODE_S]) direction.y = this->shape_speed ;    

    if (key_states[SDL_SCANCODE_A]) direction.x = -this->shape_speed ;
    else if (key_states[SDL_SCANCODE_D]) direction.x = this->shape_speed ;    

    this->shape_vel.y = direction.y * (delta_time / 1000.0f);
    this->shape_vel.x = direction.x * (delta_time / 1000.0f);

    this->shape_pos.y += this->shape_vel.y;
    this->shape_pos.x += this->shape_vel.x;

    this->shape_rect.y = this->shape_pos.y;
    this->shape_rect.x = this->shape_pos.x;
}
//========================================================
Game::Game():
    renderer(nullptr),
    window(nullptr),
    gamestate(IN_GAME),
    dimensions({700,520}),
    bg({0,0,200,255}),
    gametitle("Pong"),
    ball(
        color{
            255,
            255,
            255,
            255
        },
        SDL_Rect{
                dimensions.x/2,
                dimensions.y/2,
                15,
                15
        }
    )
{}
bool Game::initialize(){
    if (!SDL_Init(SDL_INIT_VIDEO)) return false;
    this->window = SDL_CreateWindow(gametitle.c_str(),dimensions.x,dimensions.y,0);
    if (!window) return false;
    this->renderer = SDL_CreateRenderer(window,nullptr);
    if (!renderer) return false;
    this->last_time = SDL_GetTicks();
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
void Game::update(){    
    Uint64 now = SDL_GetTicks();
    Uint64 delta_time =  now - this->last_time;
    this->last_time = now;
    
    ball.move(delta_time);    
}
void Game::render(){
    this->draw_bg();
    this->ball.draw(renderer);
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
