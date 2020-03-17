#include "bullet.h"

//Private functions


//Constructors
Bullet::Bullet(){

}
Bullet::Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movementSpeed){
	this->sprite.setTexture(*texture);

	this->sprite.setPosition(posX, posY);
	this->sprite.scale(0.03f, 0.03f);
	this->direction.x = dirX;
	this->direction.y = dirY;
	this->movementSpeed = movementSpeed;
}
Bullet::~Bullet(){

}

//Accessors
const sf::FloatRect Bullet::getBounds() const{
	return this->sprite.getGlobalBounds();
}

//Functions
void Bullet::update(){
	//Movement
	this->sprite.move(this->movementSpeed * this->direction);
}
void Bullet::render(sf::RenderTarget* target){
	target->draw(this->sprite);
}