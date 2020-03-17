#include "ball.hpp"
//Private

void Ball::initShape(sf::RenderTarget* target){
	this->shape.setRadius(static_cast<float>(rand()%10+10));

	sf::Color color;

	switch(this->type){
		case DEFAULT:
			color = sf::Color(rand()%255+1, rand()%255+1, rand()%255+1);
			break;
		case DAMAGING:
			color = sf::Color::Red;
			this->shape.setOutlineColor(sf::Color::White);
			this->shape.setOutlineThickness(2.f);
			break;
		case HEALING:
			color = sf::Color::Green;
			this->shape.setOutlineColor(sf::Color::White);
			this->shape.setOutlineThickness(2.f);
			break;	
	}

	this->shape.setFillColor(color);
	this->shape.setPosition(
		sf::Vector2f(static_cast<float>(rand()%target->getSize().x-this->shape.getGlobalBounds().width),
		 static_cast<float>(rand()%target->getSize().y-this->shape.getGlobalBounds().height)));
}

//Constructors
Ball::Ball(sf::RenderTarget* target, int type){
	
	this->type = type;

	this->initShape(target);
}

Ball::~Ball(){

}
//Accessors

const sf::CircleShape Ball::getShape() const{
	return this->shape;
}
const int& Ball::getType() const{
	return this->type;
}

//Functions

void Ball::render(sf::RenderTarget* target){
	target->draw(this->shape);
}

void Ball::update(){

}