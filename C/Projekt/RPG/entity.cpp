#include "entity.hpp"


//private functions
void Entity::initVariables(){
	this->texture = nullptr;
	this->sprite = nullptr;
	this->movementSpeed = 100.f;
}

//Constructors
Entity::Entity(){
	this->initVariables();
}
Entity::~Entity(){
	delete this->sprite;
}
//Accessors

//Component functions
void Entity::createSprite(sf::Texture* texture){
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
	this->sprite->setScale(0.05f, 0.05f);
}

//Functions
void Entity::setPosition(const float x, const float y){
	if(this->sprite)
		this->sprite->setPosition(x, y);
}
void Entity::move(const float& dt, const float x, const float y){
	if(this->sprite)
		this->sprite->move(x * this->movementSpeed * dt, y * this->movementSpeed * dt);
}
void Entity::update(const float& dt){

}
void Entity::render(sf::RenderTarget* target){
	if(this->sprite)
		target->draw(*this->sprite);
}