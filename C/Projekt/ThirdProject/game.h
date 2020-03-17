#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include "player.h"
#include "bullet.h"

class Game{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Player
	Player* player;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	
	//Private functions
	void initTextures();
	void initWindow();
	void initPlayer();
public:
	Game();
	~Game();

	//Functions
	void run();
	void pollEvents();
	void updateInput();
	void updateBullets();
	void update();
	void render();
};