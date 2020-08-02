#include "GameOver.h"
#include "../engine/App.h"

#include "Playing.h"
#include "../world/world.h"

GameOver::GameOver(we::App * app, World* world)
    : State(app)
    , m_textbox(app)
    , m_textbox2(app)
{
    m_textbox.setString("Game Over");
    m_textbox.setPosition(app->ScreenWidth() / 2, app->ScreenHeight() / 2);

    m_textbox2.setCharachterSize(48);
    m_textbox2.setString("Survived " + std::to_string(world->getRounds()) + " round(s)");
    m_textbox2.setPosition(app->ScreenWidth() / 2, app->ScreenHeight() / 2 + m_textbox.getText().getGlobalBounds().height);
}

void GameOver::Init()
{
}

void GameOver::HandleInput(sf::Event & e)
{
    // On key press reset game
    if (e.type == sf::Event::KeyPressed)
    {
        m_app->getStateMachine().RemoveStateBack();
        m_app->getStateMachine().AddState(std::make_unique<Playing>(m_app), true);
        m_app->getStateMachine().ProcessStateChanges();
    }
}

void GameOver::Update(float deltaTime)
{ 
}

void GameOver::Draw(sf::RenderWindow & window)
{
    // Keep drawing the previous state
    m_app->getStateMachine().GetStates()[1]->Draw(window);
    
    // Draw GameOver text
    m_textbox.Draw(window);

    // Draw rounds survived
    m_textbox2.Draw(window);
}
