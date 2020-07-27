#pragma once
#include <vector>
#include <memory>

#include "enemy/enemy.h"

class Spawner
{
public:
    Spawner() 
    {}

    void Update(float deltaTime)
    {
        if (m_enemies.size() > 0)
            for (auto& i : m_enemies)
                i->Update(deltaTime);
    }

    void Draw(sf::RenderWindow* window)
    {
        if (m_enemies.size() > 0)
            for (auto& i : m_enemies)
                i->Draw(window);
    }

    void setPosition(sf::Vector2f position)
    {
        m_position = position;
    }

    void SpawnEnemy(std::unique_ptr<Enemy> enemy)
    {
        enemy->setPosition(m_position);
        m_enemies.push_back(std::move(enemy));
    }

    int getEnemyCount() { return m_enemies.size(); }

    std::vector<std::unique_ptr<Enemy>>* getEnemies() { return &m_enemies; }

private:
    std::vector<std::unique_ptr<Enemy>> m_enemies;
    sf::Vector2f m_position;
};