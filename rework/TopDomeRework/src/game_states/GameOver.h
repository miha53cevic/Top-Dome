#pragma once
#include "../modules/states/State.h"

#include "../modules/gui/TextBox.h"

class App;
class World;

class GameOver : public we::State
{
public:
    GameOver(we::App* app, World* world);

    virtual void Init           ();

    virtual void HandleInput    (sf::Event& e);
    virtual void Update         (float deltaTime);
    virtual void Draw           (sf::RenderWindow& window);

    virtual void Pause          () {}
    virtual void Resume         () {}

private:
    we::TextBox m_textbox;
    we::TextBox m_textbox2;
};
