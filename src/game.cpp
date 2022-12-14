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
	this->player.setPosition(250.0f, 480.0f);
	this->player.setFillColor(sf::Color::Cyan);

	// INIT THE BALL
	this->ball.setRadius(5.0f);
	//this->ball.setOrigin(2.5f, 2.5f);
	this->ball.setPosition(250.0f, 250.0f);
	this->ball.setFillColor(sf::Color::White);

	// INIT THE BLOCKS
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 8; j++)
			{
				this->blocks[this->iblocks].setSize(sf::Vector2f(60.0f, 20.0f));
				this->blocks[this->iblocks].setPosition(61.0f * i + 5, 21.0f * j + 5);
				this->blocks[this->iblocks].setFillColor(sf::Color::Green);
				this->iblocks++;
			}

}

bool isCollide(sf::CircleShape s1, sf::RectangleShape s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

bool newIntersection(sf::FloatRect circle, sf::FloatRect rectangle)
{
	// Rectangles with negative dimensions are allowed, so we must handle them correctly

	// Compute the min and max of the circle on both axes
	float r1MinX = std::min(circle.left, (circle.left + circle.width));
	float r1MaxX = std::max(circle.left, (circle.left + circle.width));
	float r1MinY = std::min(circle.top, (circle.top + circle.height));
	float r1MaxY = std::max(circle.top, (circle.top + circle.height));

	// Compute the min and max of the second rectangle on both axes
	float r2MinX = std::min(rectangle.left, (rectangle.left + rectangle.width));
	float r2MaxX = std::max(rectangle.left, (rectangle.left + rectangle.width));
	float r2MinY = std::min(rectangle.top, (rectangle.top + rectangle.height));
	float r2MaxY = std::max(rectangle.top, (rectangle.top + rectangle.height));

	// Compute the intersection boundaries
	float interLeft = std::max(r1MinX, r2MinX);
	float interTop = std::max(r1MinY, r2MinY);
	float interRight = std::min(r1MaxX, r2MaxX);
	float interBottom = std::min(r1MaxY, r2MaxY);

	// If the intersection is valid (positive non zero area), then there is an intersection
	if ((interLeft < interRight) && (interTop < interBottom))
	{
		std::cout << "Left Side: " << interLeft << std::endl;
		std::cout << "Right Side: " << interRight << std::endl;
		std::cout << "Top Side: " << interTop << std::endl;
		std::cout << "Bottom Side: " << interBottom << std::endl;
		/*std::cout << "RECT MinX: " << r2MinX << std::endl;
		std::cout << "RECT MaxX: " << r2MaxX << std::endl;
		std::cout << "RECT MinY: " << r2MinY << std::endl;
		std::cout << "RECT MaxY: " << r2MaxY << std::endl;*/
		std::cout << "R-L Side: " << r2MaxX - interLeft << std::endl;
		std::cout << '\n' << std::endl;
		return true;
	}
	else
	{
		return false;
	}
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

	// BALL MOVE --------------------------------------------
	this->ball.move(dx, dy);

	// PADDLE AND BALL COLLISION - LEFT --------------------------
	sf::FloatRect left_p(this->player.getPosition(), this->player.getSize()/2.0f);
	if (this->ball.getGlobalBounds().intersects(left_p))
	{
		float gbBall = this->ball.getGlobalBounds().left;
		float gbPlayer = left_p.left + left_p.width;
		std::cout << "GB COORDS L: " << gbPlayer - gbBall << std::endl;

		dx = 1.0f;
		dx += (gbPlayer - gbBall)/6;

		if (dx > 0) dx *= -1.0f;
		dy = -dy;
		this->ball.setPosition(this->ball.getPosition().x, this->ball.getPosition().y - 3.0f);
	}
		
	// PADDLE AND BALL COLLISION - RIGHT --------------------------
	sf::FloatRect right_p(sf::Vector2f(this->player.getPosition().x + 50.0f, this->player.getPosition().y), this->player.getSize() / 2.0f);
	if (this->ball.getGlobalBounds().intersects(right_p))
	{
		float gbBall = this->ball.getGlobalBounds().left;
		float gbPlayer = this->player.getGlobalBounds().left + this->player.getGlobalBounds().width;
		std::cout << "GB COORDS R: " << gbPlayer - gbBall << std::endl;

		dx = 1.0f;
		dx += (gbPlayer - gbBall) / 6;

		if (dx < 0) dx*=-1.0f;
		dy = -dy;
		this->ball.setPosition(this->ball.getPosition().x, this->ball.getPosition().y - 3.0f);
	}

	// BALL AND BLOCK COLLISION
	for(int i=0;i<iblocks;i++)
		if (isCollide(this->ball, blocks[i])) {blocks[i].setPosition(-100, 0); dy=-dy;}


	// MOVE PADDLE -----------------------------------------
	this->player.setPosition(sf::Mouse::getPosition(*this->window).x, this->player.getPosition().y);

	// BALL WINDOW COLLISION && RESET ---------------------------------
	sf::Vector2f bpos = this->ball.getPosition();
	if (bpos.x<0 || bpos.x>this->window->getSize().x - this->ball.getRadius()) dx = -dx;
	if (bpos.y<0) dy = -dy;
	else if (bpos.y > this->window->getSize().y - this->ball.getRadius())
		this->ball.setPosition(250.0f, 250.0f);

	// PADDLE WINDOW COLLISION -------------------------------
	sf::FloatRect playerBounds = this->player.getGlobalBounds();
	// left side collisions
	if (playerBounds.left <= 0.0f)
		this->player.setPosition(0.0f, this->player.getPosition().y);
	// right side collisions
	else if(playerBounds.left + playerBounds.width >= this->window->getSize().x)
		this->player.setPosition(this->window->getSize().x - 100.0f, this->player.getPosition().y);

	/*std::cout << "MOUSE POS: " << sf::Mouse::getPosition(*this->window).x 
						<< " " << sf::Mouse::getPosition(*this->window).y << std::endl;*/
}

void Game::render()
{
	this->window->clear();

	//DRAW GAMEOBJECTS
	this->window->draw(this->player);
	this->window->draw(this->ball);
	for (int i = 0; i < this->iblocks; i++)
	{
		this->window->draw(this->blocks[i]);
	}

	this->window->display();
}
