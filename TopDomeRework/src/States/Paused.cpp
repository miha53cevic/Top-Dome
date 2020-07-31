#include "Paused.h"
#include "../Engine/App.h"
#include "Playing.h"

Paused::Paused(we::App * app)
    : State(app)
    , m_textbox(app)
{
    m_textbox.setString("Paused");
    m_textbox.setPosition(app->ScreenWidth() / 2, app->ScreenHeight() / 2);
}

void Paused::Init()
{
}

void Paused::HandleInput(sf::Event & e)
{
    // On ESC go back to Playing state
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
    {
        m_app->getStateMachine().RemoveState();
        m_app->getStateMachine().ProcessStateChanges();
    }
}

void Paused::Update(float deltaTime)
{ 
}

void Paused::Draw(sf::RenderWindow & window)
{
    // Keep drawing the previous state
    m_app->getStateMachine().GetStates()[1]->Draw(window);
    
    // Draw Pause text
    m_textbox.Draw(window);
}
