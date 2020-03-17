#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Bullet{
private:
	//Variables
	sf::Sprite sprite;
	sf::Vector2f direction;
	float movementSpeed;

public:

	//Constructors
	Bullet();
	Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movementSpeed);
	~Bullet();

	//Accessors
	const sf::FloatRect getBounds() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};