#include "player.hpp"

//priv functions
void Player::initVariables(){

}
void Player::initComponents(){

}

//Constructors
Player::Player(float x, float y, sf::Texture* texture){
	this->initVariables();
	this->initComponents();

	this->createSprite(texture);
	this->setPosition(x, y);
}
Player::~Player(){

}

//Accessors


//Functions
