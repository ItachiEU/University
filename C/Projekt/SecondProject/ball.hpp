#ifndef BALL_HPP
#define BALL_HPP

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

enum BallTypes {DEFAULT = 0, DAMAGING, HEALING, NROFTYPES};

class Ball{
private:
	sf::CircleShape shape;
	int type;

	void initShape(sf::RenderTarget* target);
public:
	Ball(sf::RenderTarget* target, int type);
	virtual ~Ball();

	//Accessor
	const sf::CircleShape getShape() const;
	const int& getType() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};


#endif