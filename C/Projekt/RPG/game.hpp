#pragma once

#include "MainMenuState.hpp"

class Game{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock; //delta time clock
	float dt; //delta time

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Init functions
	void initWindow();
	void initStates();
	void initKeys();
public:
	//constructors
	Game();
	~Game();
	//Accessors

	//Functions

	//Regular
	void endApplication();

	//Update
	void updateSFMLEvents();
	void updateDt();
	void update();

	//Render
	void render();

	//Core
	void run();
};