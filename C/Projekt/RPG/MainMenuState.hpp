#pragma once

#include "GameState.hpp"
#include "button.hpp"

class MainMenuState : public State{
private:
	//Variables
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	//Functions
	void initFonts();
	void initKeybinds();
	void initButtons();
	void initBackground();
	void initVariables();
public:
	//Constructors
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();
	//Accessors

	//Functions
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);

	void render(sf::RenderTarget* target = nullptr);
	void renderButtons(sf::RenderTarget* target=nullptr);
};