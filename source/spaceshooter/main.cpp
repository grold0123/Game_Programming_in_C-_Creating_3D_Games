/*
spaceshooter
1.  create game class
    -  setup
        -   initialize sdl
        -   create window ,renderer
    -  run 
        -   if setup succeeded run
        -   check for events 
        -   update game
        -   render game
    -  shutdown
        -   close renderer
        -   close window
        -   uninitialize sdl subsystems
2.  create spaceship
    1   
*/
#include"game.hpp"
int main(){
Game game;
if (game.initialize()) game.run();
game.shutdown();
}


