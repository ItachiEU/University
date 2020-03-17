#pragma once

#include<iostream>
#include<ctime>
#include<fstream>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button{
private:
	//Variables
	short unsigned buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	//Init functions

public:
	//Constructors
	Button(float x, float y, float width, float height, sf::Font* font, std::string text,
		sf::Color idleColor,sf::Color hoverColor,sf::Color activeColor);
	virtual ~Button();
	//Accessors
	const bool isPressed() const;

	//Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};