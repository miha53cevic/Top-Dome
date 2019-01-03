#pragma once
#include <SFML/Graphics.hpp>

#include "Enemy.h"

class normEnemy : public Enemy
{
public:
	normEnemy(float posX, float posY, float fSpeed = 50.0f);

	void Draw(sf::RenderWindow* window);
	void Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize, sf::Time Elapsed);

private:

};

