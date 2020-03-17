#include "MainMenuState.hpp"

//Private functions
void MainMenuState::initKeybinds(){
std::ifstream ifs("Config/mainmenustate_keybinds.in");

	if(ifs.is_open()){
		std::string key = "";
		std::string key2 = "";
		while(ifs >> key >> key2){
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();
}
void MainMenuState::initFonts(){
	if(!this->font.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/Fonts/shangri-la.ttf"))
		std::cout<<"ERROR: FAILED TO LOAD FONT IN MAIN MENU STATE!\n";
}
void MainMenuState::initButtons(){
	this->buttons["GAME_STATE"] = new Button(550, 150, 150, 50,
		&this->font, "New Game",
		sf::Color(100,100,100,200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["EXIT_STATE"] = new Button(550, 450, 150, 50,
		&this->font, "Quit",
		sf::Color(100,100,100,200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["SETTINGS"] = new Button(550, 300, 150, 50,
		&this->font, "Settings",
		sf::Color(100,100,100,200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}
void MainMenuState::initBackground(){
	this->background.setSize(sf::Vector2f((float)this->window->getSize().x, (float)this->window->getSize().x));
	if(!this->backgroundTexture.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/RPG/Resources/Images/Backgrounds/mainmenubackground.jpg")){
		std::cout<<"ERROR: FAILED TO LOAD BACKGROUND TEXTURE IN MAIN MENU\n";
	}
	this->background.setTexture(&this->backgroundTexture);
}
void MainMenuState::initVariables(){

}
//Constructors
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
 : State(window, supportedKeys, states){
 	this->initVariables();
 	this->initBackground();
 	this->initKeybinds();
 	this->initFonts();
 	this->initButtons();
}
MainMenuState::~MainMenuState(){
	auto it = this->buttons.begin();
	for(it = this->buttons.begin(); it != this->buttons.end(); ++it){
		delete it->second;
	}
}

//Accessors


//Functions
void MainMenuState::updateInput(const float& dt){

}
void MainMenuState::update(const float& dt){
	this->updateMousePositions();
	
	this->updateButtons();

	this->updateInput(dt);
}
void MainMenuState::updateButtons(){
	for(auto &it : this->buttons){
		it.second->update(this->mousePosView);
	}
	//Quit the game
	if(this->buttons["EXIT_STATE"]->isPressed()){
		this->endState();
	}
	//New game
	if(this->buttons["GAME_STATE"]->isPressed()){
		
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}
}

void MainMenuState::render(sf::RenderTarget* target){
	if(!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(target);

/*	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);*/
}
void MainMenuState::renderButtons(sf::RenderTarget* target){
	for(auto &it : this->buttons){
		it.second->render(target);
	}
}
