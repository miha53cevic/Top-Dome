#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class World
{
public:
	World(sf::Vector2u screenSize);
	~World() = default;

	void Draw(sf::RenderWindow* window);
	void Update();

	std::string* getMap();
	sf::Vector2i getMapSize();
	sf::Vector2i getPixelSize();
	int* getScore();

private:
	std::string m_Map;

	sf::Vector2i m_MapSize;
	sf::Vector2i m_PixelSize;

	sf::RectangleShape m_block;

	sf::Vector2u m_ScreenSize;

	int m_Score;

	void Setup();
};

