#include"game.hpp"

int main(){
    Game game;
    if (game.setup()) game.run();
    game.shutdown();
}


/*
--hello world
g++ src\main.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\hello_world.exe


--inputs
g++ src\main.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\inputs.exe

--ball class
g++ src\main.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\ball_class.exe

--paddle class
g++ src\main.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\paddle_class.exe
*/



/*--------------------------------------------------------------------------------------
--initial window
g++ src\*.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\initial_window.exe
build\initial_window.exe
--------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------
--object class
g++ src\*.cpp -Llib -Iinclude -lSDL3 -lSDL3_image -o build\objects.exe
build\objects.exe
--------------------------------------------------------------------------------------*/