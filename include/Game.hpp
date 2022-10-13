#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game
{
public:
	// Constructors / Destructors
	Game(char* title);
	~Game();

	// Game Objects
	sf::RectangleShape player;
	sf::CircleShape ball;
	std::vector<sf::RectangleShape*> blocks;

	// Functions
	void update();
	void handleEvents();
	void render();

	// Accessors
	bool isRunning() { return window->isOpen(); }

private:
	float dx = 6.0f, dy = 5.0f;
	sf::RenderWindow* window = nullptr;
	sf::VideoMode v_mode;
	sf::Event ev;
};