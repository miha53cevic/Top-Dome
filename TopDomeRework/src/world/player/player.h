#pragma once
#include "SFML/Graphics.hpp"
#include "../ToggleKey.h"

class World;

class Player
{
public:
    Player(World* world);

    void Draw            (sf::RenderWindow& window);
    void HandleInput     (sf::Event & e);
    void Update          (float deltaTime);

    void resetPos        ();

    void changeCharacter (int index);
    void changeSpeed     (float fSpeed);
    void changeMaxBullets(int max);

    enum class Direction
    {
        LEFT, 
        RIGHT,
        NOT_MOVING
    };

private:
    void Collision          ();
    void setSkinDirection   (Direction dir);
    void Shoot              ();
    void EnemyCollision     ();

    World* m_world;

    sf::RectangleShape m_player;

    float m_fSpeed;
    float m_fJumpSpeed;

    int   m_maxBullets;

    sf::Vector2f m_velocity;

    ToggleKey m_jumpKey;
    ToggleKey m_shootKey;

    bool m_bLookingLeft;
    int  m_skinIndex;
};