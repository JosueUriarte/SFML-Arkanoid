#include <SFML/Graphics.hpp>

#include <Game.hpp>

int main(int argc, char* argv[])
{
	// CREATE WINDOW ------------------
	Game* game = new Game("ARKANOID");
	
	// GAME LOOP ---------------------
	while (game->isRunning())
	{
		game->update();
		game->handleEvents();
		game->render();
	}

	// EXIT OUT SAFELY
	delete game;
	return 0;
}