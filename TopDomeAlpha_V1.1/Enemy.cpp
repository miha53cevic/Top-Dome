#include "Enemy.h"

Enemy::Enemy(float posX, float posY, float fSpeed)
{
	m_enemy.setSize(sf::Vector2f(20, 20));
	m_enemy.setFillColor(sf::Color::Blue);
	m_enemy.setPosition(posX, posY);

	m_fGravity = 50.0f;
	m_fSpeed = fSpeed;

	m_bLookingLeft = rand() % 2;
}

void Enemy::Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize, sf::Time Elapsed)
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

	//Move Player by velocity
	m_enemy.move(m_velocity.x, m_velocity.y);

	//Reset Horizontal Speed && Keep Vertical
	m_velocity.x = 0.f;
}

void Enemy::Draw(sf::RenderWindow* window)
{
	window->draw(m_enemy);
}

sf::RectangleShape* Enemy::getEnemy()
{
	return &m_enemy;
}