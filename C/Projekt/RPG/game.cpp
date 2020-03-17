#include "game.hpp"


//Private functions
void Game::initWindow(){

	std::ifstream ifs("Config/window.in");	
	std::string title = "NONE";
	sf::VideoMode window_bounds(800,600);
	int framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if(ifs.is_open()){
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}

	ifs.close();

	this->window = new sf::RenderWindow(window_bounds,title, sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}
void Game::initKeys(){
	std::ifstream ifs("Config/supported_keys.in");

	if(ifs.is_open()){
		std::string key = "";
		int value = 0;
		while(ifs >> key >> value){
			this->supportedKeys[key] = value;
		}
	}
	ifs.close();

	//debug
	for(auto i : this->supportedKeys)
		std::cout<< i.first <<" " << i.second <<std::endl;

}
void Game::initStates(){
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}
//Constructors
Game::Game(){
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game(){

	delete this->window;

	while(!this->states.empty()){
		delete this->states.top();
		this->states.pop();
	}
}

//Accessors


//Functions

//Regular
void Game::endApplication(){
	std::cout<< "Ending Application! \n";
}

//Update
void Game::update(){
	this->updateSFMLEvents();

	if(!this->states.empty()){
		this->states.top()->update(this->dt);

		if(this->states.top()->getQuit()){
			//Probably wanna do something here first: saving etc
			this->states.top()->endState();

			delete this->states.top();
			this->states.pop();
		}
	}
	else{
		//App quiting

		this->endApplication();
		this->window->close();
	}
}
void Game::updateDt(){ //Keeping track of elapsed time in the while loop
	this->dt = this->dtClock.restart().asSeconds();
}
void Game::updateSFMLEvents(){
	while(this->window->pollEvent(this->sfEvent)){
		if(this->sfEvent.type == sf::Event::Closed){
			this->window->close();
		}
	}
}

//Render
void Game::render(){
	this->window->clear();
	//Draw stuff
	if(!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}

//Core
void Game::run(){
	while(this->window->isOpen()){
		this->updateDt();

		this->update();
		this->render();
	}
}