#include "PowerUp.h"

PowerUp::PowerUp()
	: m_currentWeapon(Weapons::AutomaticPistol)
{
	m_item.setFillColor(sf::Color::Cyan);
	m_item.setSize(sf::Vector2f(20, 20));

	m_bVisible = false;
}

void PowerUp::Spawn(float x, float y)
{
	m_item.setPosition(x, y);

	m_bVisible = true;
}

void PowerUp::Update(Player* l_player)
{
	sf::FloatRect player = l_player->m_player.getGlobalBounds();
	sf::FloatRect item = m_item.getGlobalBounds();

	if (player.intersects(item))
	{
		m_bVisible = false;

		//Clear all bullets first
		l_player->getBulletVector()->clear();

		m_currentWeapon = Weapons(rand() % NumberOfWeapons);

		printf_s("CurrentWeapon = %d", m_currentWeapon);

		switch (m_currentWeapon)
		{
			case Weapons::AutomaticPistol:
			{
				l_player->changeBulletDamage(1);
				l_player->changeBulletSpeed(500.0f);
				l_player->changeMaxBullets(3);

				break;
			}
			case Weapons::Rifle:
			{
				l_player->changeBulletDamage(1);
				l_player->changeBulletSpeed(500.0f);
				l_player->changeMaxBullets(5);

				break;
			}
			case Weapons::Sniper:
			{
				l_player->changeBulletDamage(3);
				l_player->changeBulletSpeed(800.0f);
				l_player->changeMaxBullets(1);

				break;
			}
		}
	}
}

void PowerUp::Draw(sf::RenderWindow *window)
{
	window->draw(m_item);
}

bool PowerUp::isVisible()
{
	return m_bVisible;
}