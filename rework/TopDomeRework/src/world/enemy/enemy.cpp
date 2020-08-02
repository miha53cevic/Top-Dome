#include "enemy.h"

#include "../world.h"
#include "../../modules/math/Math.h"

Enemy::Enemy(World * world)
    : m_world(world)
{
    // Random looking direction
    m_bLookingLeft = Math::iRandom(0, 1);

    Setup();
}

void Enemy::Setup(int health, float speed, sf::Vector2f size, sf::Color c)
{
    m_enemy.setSize(size);
    m_enemy.setFillColor(c);
    m_health = health;
    m_fSpeed = speed;
}

void Enemy::Draw(sf::RenderWindow * window)
{
    window->draw(m_enemy);
}

void Enemy::Update(float deltaTime)
{
    // Gravity
    m_velocity.y += m_world->getGravity() * deltaTime;

    // Movement
    if (m_bLookingLeft) m_velocity.x += -m_fSpeed * deltaTime;
    else                m_velocity.x += m_fSpeed * deltaTime;

    Collision();
    m_enemy.move(m_velocity);

    // Reset velocity
    m_velocity.x = 0;
}

int Enemy::getHP()
{
    return m_health;
}

void Enemy::Damage(int damage)
{
    m_health -= damage;
}

bool Enemy::isDead()
{
    if (m_health <= 0) return true;
    else               return false;
}

void Enemy::setPosition(sf::Vector2f position)
{
    m_enemy.setPosition(position);
}

sf::Vector2f Enemy::getPosition()
{
    return m_enemy.getPosition();
}

sf::RectangleShape * Enemy::getEnemy()
{
    return &m_enemy;
}

void Enemy::Collision()
{
    sf::Vector2f size = m_enemy.getSize();

    sf::Vector2f topLeft = m_enemy.getPosition();
    sf::Vector2f topRight = sf::Vector2f(topLeft.x + size.x, topLeft.y);
    sf::Vector2f bottomLeft = sf::Vector2f(topLeft.x, topLeft.y + size.y);
    sf::Vector2f bottomRight = sf::Vector2f(topRight.x, topRight.y + size.y);

    sf::Vector2f xVel = { m_velocity.x, 0 };
    sf::Vector2f yVel = { 0, m_velocity.y };

    // Bottom
    if (m_world->getTileFromGlobal(bottomLeft + yVel) == '#' || m_world->getTileFromGlobal(bottomRight + yVel) == '#')
        m_velocity.y = 0;

    // Left
    if (m_world->getTileFromGlobal(topLeft + xVel) == '#' || m_world->getTileFromGlobal(bottomLeft + xVel) == '#')
        m_bLookingLeft = !m_bLookingLeft;

    // Right
    if (m_world->getTileFromGlobal(topRight + xVel) == '#' || m_world->getTileFromGlobal(bottomRight + xVel) == '#')
        m_bLookingLeft = !m_bLookingLeft;

    // Top
    if (m_world->getTileFromGlobal(topLeft + yVel) == '#' || m_world->getTileFromGlobal(topRight + yVel) == '#')
        m_velocity.y = 0;

    // Reset enemy positions
    // Bottom of the map
    if (bottomLeft.y + yVel.y + (size.y / 2) >= m_world->getWindowSize().y)
    {
        m_enemy.setPosition(m_world->getSpawner().getPosition());
        
        // Update score
        m_world->setLives(m_world->getLives() - 1);
    }
}
