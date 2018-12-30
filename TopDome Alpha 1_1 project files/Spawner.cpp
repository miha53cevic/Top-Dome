#include "Spawner.h"

Spawner::Spawner()
{
	m_NumberOfEnemies = 3;
	m_bWaveOver = true;
}

void Spawner::Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize, sf::Time Elapsed, int& Score, std::vector<Bullet>& vecBullets, Player* m_player)
{
	if (m_vecEnemys.size() < m_NumberOfEnemies && m_bWaveOver)
	{
		//Get Starting Position
		float x, y;
		x = mapSize.x / 2 * pixelSize.x;
		y =  	  0		  *	pixelSize.y;

		addNormEnemy(x, y);

		//Chance to spawn quickEnemys
		if (rand() % 256 >= 200)
		{
			addQuickEnemy(x, y);
		}
	}
	else
	{
		m_bWaveOver = false;
	}

	for (auto &i : m_vecEnemys)
	{
		i->Update(map, mapSize, pixelSize, Elapsed);
	}

	//Out Of Map Check
	std::vector<Enemy*>::iterator iter;
	for (iter = m_vecEnemys.begin(); iter != m_vecEnemys.end();)
	{
		if (int((*iter)->getEnemy()->getPosition().y / pixelSize.y) == mapSize.y - 1)
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
	
	//Enemy and Bullet Collision
	if (!vecBullets.empty())
	{
		std::vector<Bullet>::iterator bulletIter;

		for (iter = m_vecEnemys.begin(); iter != m_vecEnemys.end();)
		{
			bool Collision = false;

			sf::FloatRect enemy = (*iter)->getEnemy()->getGlobalBounds();

			for (bulletIter = vecBullets.begin(); bulletIter != vecBullets.end();)
			{
				sf::FloatRect bullet = bulletIter->getBullet()->getGlobalBounds();

				if (bullet.intersects(enemy))
				{
					//Delete Enemy
					iter = m_vecEnemys.erase(iter);

					//Delete Bullet
					bulletIter = vecBullets.erase(bulletIter);

					Collision = true;
				}
				else
				{
					bulletIter++;
				}
			}
			if (!Collision)
			{
				iter++;
			}
		}
	}

	//Enemy and Player Collision
	sf::FloatRect player = m_player->m_player.getGlobalBounds();

	for (iter = m_vecEnemys.begin(); iter != m_vecEnemys.end(); iter++)
	{
		sf::FloatRect curEnemy = (*iter)->getEnemy()->getGlobalBounds();

		if (player.intersects(curEnemy))
		{
			m_player->changeSpeed(125.0f);
		}
	}
	

	//Is Wave Over
	if (m_vecEnemys.empty())
	{
		m_bWaveOver = true;

		m_NumberOfEnemies += 1;

		//Reset Player Speed after Wave
		m_player->changeSpeed(200.0f);
	}
}

void Spawner::Draw(sf::RenderWindow* window)
{
	for (auto &i : m_vecEnemys)
	{
		i->Draw(window);
	}
}

void Spawner::addNormEnemy(float x, float y)
{
	Enemy* enemy = new normEnemy(x, y, rand() % 100 + 100);
	m_vecEnemys.push_back(enemy);
}

void Spawner::addQuickEnemy(float x, float y)
{
	Enemy* enemy = new quickEnemy(x, y, rand() % 150 + 200);
	m_vecEnemys.push_back(enemy);
}

void Spawner::addTankEnemy(float x, float y)
{
	Enemy* enemy = new normEnemy(x, y, rand() % 100 + 100);
	m_vecEnemys.push_back(enemy);
}

void Spawner::Reset()
{
	m_NumberOfEnemies = 3;
	m_bWaveOver = true;

	m_vecEnemys.clear();
}

int Spawner::getNumberOfEnemies()
{
	return m_NumberOfEnemies;
}
