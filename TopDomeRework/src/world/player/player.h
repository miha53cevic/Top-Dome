#pragma once
#include "SFML/Graphics.hpp"
#include "../ToggleKey.h"

class World;

class Player
{
public:
    Player(World* world);

    void Draw(sf::RenderWindow& window);
    void HandleInput(sf::Event & e);
    void Update(float deltaTime);

    void resetPos();

    void changeCharacter(int index);

    enum class Direction
    {
        LEFT, RIGHT, NOT_MOVING
    };

private:
    void Collision();
    void setSkinDirection(Direction dir);

    World* m_world;

    sf::Vector2f m_position;
    sf::RectangleShape m_player;
    int m_skinIndex;

    float m_fGravity;
    float m_fSpeed;
    float m_fJumpSpeed;
    sf::Vector2f m_velocity;

    ToggleKey m_jumpKey;
    ToggleKey m_shootKey;

    bool m_bLookingLeft;
};