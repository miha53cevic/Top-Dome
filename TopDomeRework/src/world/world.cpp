#include "world.h"
#include <iostream>
#include "../engine/App.h"
#include "../modules/math/Math.h"

World::World(we::App* app, int winX, int winY)
    : m_textbox(app)
{
    m_winSize = { winX, winY };

    // Default values
    m_map = "";
    m_lives = 3;
    m_round = 0;
    m_killedEnemies = 0;
    m_bGameOver  = false;
    
    m_fGravity = 50.f;

    // Center Lives text
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
                    m_spawner.setPosition(sf::Vector2f(j * m_blockSize.x, i * m_blockSize.y));
            }
        }
    }
    else std::cout << "Could not load map " << path << std::endl;
}

void World::Update(float deltaTime)
{
    

    // Round Manager
    if (m_killedEnemies < (int)(m_round * 1.5f))
    {
        // Add one more enemy every 3 rounds
        if (m_spawner.getEnemyCount() < 1 + (m_round / 3))
        {
            // Spawn normal enemies
            m_spawner.SpawnEnemyType(std::make_unique<Enemy>(this), 1, Math::fRandom(150.0f, 250.0f), {32,32}, sf::Color::Red);

            // Chance to spawn quick enemies
            if (Math::iRandom(0, 256) >= 200)
                m_spawner.SpawnEnemyType(std::make_unique<Enemy>(this), 1, Math::fRandom(300.0f, 350.0f), { 24,24 }, sf::Color::Yellow);

            // Chance to spawn heavy enemies
            if (Math::iRandom(0, 256) >= 200)
                m_spawner.SpawnEnemyType(std::make_unique<Enemy>(this), 3, Math::fRandom(50.0f, 100.0f), { 48,48 }, sf::Color::Magenta);
        }
    }
    else
    {
        // If the killed quota is hit go to next round
        m_round++;

        // Reset killCount
        m_killedEnemies = 0;
    }
    m_spawner.Update(deltaTime);

    // GameOver Manager
    if (m_lives <= 0)
        m_bGameOver = true;
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
    m_textbox.setString("Lives: " + std::to_string(m_lives));
    m_textbox.Draw(window);

    // Draw enemies
    m_spawner.Draw(&window);
}

void World::setLives(int lives)
{
    m_lives = abs(lives);
}

int World::getLives()
{
    return m_lives;
}

int World::getRounds()
{
    return m_round;
}

void World::setRounds(int round)
{
    m_round = abs(round);
}

bool World::GameOver()
{
    return m_bGameOver;
}

void World::addToKillCount()
{
    m_killedEnemies++;
}

float World::getGravity()
{
    return m_fGravity;
}

void World::setGravity(float g)
{
    m_fGravity = g;
}

sf::Vector2f World::getSpawnpoint()
{
    return m_spawnpoint;
}

sf::Vector2i World::getWindowSize()
{
    return m_winSize;
}

Spawner& World::getSpawner()
{
    return m_spawner;
}
