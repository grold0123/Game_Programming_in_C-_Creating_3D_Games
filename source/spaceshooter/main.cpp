/*************************************
spaceshooter
**************************************/
#include<iostream>
#include"game.hpp"
//149
int main(){
	Game Game;
	if (Game.Initialize()) Game.Run();
	Game.Shutdown();
	return 0;
}
