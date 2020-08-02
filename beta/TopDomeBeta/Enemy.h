#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(float posX, float posY, float fSpeed = 50.0f);
	~Enemy() = default;

	virtual void Draw(sf::RenderWindow* window) = 0;
	virtual void Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize, sf::Time Elapsed) = 0;

	void setColour(sf::Color c);

	sf::RectangleShape* getEnemy();

	int getHP();

	void removeHP(int HP);

protected:
	sf::RectangleShape m_enemy;

	sf::Vector2f m_velocity;

	float m_fSpeed;
	float m_fGravity;

	bool m_bLookingLeft;

	int m_HP;
};

