#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
	//CREATE WINDOW
	sf::RenderWindow window(sf::VideoMode(500, 500), "Test");
	sf::Event e;

	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}
	}

	return 0;
}