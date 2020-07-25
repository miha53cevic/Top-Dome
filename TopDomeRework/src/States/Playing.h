#pragma once
#include "State.h"
#include "../world/world.h"
#include "../world/player/player.h"

class App;

class Playing : public we::State
{
public:
    Playing(we::App* app);

    virtual void Init();

    virtual void HandleInput(sf::Event& e);
    virtual void Update(float deltaTime);
    virtual void Draw(sf::RenderWindow& window);

    virtual void Pause() {}
    virtual void Resume() {}

private:
    World m_world;
    Player m_player;
};
