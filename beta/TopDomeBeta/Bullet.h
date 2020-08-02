#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(float posX, float posY, float sizeX = 10.0f, float sizeY = 10.0f, sf::Color c = sf::Color::Red)
		: fVelocity(50.0f)
		, BulletDamage(1)
	{
		m_bullet.setFillColor(c);
		m_bullet.setSize(sf::Vector2f(sizeX, sizeY));

		m_bullet.setPosition(posX, posY);
	}

	void setBulletDamage(int damage)
	{
		BulletDamage = damage;
	}

	void setVelocity(float velocity, bool LookingLeft)
	{
		if (LookingLeft)
			fVelocity = -velocity;

		else
			fVelocity = velocity;

		bLeft = LookingLeft;
	}

	void Update()
	{
		m_bullet.move(fVelocity, 0);
	}

	sf::RectangleShape* getBullet()
	{
		return &m_bullet;
	}

	bool getDir()
	{
		return bLeft;
	}

	float getVelocity()
	{
		return fVelocity;
	}

	int getBulletDamage()
	{
		return BulletDamage;
	}
	
private:
	sf::RectangleShape m_bullet;

	bool bLeft;

	float fVelocity;

	int BulletDamage;
};

