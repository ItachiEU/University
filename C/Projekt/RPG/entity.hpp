#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Entity{
private:
	void initVariables();
protected:
	//Variables
	sf::Texture* texture;
	sf::Sprite* sprite;

	float movementSpeed;

public:
	//Constructors
	Entity();
	virtual ~Entity();
	//Accessors

	//Component functions
	void createSprite(sf::Texture* texture);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};