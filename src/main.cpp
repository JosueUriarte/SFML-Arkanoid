#define _CRTDBG_MAP_ALLOC
#include <SFML/Graphics.hpp>
#include <memory>
#include <Game.hpp>

int main(int argc, char* argv[])
{
	// MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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
	return EXIT_SUCCESS;
}