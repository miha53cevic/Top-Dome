#include "game.h"

int main()
{
	Game game(sf::Vector2u(1280, 720), "TopDome SFML");

	while (!game.getWindow() -> IsDone())
	{
		int* Score = game.getWorld()->getScore();

		//if (*Score > 0)
		//{
			game.HandleInput();
			game.Update();
			game.Render();
			game.RestartClock();
		//}
	}

	return 0;
}