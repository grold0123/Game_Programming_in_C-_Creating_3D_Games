#include"game.hpp"

int main(){
    Game game;
    if (game.setup()) game.run();
    game.shutdown();
}


/*
initial window
g++ src\*.cpp -Iinclude -Llib -lSDL3 -lSDL3_image -o build\initial_window.exe

draw objects with rect values
g++ src\*.cpp -Iinclude -Llib -lSDL3 -lSDL3_image -o build\object_rects.exe

move objects
g++ src\*.cpp -Iinclude -Llib -lSDL3 -lSDL3_image -o build\move_object.exe
*/


