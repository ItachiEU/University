#ifndef GAME_HPP
#define GAME_HPP

#include<iostream>
#include<vector>
#include<sstream>
#include<ctime>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>

/*
	Class that acts as the game engine
*/

class Game{
private:
	//Variables

	//Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game logic
	unsigned int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	int health;
	bool endGame;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Private functions
	void initText();
	void initFonts();
	void initVariables();
	void initEnemies();
	void initWindow();
public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;
	//Functions
	void pollEvents();
	void spawnEnemy();

	void updateMousePositions();
	void updateEnemies();
	void update();
	void updateText();

	void render();
	void renderEnemies(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);

};

#endif