#include "game.h"

//Private functions
void Game::initWindow(){
	this->videoMode = sf::VideoMode(1200, 800);
	this->window = new sf::RenderWindow(videoMode, "Game 3", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures(){
	this->textures["BULLET"] = new sf::Texture();
	if(!this->textures["BULLET"]->loadFromFile("Textures/bullet.png")){
		std::cout<<"FAILED TO LOAD BULLET TEXTURES\n";
	}
}
void Game::initPlayer(){
	this->player = new Player();
}
//Constructors

Game::Game(){
	this->initWindow();
	this->initTextures();
	this->initPlayer();
}
Game::~Game(){
	delete this->window;
	delete this->player;

	//Delete textures
	for(auto &i: this->textures)
		delete i.second;
	//Delete bullets
	for(auto *i: this->bullets){
		delete i;
	}
}

//Public Functions
void Game::run(){
	while(this->window->isOpen()){
		this->update();
		this->render();
	}
}
void Game::pollEvents(){
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
void Game::updateBullets(){
	unsigned int counter = 0;
	for(auto *i: this->bullets){
		i->update();
		//Bullet culling (top of screen)
		if(i->getBounds().top + i->getBounds().height < 0.f){
			//Delete the bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		++counter;
	}
}
void Game::updateInput(){
	//Move player
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		this->player->move(-1.f, 0.f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		this->player->move(1.f, 0.f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		this->player->move(0.f, -1.f);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		this->player->move(0.f, 1.f);
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()){
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::update(){
	this->pollEvents();

	//Move player
	this->updateInput();

	this->player->update();

	this->updateBullets();
}

void Game::render(){
	this->window->clear();
	//draw all the stuff

	//Render the player
	this->player->render(this->window);

	//Render bullets
	for(auto *i: this->bullets){
		i->render(this->window);
	}

	this->window->display();
}
