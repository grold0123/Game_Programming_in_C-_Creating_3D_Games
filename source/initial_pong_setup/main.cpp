/*====================================
initial_pong_setup
====================================*/
#include<game/game.h>
int main(){
	Game game;
	if(game.initialize()) game.run();	
	game.shutdown();
}