#pragma once
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../modules/gui/TextBox.h"
#include "spawner.h"

class App;

class World
{
public:
    World(we::App* app, int winX, int winY);

    void loadMap    (std::string path);
    void Update     (float deltaTime);

    // Uses the string map coordinate system
    char getTileFromLocal   (int x, int y);
    // Uses the global coordinates system and converts it to the string map coordinate system
    char getTileFromGlobal  (sf::Vector2f pos);

    void Draw       (sf::RenderWindow& window);

    void setLives   (int lives);
    int  getLives   ();

    int  getRounds  ();
    void setRounds  (int round);

    bool GameOver   ();

    void addToKillCount();

    float getGravity();
    void  setGravity(float g);

    sf::Vector2i getWindowSize();

    sf::Vector2f getSpawnpoint();

    Spawner&     getSpawner();

private:
    sf::Vector2i m_mapSize;
    sf::Vector2f m_blockSize;
    sf::Vector2i m_winSize;

    std::string  m_map;

    int          m_lives;
    int          m_round;
    int          m_killedEnemies;

    bool         m_bGameOver;
    float        m_fGravity;

    we::TextBox  m_textbox;

    Spawner      m_spawner;

    sf::Vector2f m_spawnpoint;
};