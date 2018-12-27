#include "Spawner.h"

Spawner::Spawner()
{
}

void Spawner::Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize, sf::Time Elapsed, int& Score)
{
	if (m_vecEnemys.size() < 3)
	{
		//Get Starting Position
		float x, y;
		x = mapSize.x / 2 * pixelSize.x;
		y =  	  0		  *	pixelSize.y;

		addEnemy(x, y);
	}

	for (auto &i : m_vecEnemys)
	{
		i.Update(map, mapSize, pixelSize, Elapsed);
	}

	//Out Of Map Check
	std::vector<Enemy>::iterator iter;
	for (iter = m_vecEnemys.begin(); iter != m_vecEnemys.end();)
	{
		if (int(iter->getEnemy()->getPosition().y / pixelSize.y) == mapSize.y - 1)
		{
			iter = m_vecEnemys.erase(iter);

			//Remove From Score
			Score -= 1;
		}
		else
		{
			iter++;
		}
	}
}

void Spawner::Draw(sf::RenderWindow* window)
{
	for (auto &i : m_vecEnemys)
	{
		i.Draw(window);
	}
}

void Spawner::addEnemy(float x, float y)
{
	Enemy enemy(x, y, rand() % 100 + 100);
	m_vecEnemys.push_back(enemy);
}
