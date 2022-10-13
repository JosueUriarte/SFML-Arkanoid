#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Game.hpp"

Game::Game(char* title)
{
	// CREATE WINDOW
	this->v_mode.height = 500;
	this->v_mode.width = 500;
	this->window = new sf::RenderWindow(v_mode, title, sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

	// INIT THE PLAYER
	this->player.setSize(sf::Vector2f(100.0f, 10.0f));
	this->player.setOrigin(50.0f, 5.0f);
	this->player.setPosition(250.0f, 480.0f);
	this->player.setFillColor(sf::Color::Magenta);

	// INIT THE BALL
	this->ball.setRadius(5.0f);
	this->ball.setOrigin(2.5f, 2.5f);
	this->ball.setPosition(250.0f, 250.0f);
	this->ball.setFillColor(sf::Color::White);

	// INIT THE BLOCKS
}

Game::~Game()
{
	delete this->window;
}

void Game::handleEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window->close();

		else if (this->ev.type == sf::Event::KeyPressed)
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
	}
}

void Game::update()
{
	// PADDLE AND BALL COLLISION
	if(this->ball.getGlobalBounds().intersects(this->player.getGlobalBounds()))
		dy = -dy;

	// BALL WINDOW COLLISION
	sf::Vector2f bpos = this->ball.getPosition();
	if (bpos.x<0 || bpos.x>this->window->getSize().x - this->ball.getRadius()) dx = -dx;
	if (bpos.y<0 || bpos.y>this->window->getSize().y - this->ball.getRadius()) dy = -dy;

	// PADDLE WINDOW COLLISION
	sf::FloatRect playerBounds = this->player.getGlobalBounds();
	if (playerBounds.left <= 0.0f)
		this->player.setPosition(0.0f + 50.0f, this->player.getPosition().y);
	else if(playerBounds.left + playerBounds.width >= this->window->getSize().x)
		this->player.setPosition(this->window->getSize().x - 50.0f, this->player.getPosition().y);
	
	// MOVE PADDLE
	this->player.setPosition(sf::Mouse::getPosition(*this->window).x, this->player.getPosition().y);

	// BALL MOVE
	this->ball.move(dx, dy);

	/*std::cout << "MOUSE POS: " << sf::Mouse::getPosition(*this->window).x 
						<< " " << sf::Mouse::getPosition(*this->window).y << std::endl;*/
}

void Game::render()
{
	this->window->clear();

	//DRAW GAMEOBJECTS
	this->window->draw(this->player);
	this->window->draw(this->ball);

	this->window->display();
}
