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
	sf::RectangleShape blocks[100];

	// Functions
	void update();
	void handleEvents();
	void render();

	// Accessors
	bool isRunning() { return window->isOpen(); }

private:
	int iblocks = 0;
	float dx = 2.0f, dy = 4.0f;
	sf::RenderWindow* window = nullptr;
	sf::VideoMode v_mode;
	sf::Event ev;
};