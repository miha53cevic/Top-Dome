#pragma once
#include <vector>
#include "SFML/Graphics.hpp"

#include "../../modules/util/ToggleKey.h"
#include "bullet.h"

class World;

class Player
{
public:
    Player(World* world);

    void Draw            (sf::RenderWindow& window);
    void HandleInput     (sf::Event & e);
    void Update          (float deltaTime);

    void SpawnPlayer     (sf::Vector2f spawnpoint);

    void changeCharacter (int index);
    void changeSpeed     (float fSpeed);
    void changeMaxBullets(int max);

    std::vector<Bullet>& getBulletsVector();

    enum class Direction
    {
        LEFT, 
        RIGHT,
        NOT_MOVING
    };

private:
    void Collision           ();
    void setSkinDirection    (Direction dir);
    void Shoot               ();
    void EnemyCollision      ();
    void BulletEnemyCollision();

    World* m_world;

    sf::RectangleShape m_player;

    float m_fSpeed;
    float m_fJumpSpeed;

    int   m_maxBullets;

    sf::Vector2f m_velocity;
    sf::Vector2f m_spawnpoint;

    ToggleKey m_jumpKey;
    ToggleKey m_shootKey;

    bool m_bLookingLeft;
    int  m_skinIndex;

    std::vector<Bullet> m_vecBullets;
};