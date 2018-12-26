#pragma once
#include "window.h"
#include "World.h"
#include "Player.h"

class Game
{
public:
	Game(const sf::Vector2u& l_size, const std::string& l_name);
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* getWindow();

	void RestartClock();

private:
	Window m_window;
	World m_world;
	Player m_player;

	sf::Clock m_clock;
	sf::Time m_elapsed;
};