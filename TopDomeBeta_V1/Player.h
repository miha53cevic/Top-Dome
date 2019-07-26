#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Bullet.h"
#include "ToggleKey.h"

class Player
{
public:
	Player(const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize);
	~Player() = default;

	void Draw(sf::RenderWindow* window);
	void Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize);
	void Input(sf::Time Elapsed);

	std::vector<Bullet>* getBulletVector();

	void changeSpeed(float fSpeed = 200.0f);

	//Get Weapon Specifics
	void changeBulletSpeed(float speed);
	void changeMaxBullets(int max);
	void changeBulletDamage(int damage);

	void Reset();

	sf::RectangleShape m_player;

private:
	sf::Vector2f m_velocity;

	float m_fSpeed;
	float m_fGravity;
	float m_fJumpSpeed;
	float m_fBulletSpeed;

	bool m_bLookingLeft;

	int m_nMaxBullets;
	int m_nBulletDamage;

	std::vector<Bullet> m_vecBullets;

	sf::Vector2f m_defaultPos;

	ToggleKey m_toggleJump;
	ToggleKey m_toggleShoot;
};

