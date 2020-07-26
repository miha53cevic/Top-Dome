#pragma once
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "../GUI/TextBox.h"
#include "Bullet.h"

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

    void setScore   (int score);
    int  getScore   ();

    float getGravity();
    void  setGravity(float g);

    std::vector<Bullet>* getBulletVector();

    sf::Vector2i getWindowSize();
    sf::Vector2f getSpawnpoint();

private:
    sf::Vector2i m_mapSize;
    sf::Vector2f m_blockSize;
    sf::Vector2i m_winSize;

    std::string  m_map;

    int          m_score;

    we::TextBox  m_textbox;

    sf::Vector2f m_spawnpoint;
    sf::Vector2f m_spawnerLocation;

    float        m_fGravity;

    std::vector<Bullet> m_bullets;
};