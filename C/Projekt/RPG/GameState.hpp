#pragma once

#include "state.hpp"

class GameState : public State{
private:
	//Variables
	Player* player;

	//Functions
	void initKeybinds();
	void initTextures();
	void initPlayers();
public:
	//Constructors
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();
	//Accessors

	//Functions
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};