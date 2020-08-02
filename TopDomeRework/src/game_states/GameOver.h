#pragma once
#include "../modules/states/State.h"

#include "../modules/gui/TextBox.h"

class App;

class GameOver : public we::State
{
public:
    GameOver(we::App* app);

    virtual void Init           ();

    virtual void HandleInput    (sf::Event& e);
    virtual void Update         (float deltaTime);
    virtual void Draw           (sf::RenderWindow& window);

    virtual void Pause          () {}
    virtual void Resume         () {}

private:
    we::TextBox m_textbox;
};
