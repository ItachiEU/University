#include "game.hpp"

int main(){
	//Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init game engine
	Game game;

	//Game loop
	while(game.running() && !game.getEndGame()){
		//Update
		game.update();
		//Render
		game.render();
	}
	//end of application
	return 0;
}