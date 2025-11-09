#include"game.hpp"
#include"object.hpp"
#include<vector>
#include<iostream>
using namespace std;

bool Game::setup(){
    if (SDL_Init(SDL_INIT_VIDEO)){
        if (SDL_CreateWindowAndRenderer(
            gameTitle,
            gameWidth,
            gameHeight,
            windowFlag,
            &gameWindow,
            &gameRenderer)) 
        {
            return true;
        }
    }
    return false;
}
void Game::run(){    
    GameObject ball({0,0,50,50});
    while(gameState != CLOSE_GAME) {                                
        {//poll event
            while (SDL_PollEvent(&gameEvent)) {
                if (gameEvent.type == SDL_EVENT_QUIT) gameState = CLOSE_GAME;
                else if (gameEvent.type == SDL_EVENT_KEY_DOWN){
                    ball.displayPhysics();
                    cout << "current - last: " << (currentTime-lastTime) << endl;
                    cout << "Delta time: " << deltaTime << endl;
                } 
            }
        }
        {//get input 
            keyState = SDL_GetKeyboardState(nullptr);            
            ball.getDirection(keyState);
        }
        {//update
            {//delta time
                currentTime = static_cast<double>(SDL_GetTicks());
                deltaTime = (currentTime - lastTime)/1000.0;
                if (deltaTime < .0001) deltaTime = 0.0001;
                lastTime = currentTime;
                
            }                      
            ball.move(deltaTime,gameWidth,gameHeight);
        }
        {//render
            {//bg color
                SDL_SetRenderDrawColor(gameRenderer,255,255,255,255);
                SDL_RenderClear(gameRenderer);
            }
            {//draw game objects
                ball.draw(*gameRenderer);
            }
            SDL_RenderPresent(gameRenderer);
        }
    }
}
void Game::shutdown(){
    SDL_DestroyRenderer(gameRenderer);
    SDL_DestroyWindow(gameWindow);
    SDL_Quit();
}