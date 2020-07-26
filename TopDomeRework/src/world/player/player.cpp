#include "player.h"
#include "../world.h"
#include "../../ResourceManager/ResourceManager.h"

Player::Player(World * world)
    : m_world(world)
    , m_jumpKey(sf::Keyboard::W, 1.0f)
    , m_shootKey(sf::Keyboard::Space, 0.4f)
{
    m_fSpeed = 200.f;
    m_fJumpSpeed = 1000.f;
    m_velocity = { 0, 0 };

    m_bLookingLeft = false;

    m_skinIndex = 2;
    m_player.setSize(sf::Vector2f(32, 32));
    m_player.setTexture(&we::ResourceManager::get().getTexture("players"));
}

void Player::Draw(sf::RenderWindow & window)
{
    window.draw(m_player);
}

void Player::HandleInput(sf::Event & e)
{
}

void Player::Update(float deltaTime)
{
    // Gravity
    m_velocity.y += m_world->getGravity() * deltaTime;

    // Controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_velocity.x += -m_fSpeed * deltaTime;
        m_bLookingLeft = true;
        setSkinDirection(Direction::LEFT);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_velocity.x += m_fSpeed * deltaTime;
        m_bLookingLeft = false;
        setSkinDirection(Direction::RIGHT);
    }

    if (m_velocity.x == 0)
        setSkinDirection(Direction::NOT_MOVING);

    if (m_jumpKey.isKeyPressed())
    {
        m_velocity.y += -m_fJumpSpeed * deltaTime;
    }
    if (m_shootKey.isKeyPressed())
    {
        Shoot();
    }

    Collision();
    m_player.move(m_velocity);

    // Reset velocity
    m_velocity.x = 0;
}

void Player::resetPos()
{
    m_player.setPosition(m_world->getSpawnpoint().x, m_world->getSpawnpoint().y);
}

void Player::changeCharacter(int index)
{
    // 4 Charachters are available
    if (abs(index) >= 4)
        index = 0;

    m_skinIndex = index;
}

void Player::changeSpeed(float fSpeed)
{
    m_fSpeed = fSpeed;
}

void Player::Collision()
{
    sf::Vector2f topLeft = m_player.getPosition();
    sf::Vector2f topRight = sf::Vector2f(topLeft.x + 32, topLeft.y);
    sf::Vector2f bottomLeft = sf::Vector2f(topLeft.x, topLeft.y + 32);
    sf::Vector2f bottomRight = sf::Vector2f(topRight.x, topRight.y + 32);

    // If we don't seperate the velocity when you jump into a wall and keep holding the direction key
    // you are stuck in the wall because it also moves the y position in the bottom AND top check
    sf::Vector2f xVel = { m_velocity.x, 0 };
    sf::Vector2f yVel = { 0, m_velocity.y };

    // Bottom
    if (m_world->getTileFromGlobal(bottomLeft + yVel) == '#' || m_world->getTileFromGlobal(bottomRight + yVel) == '#')
        m_velocity.y = 0;
    
    // Left
    if (m_world->getTileFromGlobal(topLeft + xVel) == '#' || m_world->getTileFromGlobal(bottomLeft + xVel) == '#')
        m_velocity.x = 0;

    // Right
    if (m_world->getTileFromGlobal(topRight + xVel) == '#' || m_world->getTileFromGlobal(bottomRight + xVel) == '#')
        m_velocity.x = 0;

    // Top
    if (m_world->getTileFromGlobal(topLeft + yVel) == '#' || m_world->getTileFromGlobal(topRight + yVel) == '#')
        m_velocity.y = 0;

    // Reset player positions
    // Bottom of the map
    if (bottomLeft.y + yVel.y + 16 >= m_world->getWindowSize().y)
        m_player.setPosition(m_world->getSpawnpoint());

    // Top of the map
    if (topLeft.y + yVel.y <= 0)
        m_velocity.y = 0;
}

void Player::setSkinDirection(Direction dir)
{
    if (dir == Direction::LEFT)
    {
        sf::IntRect rect(32 * 1, m_skinIndex * 32, 32, 32);
        m_player.setTextureRect(rect);
    }
    else if (dir == Direction::NOT_MOVING)
    {
        sf::IntRect rect(32 * 0, m_skinIndex * 32, 32, 32);
        m_player.setTextureRect(rect);
    }
    else if (dir == Direction::RIGHT)
    {
        sf::IntRect rect(32 * 2, m_skinIndex * 32, 32, 32);
        m_player.setTextureRect(rect);
    }
}

void Player::Shoot()
{
    Bullet temp(m_player.getPosition().x, m_player.getPosition().y);
    temp.setVelocity(300.0f, m_bLookingLeft);
    m_world->getBulletVector()->push_back(temp);
}