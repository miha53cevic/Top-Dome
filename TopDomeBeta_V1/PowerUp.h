#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

#define NumberOfWeapons 3

enum class Weapons
{
	AutomaticPistol,
	Rifle,
	Sniper
};

class PowerUp
{
public:
	PowerUp();
	~PowerUp() = default;

	void Spawn(float posX, float posY);
	void Update(Player* player);
	void Draw(sf::RenderWindow *window);

	bool isVisible();

private:
	sf::RectangleShape m_item;

	Weapons m_currentWeapon;

	bool m_bVisible;
};

