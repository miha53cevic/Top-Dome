#include "normEnemy.h"

normEnemy::normEnemy(float posX, float posY, float fSpeed)
	: Enemy(posX, posY, fSpeed)
{
	m_HP = 1;
}

void normEnemy::Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize, sf::Time Elapsed)
{
	//Get Tile Lambda Function
	auto getTile = [&](float x, float y) -> char
	{
		int nX, nY;
		nX = x / pixelSize.x;
		nY = y / pixelSize.y;

		return map[(nY * mapSize.x) + nX];
	};

	//Gravity
	m_velocity.y += m_fGravity * Elapsed.asSeconds();

	if (m_bLookingLeft)
	{
		m_velocity.x = -m_fSpeed * Elapsed.asSeconds();
	}
	else
	{
		m_velocity.x = m_fSpeed * Elapsed.asSeconds();
	}

	//	X - Axis
	if (m_velocity.x <= 0)
	{
		if (getTile(m_enemy.getPosition().x + m_velocity.x, m_enemy.getPosition().y) != '.' || getTile(m_enemy.getPosition().x + m_velocity.x, m_enemy.getPosition().y + m_enemy.getSize().y) != '.')
		{
			m_velocity.x = 0.f;
			m_bLookingLeft = false;
		}
	}
	else
	{
		if (getTile(m_enemy.getPosition().x + m_enemy.getSize().x + m_velocity.x, m_enemy.getPosition().y) != '.' || getTile(m_enemy.getPosition().x + m_enemy.getSize().x + m_velocity.x, m_enemy.getPosition().y + m_enemy.getSize().y) != '.')
		{
			m_velocity.x = 0.f;
			m_bLookingLeft = true;
		}
	}

	//	Y - Axis
	if (m_velocity.y <= 0)
	{
		if (getTile(m_enemy.getPosition().x, m_enemy.getPosition().y + m_velocity.y) != '.' || getTile(m_enemy.getPosition().x + m_enemy.getSize().x, m_enemy.getPosition().y + m_velocity.y) != '.')
		{
			m_velocity.y = 0.f;
		}
	}
	else
	{
		if (getTile(m_enemy.getPosition().x, m_enemy.getPosition().y + m_enemy.getSize().y + m_velocity.y) != '.' || getTile(m_enemy.getPosition().x + m_enemy.getSize().x, m_enemy.getPosition().y + m_enemy.getSize().y + m_velocity.y) != '.')
		{
			m_velocity.y = 0.f;
		}
	}

	//Move Enemy by velocity
	m_enemy.move(m_velocity.x, m_velocity.y);

	//Reset Horizontal Speed && Keep Vertical
	m_velocity.x = 0.f;
}

void normEnemy::Draw(sf::RenderWindow* window)
{
	window->draw(m_enemy);
}