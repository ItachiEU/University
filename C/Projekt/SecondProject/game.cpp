#include "game.h"

//Private functions
void Game::initWindow(){
	this->videoMode = sf::VideoMode(1200, 800);
	this->window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}
void Game::initVariables(){
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
	this->points = 0;
}
void Game::initFont(){
	if(!this->font.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/Fonts/shangri-la.ttf"))
			std::cout<<"Error loading font\n";
}
void Game::initText(){
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(48);
	this->guiText.setString("test");

	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(72);
	this->endGameText.setPosition(500, 300);
	this->endGameText.setString("GAME OVER");
}
//Constructors and Destructors
Game::Game(){
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}
Game::~Game(){
	delete this->window;
}
//Accessors
const bool& Game::getEndGame() const{
	return this->endGame;
}

//Functions
void Game::spawnSwagBalls(){
	//Timer
	if(this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else{
		if(this->swagBalls.size() < this->maxSwagBalls){
				this->swagBalls.push_back(Ball(this->window, this->randomizeType()));
				this->spawnTimer = 0.f;
			}
		}
}
const int Game::randomizeType(){
	int type = BallTypes::DEFAULT;
	int randValue = rand()%100+1;

	if(randValue <=10)
		type = BallTypes::DAMAGING;
	else
	if(randValue <=20)
		type = BallTypes::HEALING;
	return type;
}
void Game::updateCollision(){
	//Check collision
	for(size_t i = 0; i < this->swagBalls.size(); i++){
		if(this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds())){
			
			switch(this->swagBalls[i].getType()){
				case BallTypes::DEFAULT:
					this->points++;
					break;
				case BallTypes::DAMAGING:
					this->player.takeDamage(1);
					break;
				case BallTypes::HEALING:
					this->player.gainHealth(1);
					break;
			}

			//Remove the ball
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
}
void Game::updateGui(){
	std::stringstream ss;

	ss << "Points: " << this->points << "\n " << "Health: "<< this->player.getHp() << " / "
	<< this->player.getHpMax();

	this->guiText.setString(ss.str());
}
void Game::updateStatus(){
	if(player.getHp()<=0)
		this->endGame = true;
}
void Game::update(){
	this->pollEvents();

	this->updateStatus();

	if(this->endGame == false){
		this->spawnSwagBalls();

		this->player.update(this->window);

		this->updateCollision();

		this->updateGui();
	}

}
void Game::renderGui(sf::RenderTarget* target){
	target->draw(this->guiText);
}
void Game::render(){
	this->window->clear();

	//Render stuff
	for(auto i : this->swagBalls){
		i.render(this->window);
	}

	this->player.render(this->window);

	//Render Gui
	this->renderGui(this->window);

	//Render end text
	if(this->endGame){
		this->window->draw(this->endGameText);
	}

	this->window->display();

}
const bool Game::running() const{
	return this->window->isOpen();
}
void Game::pollEvents(){
	while(this->window->pollEvent(this->sfmlEvent)){
		switch(this->sfmlEvent.type){
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if(this->sfmlEvent.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
			default:
				break;
		}
	}
}