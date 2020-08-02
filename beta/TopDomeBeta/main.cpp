#include "game.h"

int main()
{
	Game game(sf::Vector2u(1280, 720), "TopDome SFML");

	while (!game.getWindow() -> IsDone())
	{
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}

	return 0;
}