#include "game.hpp"
//private functions
void Game::initVariables(){
	this->window = NULL;

	//Game logic
	this->points = 0;
	this->enemySpawnTimerMax = 50.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
	this->health = 10;
	this->endGame = false;
}

void Game::initWindow(){
	this->videoMode.height = 800;
	this->videoMode.width = 1200;
	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}
void Game::initFonts(){
	this->font.loadFromFile("/home/itachi/Desktop/Programowanie/C/Projekt/Fonts/HangedLetters.ttf");
}
void Game::initText(){
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(48);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}
void Game::initEnemies(){
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
}

//Constructors / Destructors
Game::Game(){
	this->initVariables();
	this->initWindow();
	this->initEnemies();
	this->initFonts();
	this->initText();
}

Game::~Game(){
	delete this->window;
}
//Accessors
const bool Game::running() const{
	return this->window->isOpen();
}
const bool Game::getEndGame() const{
	return this->endGame;
}

//Functions

void Game::spawnEnemy(){
	//Spawning the enemy and setting their color and positions ( random )
	this->enemy.setPosition(static_cast<float>(rand()%static_cast<int>((this->window->getSize().x-this->enemy.getSize().x))), 0.f);

	//Randomize enemy type
	int type = rand() % 5;
	switch(type){
		case 0:
			this->enemy.setFillColor(sf::Color::Magenta);
			this->enemy.setSize(sf::Vector2f(10.f, 10.f));
			break;
		case 1:
			this->enemy.setFillColor(sf::Color::Blue);
			this->enemy.setSize(sf::Vector2f(30.f, 30.f));
			break;
		case 2:
			this->enemy.setFillColor(sf::Color::Cyan);
			this->enemy.setSize(sf::Vector2f(50.f, 50.f));
			break;
		case 3:
			this->enemy.setFillColor(sf::Color::Red);
			this->enemy.setSize(sf::Vector2f(70.f, 70.f));
			break;
		case 4:
			this->enemy.setFillColor(sf::Color::Green);
			this->enemy.setSize(sf::Vector2f(100.f, 100.f));
			break;
		default:
			this->enemy.setFillColor(sf::Color::Yellow);
			this->enemy.setSize(sf::Vector2f(100.f, 100.f));
			break;
	}

	//spawn the enemy
	this->enemies.push_back(this->enemy);
}

void Game::updateText(){
	std::stringstream ss;
	ss << "Points: " << this->points <<"\n" << "Health: " << this->health;
	this->uiText.setString(ss.str());
}

void Game::updateEnemies(){
	//Updating the timer for enemy spawning
	if((int)this->enemies.size() < this->maxEnemies){
		if(this->enemySpawnTimer >= this->enemySpawnTimerMax){
			//spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}
	//Moving and updating the enemies
	for(int i = 0; i<(int)this->enemies.size(); i++){
		this->enemies[i].move(0.f, 2.f);
		if(this->enemies[i].getPosition().y > this->window->getSize().y){
			this->enemies.erase(this->enemies.begin()+i);
			this->health--;
		}
	}
	//Check if clicked upon
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(!this->mouseHeld){
			this->mouseHeld = true;
			bool deleted = false;
			for(int i=0; i<(int)this->enemies.size() && deleted == false; i++){
				if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)){
					//Gain points
					if(this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 10;
					else 
					if(this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points +=7;
					else
					if(this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points +=5;
					else
					if(this->enemies[i].getFillColor() == sf::Color::Red)
						this->points +=3;
					else
					if(this->enemies[i].getFillColor() == sf::Color::Green)
						this->points +=1;

					deleted = true;
					this->enemies.erase(this->enemies.begin()+i);
				}
			}
		}
	}
	else{
		this->mouseHeld = false;
	}

}

void Game::renderEnemies(sf::RenderTarget& target){

	//Rendering all the enemies
	for(auto &e : this->enemies){
		target.draw(e);
	}
}

void Game::renderText(sf::RenderTarget& target){
	target.draw(this->uiText);
}

void Game::pollEvents(){
	//Event polling
	while(this->window->pollEvent(this->ev)){
		switch(this->ev.type){
			case sf::Event::Closed: 
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if(this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
				break;
			default:
				break;
		}
	}
}

void Game::updateMousePositions(){
	//Updates the mouse position relative to the window
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	//Updates the mouse position relative to the view
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update(){

	this->pollEvents();

	if(!this->endGame){
		//Update mouse position
		//Relative to the window
		this->updateMousePositions();

		this->updateEnemies();

		this->updateText();
	}
	//End game condition
	if(this->health <= 0)
			this->endGame = true;
}

void Game::render(){
	/*
		Renders the game objects 
	*/
	this->window->clear();
	//Draw game objects jere
	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	this->window->display();
}