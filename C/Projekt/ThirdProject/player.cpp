#include "player.h"
//Private functions
void Player::initTexture(){
	//Load a texture from file
	if(!this->texture.loadFromFile("Textures/ship.png")){
		std::cout<<"FAILED TO LOAD TEXTURE\n";
	}
}
void Player::initVariables(){
	this->movementspeed = 5.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}
void Player::initSprite(){
	//set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(0.1f, 0.1f);
}

//Constructors
Player::Player(){
	this->initTexture();
	this->initSprite();
	this->initVariables();
}
Player::~Player(){

}

//Accessors
const sf::Vector2f& Player::getPos() const{
	return this->sprite.getPosition();
}

//Functions
void Player::move(float dirX, float dirY){
	this->sprite.move(this->movementspeed * dirX, this->movementspeed * dirY);
}
bool Player::canAttack(){
	if(this->attackCooldown >= attackCooldownMax){
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}
void Player::updateCooldown(){
	if(this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 1.f;
}
void Player::update(){
	this->updateCooldown();
}
void Player::render(sf::RenderTarget* target){
	target->draw(this->sprite);
}