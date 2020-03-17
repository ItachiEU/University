#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Player{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementspeed;

	float attackCooldown;
	float attackCooldownMax;

	//Private functions
	void initVariables();
	void initSprite();
	void initTexture();
public:
	Player();
	virtual ~Player();

	//Accessors
	const sf::Vector2f& getPos() const;

	//Functions
	void move(float dirX, float dirY);

	bool canAttack();
	void updateCooldown();
	void update();
	void render(sf::RenderTarget* target);
};
