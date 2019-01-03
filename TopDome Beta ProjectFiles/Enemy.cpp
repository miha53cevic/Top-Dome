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

sf::RectangleShape* Enemy::getEnemy()
{
	return &m_enemy;
}

void Enemy::setColour(sf::Color c)
{
	m_enemy.setFillColor(c);
}

int Enemy::getHP()
{
	return m_HP;
}

void Enemy::removeHP(int HP)
{
	m_HP -= HP;
}