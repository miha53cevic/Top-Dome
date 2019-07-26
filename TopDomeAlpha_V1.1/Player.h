#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Bullet.h"

class Player
{
public:
	Player(const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize);
	~Player() = default;

	void Draw(sf::RenderWindow* window);
	void Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize);
	void Input(sf::Time Elapsed);

	bool* getJumpState();
	bool* getShootState();

private:
	sf::RectangleShape m_player;

	sf::Vector2f m_velocity;

	float m_fSpeed;
	float m_fGravity;
	float m_fJumpSpeed;
	float m_fBulletSpeed;

	bool m_bJump;
	bool m_bShoot;

	bool m_bLookingLeft;

	int m_nMaxBullets;

	std::vector<Bullet> m_vecBullets;
};

