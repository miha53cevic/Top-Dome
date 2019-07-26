#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Enemy.h"
#include "normEnemy.h"
#include "quickEnemy.h"
#include "tankEnemy.h"

#include "Player.h"

#include "Bullet.h"

#include "PowerUp.h"

class Spawner
{
public:
	Spawner();
	~Spawner() = default;

	void Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize, sf::Time Elapsed, int& Score, std::vector<Bullet>& vecBullets, Player* m_player);
	void Draw(sf::RenderWindow* window);

	void addNormEnemy(float x, float y);
	void addQuickEnemy(float x, float y);
	void addTankEnemy(float x, float y);

	void Reset();

	int getNumberOfEnemies();

private:
	std::vector<Enemy*> m_vecEnemys;

	int m_NumberOfEnemies;
	bool m_bWaveOver;

	PowerUp m_powerUp;
};

