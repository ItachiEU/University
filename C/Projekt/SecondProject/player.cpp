#include "player.h"

//Private
void Player::initShape(){
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}
void Player::initVariables(){
	this->movementSpeed = 5.f;
	this->hpMax = 3;
	this->hp = hpMax;
}

Player::Player(float x, float y){
	//setting player position
	this->shape.setPosition(x, y);
	
	//Initializing stuff
	this->initVariables();
	this->initShape();
}
Player::~Player(){

}

//Accessors
const sf::RectangleShape& Player::getShape() const{
	return this->shape;
}
const int& Player::getHp() const{
	return this->hp;
}
const int& Player::getHpMax() const{
	return this->hpMax;
}

//Functions
void Player::updateWindowBoundsCollision(sf::RenderTarget* target){
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();
	//Left
	if(playerBounds.left < 0.f)
		this->shape.setPosition(0.f,playerBounds.top);
	playerBounds = this->shape.getGlobalBounds();
	//Right
	if(playerBounds.left+playerBounds.width > target->getSize().x)
		this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
	playerBounds = this->shape.getGlobalBounds();
	//Top
	if(playerBounds.top < 0.f)
		this->shape.setPosition(std::min(playerBounds.left,target->getSize().x-playerBounds.width), 0.f);
	playerBounds = this->shape.getGlobalBounds();
	//Down
	if(playerBounds.top+playerBounds.height > target->getSize().y)
		this->shape.setPosition(std::min(playerBounds.left, target->getSize().x-playerBounds.width), target->getSize().y - playerBounds.height);
	playerBounds = this->shape.getGlobalBounds();
}

void Player::takeDamage(const int damage){
	if(this->hp > 0)
		this->hp -= damage;
	if(this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health){
	if(this->hp < this->hpMax)
		this->hp += health;
	if(this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void Player::updateInput(){
	//Keyboard input
	//Left
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		this->shape.move(-this->movementSpeed, 0.f);
	}//Right
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		this->shape.move(this->movementSpeed, 0.f);
	}//Up
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		this->shape.move(0.f, -this->movementSpeed);
	}//Down
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		this->shape.move(0.f, this->movementSpeed);
	}
}
void Player::update(sf::RenderTarget* target){
	//Update movement
	this->updateInput();

	//Window bounds collision
	this->updateWindowBoundsCollision(target);

}
void Player::render(sf::RenderTarget* target){
	target->draw(this->shape);
}