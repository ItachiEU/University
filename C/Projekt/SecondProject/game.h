#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include "player.h"
#include "ball.hpp"

class Game{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event sfmlEvent;
	Player player;

	//Game logic
	bool endGame;
	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	std::vector<Ball> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;

	void initWindow();
	void initFont();
	void initText();
	void initVariables();
public:
	//Constructors adn Destructors
	Game();
	~Game();
	//Accessors
	const bool& getEndGame() const;
 
	//Modifiers

	//Functions
	const bool running() const;
	void pollEvents();
	void spawnSwagBalls();
	const int randomizeType();
	void updateCollision();
	void update();
	void updateGui();
	void updateStatus();

	void render();
	void renderGui(sf::RenderTarget* target);
};


#endif