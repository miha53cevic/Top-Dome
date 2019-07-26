#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Enemy.h"

class Spawner
{
public:
	Spawner();
	~Spawner() = default;

	void Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize, sf::Time Elapsed, int& Score);
	void Draw(sf::RenderWindow* window);

	void addEnemy(float x, float y);

private:
	std::vector<Enemy> m_vecEnemys;

};

