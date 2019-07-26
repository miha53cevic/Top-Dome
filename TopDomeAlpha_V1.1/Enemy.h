#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(float posX, float posY, float fSpeed = 50.0f);
	~Enemy() = default;

	void Draw(sf::RenderWindow* window);
	void Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize, sf::Time Elapsed);

	sf::RectangleShape* getEnemy();

private:
	sf::RectangleShape m_enemy;

	sf::Vector2f m_velocity;

	float m_fSpeed;
	float m_fGravity;

	bool m_bLookingLeft;
};

