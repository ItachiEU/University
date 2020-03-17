#include "game.h"

int main(){
	srand(static_cast<unsigned>(time(NULL)));

	//Initialize Game object

	Game game;

	//Game loop

	while(game.running() /*&& !game.getEndGame()*/){
		game.update();
		game.render();
	}
	
	return 0;
}