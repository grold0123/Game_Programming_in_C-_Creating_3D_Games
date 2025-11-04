/*
pong
*/
#include<iostream>
#include"game.hpp"

int main(){
	/*
	create game instance
	setup game instance
		initialize SDL
			create game window , game renderer		
	if setup success run game 
		get input
		update game
		render
	close game
	*/
	Game GAME;	
	if (GAME.setup()) GAME.run();
	GAME.shutdown();
}
