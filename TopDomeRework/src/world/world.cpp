#include "world.h"
#include <iostream>
#include "../Engine/App.h"

World::World(we::App* app, int winX, int winY)
    : m_textbox(app)
{
    m_winSize = { winX, winY };

    // Default values
    m_map = "";
    m_score = 0;
    
    m_fGravity = 50.f;

    m_textbox.setString("Lives: X");
    m_textbox.setPosition(winX - m_textbox.getText().getLocalBounds().width / 1.5f,
                          winY - m_textbox.getText().getLocalBounds().height);
}

void World::loadMap(std::string path)
{
    std::ifstream reader(path);
    if (reader.is_open())
    {
        std::string line;
        m_mapSize = { 0, 0 };
        while (std::getline(reader, line))
        {
            // Find out the width and height of the map
            m_mapSize.x = line.length();
            m_mapSize.y++;

            // Save the map layout
            m_map += line;
        }
        reader.close();

        // Calculate each block size
        m_blockSize.x = m_winSize.x / m_mapSize.x;
        m_blockSize.y = m_winSize.y / m_mapSize.y;

        // Find and save the spawnpoint location
        for (int i = 0; i < m_mapSize.y; i++)
        {
            for (int j = 0; j < m_mapSize.x; j++)
            {
                if (getTileFromLocal(j, i) == 'S')
                    m_spawnpoint = sf::Vector2f(j * m_blockSize.x, i * m_blockSize.y);
                else if (getTileFromLocal(j, i) == 'E')
                    m_spawnerPos = sf::Vector2f(j * m_blockSize.x, i * m_blockSize.y);
            }
        }
        m_spawner.setPosition(m_spawnerPos);
    }
    else std::cout << "Could not load map " << path << std::endl;
}

void World::Update(float deltaTime)
{
    // Remove bullets outside of the map
    if (m_bullets.size() > 0)
    {
        for (auto iter = m_bullets.begin(); iter != m_bullets.end();)
        {
            iter->Update(deltaTime);

            if (getTileFromGlobal(iter->getPosition()) == '#')
            {
                iter = m_bullets.erase(iter);
            }
            else iter++;
        }
    }

#ifdef DEBUG
    std::cout << "Bullets: " << m_bullets.size() << "\n";
#endif

    // Round Manager
    if (m_spawner.getEnemyCount() == 0)
    {
        m_spawner.SpawnEnemy(std::make_unique<Enemy>(this));
    }
    m_spawner.Update(deltaTime);

    // Bullet VS Enemy Collision
    for (auto bullet = m_bullets.begin(); bullet != m_bullets.end();)
    {
        bool hit = false;

        for (auto enemy = m_spawner.getEnemies()->begin(); enemy != m_spawner.getEnemies()->end();)
        {
            sf::FloatRect bulletRect = bullet->getBullet()->getGlobalBounds();
            sf::FloatRect enemyRect = enemy->get()->getEnemy()->getGlobalBounds();

            if (bulletRect.intersects(enemyRect))
            {
                hit = true;

                // Delete the bullet
                bullet = m_bullets.erase(bullet);
                
                // If the enemy is dead delete him
                if (!enemy->get()->Damage(1))
                {
                    enemy = m_spawner.getEnemies()->erase(enemy);
                }
                else enemy++;
            }
            else
            {
                enemy++;
            }
        }

        if (!hit)
            bullet++;
    }
}

char World::getTileFromLocal(int x, int y)
{
    return m_map[(y * m_mapSize.x) + x];
}

char World::getTileFromGlobal(sf::Vector2f pos)
{
    int x = pos.x / m_blockSize.x;
    int y = pos.y / m_blockSize.y;
    return m_map[(y * m_mapSize.x) + x];
}

void World::Draw(sf::RenderWindow& window)
{
    // Draw the map
    sf::RectangleShape rect;
    for (int i = 0; i < m_mapSize.y; i++)
    {
        for (int j = 0; j < m_mapSize.x; j++)
        {
            if (getTileFromLocal(j, i) == '#')
            {
                rect.setSize(sf::Vector2f(m_blockSize.x, m_blockSize.y));
                rect.setPosition(j * m_blockSize.x, i * m_blockSize.y);
                rect.setFillColor(sf::Color(128, 128, 128));
                window.draw(rect);
            }
        }
    }

    // Draw the GUI
    m_textbox.setString("Lives: " + std::to_string(m_score));
    m_textbox.Draw(window);

    // Draw Bullets
    if (m_bullets.size() > 0)
    {
        for (auto& i : m_bullets)
            i.Draw(&window);
    }

    // Draw enemies
    m_spawner.Draw(&window);
}

void World::setScore(int score)
{
    m_score = score;
}

int World::getScore()
{
    return m_score;
}

float World::getGravity()
{
    return m_fGravity;
}

void World::setGravity(float g)
{
    m_fGravity = g;
}

std::vector<Bullet>* World::getBulletVector()
{
    return &m_bullets;
}

sf::Vector2i World::getWindowSize()
{
    return m_winSize;
}

sf::Vector2f World::getSpawnpoint()
{
    return m_spawnpoint;
}

sf::Vector2f World::getSpawnerPos()
{
    return m_spawnerPos;
}
