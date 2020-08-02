#pragma once
#include <SFML/Graphics.hpp>

class World;

class Enemy
{
public:
    Enemy           (World* world);

    void Setup      (int health = 1, float speed = 200.0f, sf::Vector2f size = sf::Vector2f(32, 32), sf::Color c = sf::Color::Red);

    void Draw       (sf::RenderWindow* window);
    void Update     (float deltaTime);

    int getHP       ();

    void Damage     (int damage);
    bool isDead     ();

    void         setPosition    (sf::Vector2f position);
    sf::Vector2f getPosition    ();

    sf::RectangleShape* getEnemy();

protected:
    void Collision();

    int     m_health;
    float   m_fSpeed;
    bool    m_bLookingLeft;

    sf::RectangleShape  m_enemy;
    sf::Vector2f        m_velocity;

    World*              m_world;
};