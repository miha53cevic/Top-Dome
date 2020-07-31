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
        if (m_vecEnemies.size() > 0)
            for (auto& i : m_vecEnemies)
                i->Update(deltaTime);
    }

    void Draw(sf::RenderWindow* window)
    {
        if (m_vecEnemies.size() > 0)
            for (auto& i : m_vecEnemies)
                i->Draw(window);
    }

    void setPosition(sf::Vector2f position)
    {
        m_position = position;
    }

    void SpawnEnemy(std::unique_ptr<Enemy> enemy)
    {
        enemy->setPosition(m_position);
        m_vecEnemies.push_back(std::move(enemy));
    }

    int getEnemyCount() { return m_vecEnemies.size(); }

    std::vector<std::unique_ptr<Enemy>>* getEnemiesVec() { return &m_vecEnemies; }

private:
    std::vector<std::unique_ptr<Enemy>> m_vecEnemies;
    sf::Vector2f m_position;
};