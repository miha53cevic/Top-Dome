#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Textbox
{
public:
	Textbox(int fontSize = 64, int outlineThickness = 5, sf::Color c = sf::Color::Black)
	{
		//font Loading
		if (!m_font.loadFromFile("fonts/Arial.ttf"))
		{
			//Error
		}

		//Text loading
		m_text.setFont(m_font);
		m_text.setCharacterSize(fontSize);
		m_text.setOutlineColor(c);
		m_text.setOutlineThickness(outlineThickness);
	}

	void setPosition(float x, float y)
	{
		m_text.setPosition(x, y);
	}

	void setText(std::string l_text)
	{
		m_text.setString(l_text);
	}

	void Draw(sf::RenderWindow* window)
	{
		window->draw(m_text);
	}

private:
	sf::Text m_text;
	sf::Font m_font;
};