#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(float posX, float posY, float sizeX = 10.0f, float sizeY = 10.0f, sf::Color c = sf::Color::Red)
		: m_fVelocity(50.0f)
		, m_BulletDamage(1)
	{
		m_bullet.setFillColor(c);
		m_bullet.setSize(sf::Vector2f(sizeX, sizeY));

		m_bullet.setPosition(posX + (sizeX / 2), posY + (sizeY / 2));
	}

	void setBulletDamage(int damage)
	{
        m_BulletDamage = damage;
	}

	void setVelocity(float velocity, bool LookingLeft)
	{
		if (LookingLeft)
            m_fVelocity = -velocity;

		else
            m_fVelocity = velocity;

        m_bLeft = LookingLeft;
	}

	void Update(float deltaTime)
	{
		m_bullet.move(m_fVelocity * deltaTime, 0);
	}

    void Draw(sf::RenderWindow* window)
    {
        window->draw(m_bullet);
    }

    sf::Vector2f getPosition()
    {
        return m_bullet.getPosition();
    }

	bool getDir()
	{
		return m_bLeft;
	}

	float getVelocity()
	{
		return m_fVelocity;
	}

	int getBulletDamage()
	{
		return m_BulletDamage;
	}
	
private:
	sf::RectangleShape m_bullet;

	bool m_bLeft;

	float m_fVelocity;
	int   m_BulletDamage;
};

