#pragma once
#include<SDL3/SDL.h>
#include<iostream>

/***************************************************/
class Game{
public:

    Game();

    bool setup();
    void run();
    void shutdown();

private:

    void handle_events();
    void update();
    void render();

    void draw_bg();
    void draw_wall();
    void draw_paddles();
    void draw_ball();

    void paddle_control(float&);
    void bounce(float&);
    void reset();

    float thickness;

    SDL_FRect topwall;
    SDL_FRect bottomwall;    
    
    struct vector2d{
        vector2d(float a=0,float b=0):x(a),y(b){}
        float x;float y;
    };
            
    SDL_FRect leftpaddle;
    vector2d left_pos;
    vector2d left_acc;
    vector2d left_vec;

    SDL_FRect rightpaddle;
    vector2d right_pos;
    vector2d right_acc;
    vector2d right_vec;

    SDL_FRect ball;
    vector2d ball_pos;
    vector2d ball_acc;
    vector2d ball_vec;

    SDL_Window*game_window;
    SDL_Renderer*game_renderer;

    int paddle_speed;
    float friction;
    
    Uint64 last_tick;

    bool IN_GAME;
};
/***************************************************/
Game::Game()
    :
        game_window(nullptr),
        game_renderer(nullptr),
        IN_GAME(true),
        thickness(15),
        topwall{0,0,700,thickness},
        bottomwall{0,520-thickness,700,thickness},
        leftpaddle{0,520/4,15,520/4},
        left_pos(leftpaddle.x,leftpaddle.y),
        rightpaddle{700-15,520/4,15,520/4},
        right_pos(rightpaddle.x,rightpaddle.y),
        ball{700/2,520/2,thickness,thickness},
        ball_pos{ball.x,ball.y},
        ball_vec{-100,100},
        paddle_speed(700),        
        friction(.9)        
{}
bool Game::setup(){
    if (!SDL_Init(SDL_INIT_VIDEO)) return false ;
    game_window = SDL_CreateWindow("Pong",700,520,0);
    if (!game_window) return false;
    game_renderer = SDL_CreateRenderer(game_window,NULL);
    last_tick = SDL_GetTicks();
    return true;
}
void Game::run(){
    while (IN_GAME) {
        handle_events();
        update();
        render();
    }
}
void Game::shutdown(){
    SDL_DestroyRenderer(game_renderer);
    SDL_DestroyWindow(game_window);
    SDL_Quit();
}
void Game::handle_events(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) IN_GAME = false;
        else if (event.type == SDL_EVENT_KEY_DOWN) switch (event.key.key) {
            case SDLK_W : std::cout << "Pressed W key\n" ; break;
            case SDLK_S : std::cout << "Pressed S key\n" ; break;
            case SDLK_D : std::cout << "Pressed D key\n" ; break;
            case SDLK_A : std::cout << "Pressed A key\n" ; break;
        }        
    }        
}
void Game::update(){
    
    float now = SDL_GetTicks();
    float delta_time =  (now - last_tick)/1000.0f;
    last_tick = now;

    paddle_control(delta_time);
    bounce(delta_time);
    if  (ball.x + ball.w < 0 || ball.x > 700) reset();
        
}
void Game::render(){

    draw_bg();

    draw_wall();

    draw_paddles();

    draw_ball();
    
    SDL_RenderPresent(game_renderer);
}
void Game::draw_bg(){

    SDL_SetRenderDrawColor(game_renderer,0,0,255,255);

    SDL_RenderClear(game_renderer);
}
void Game::draw_wall(){

    SDL_SetRenderDrawColor(game_renderer,255,255,255,255);

    SDL_RenderFillRect(game_renderer,&topwall);

    SDL_RenderFillRect(game_renderer,&bottomwall);
}
void Game::draw_paddles(){
    SDL_SetRenderDrawColor(game_renderer,0,255,0,255);

    SDL_RenderFillRect(game_renderer,&leftpaddle);

    SDL_RenderFillRect(game_renderer,&rightpaddle);
}
void Game::draw_ball(){

    SDL_SetRenderDrawColor(game_renderer,255,0,0,255);

    SDL_RenderFillRect(game_renderer,&ball);
}
void Game::paddle_control(float&delta_time){
    
    const bool*key_press = SDL_GetKeyboardState(nullptr);
    vector2d left_paddle_direction{0,0};
    vector2d right_paddle_direction{0,0};

    //get direction depending on input
    if (key_press[SDL_SCANCODE_W]){
        left_paddle_direction.y = -1;
    } 
    if (key_press[SDL_SCANCODE_S]) {
        left_paddle_direction.y = 1;
    }
    if (key_press[SDL_SCANCODE_UP]) {
        right_paddle_direction.y = -1;
    }
    if (key_press[SDL_SCANCODE_DOWN]) {
        right_paddle_direction.y = 1;
    }

    //apply direction and speed to acceleration
    left_acc.y = left_paddle_direction.y  *  paddle_speed;
    right_acc.y = right_paddle_direction.y  * paddle_speed;

    //apply acceleration to velocity per delta time
    left_vec.y += left_acc.y * delta_time;
    right_vec.y += right_acc.y * delta_time;

    //apply friction to velocity
    if (left_paddle_direction.y == 0) left_vec.y *= friction;
    if (right_paddle_direction.y == 0) right_vec.y *= friction;        
    

    //change position by its velocity per delta time
    left_pos.y += left_vec.y * delta_time;
    right_pos.y += right_vec.y * delta_time;

    //paddle bounds
    if (left_pos.y < thickness){
        left_pos.y = thickness ; 
        left_vec.y = 0;
    } 
    else if (left_pos.y + leftpaddle.h > 520 - thickness) {
        left_pos.y = 520 - thickness -  leftpaddle.h; 
        left_vec.y = 0;
    }
    
    if (right_pos.y < thickness) {
        right_pos.y = thickness; 
        right_vec.y = 0;
    }
    else if (right_pos.y + rightpaddle.h > 520 - thickness) {
        right_pos.y = 520 - thickness -  rightpaddle.h;
        right_vec.y = 0;
    }   
    
    //assign position to rect
    rightpaddle.y = right_pos.y;
    leftpaddle.y = left_pos.y;
}
void Game::bounce(float&delta_time){

    ball_pos.x += ball_vec.x * delta_time;
    ball_pos.y += ball_vec.y* delta_time;

    if  (
            ball_pos.x          <=  leftpaddle.x + leftpaddle.w      &&          
            ball_pos.x + ball.w >=  leftpaddle.x                     &&  
            ball_pos.y + ball.h >=  leftpaddle.y                     && 
            ball_pos.y          <=  leftpaddle.y + leftpaddle.h
        ){
            ball_pos.x          =   leftpaddle.x + leftpaddle.w;
            ball_vec.x          *=  -1;             
        }
        
    if  (
            ball_pos.x          <=  rightpaddle.x + rightpaddle.w    &&
            ball_pos.x + ball.w >=  rightpaddle.x                    &&
            ball_pos.y + ball.h >=  rightpaddle.y                    &&
            ball_pos.y          <=  rightpaddle.y + rightpaddle.h
        ){
            ball_pos.x          ==  rightpaddle.x + rightpaddle.w;
            ball_vec.x          *=  -1; 
        }   
    
    

    if (ball_pos.y < thickness) ball_vec.y *= -1; 
    else if (ball_pos.y + ball.h > 520 - thickness) ball_vec.y *= -1;

    ball.x = ball_pos.x;
    ball.y = ball_pos.y;    
}
void Game::reset(){
    ball_pos.x          =   700/2   ; 
    ball_pos.y          =   520/2   ;
    ball_vec.x          *=  -1      ;
    ball_vec.y          *=  -1      ;
}
/***************************************************/

