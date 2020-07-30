#include "Playing.h"
#include "../Engine/App.h"
#include "GameOver.h"

Playing::Playing(we::App * app)
    : State(app)
    , m_world(m_app, app->ScreenWidth(), app->ScreenHeight())
    , m_player(&m_world)
{
}

void Playing::Init()
{
    // Load map
    m_world.loadMap("map.txt");
    
    // Spawn player
    m_player.resetPos();
}

void Playing::HandleInput(sf::Event & e)
{
    m_player.HandleInput(e);
}

void Playing::Update(float deltaTime)
{
    m_world.Update(deltaTime);
    m_player.Update(deltaTime);

    // Check for GameOver
    if (m_world.GameOver())
    {
        m_app->getStateMachine().AddState(std::make_unique<GameOver>(m_app), false);
        m_app->getStateMachine().ProcessStateChanges();
    }
}

void Playing::Draw(sf::RenderWindow & window)
{
    m_world.Draw(window);
    m_player.Draw(window);
}
