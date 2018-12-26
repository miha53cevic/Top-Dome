#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(float sizeX = 10.0f, float sizeY = 10.0f, sf::Color c = sf::Color::Red)
		: fVelocity(50.0f)
	{
		m_bullet.setFillColor(c);
		m_bullet.setSize(sf::Vector2f(sizeX, sizeY));
	}

	void setVelocity(float velocity)
	{
		fVelocity = velocity;
	}

	void Update()
	{
		m_bullet.move(fVelocity, 0);
	}

	sf::RectangleShape* getBullet()
	{
		return &m_bullet;
	}
	
private:
	sf::RectangleShape m_bullet;

	float fVelocity;
};

