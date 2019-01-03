#include "World.h"

#include <fstream>

World::World(sf::Vector2u screenSize)
{
	m_ScreenSize = screenSize;
	m_Score = 3;
	
	//Set TextBox Position For Score
	m_textbox.setPosition(screenSize.x - 265, screenSize.y - 75);

	Setup();
}

void World::Update()
{
	//Update TextBox
	m_textbox.setText("Lives: " + std::to_string(m_Score));
}

void World::Draw(sf::RenderWindow* window)
{
	for (int y = 0; y < m_MapSize.y; y++)
	{
		for (int x = 0; x < m_MapSize.x; x++)
		{
			switch (m_Map[(y * m_MapSize.x) + x])
			{
				case '.':
				{
					break;
				}
				case '#':
				{
					m_block.setPosition(x * m_PixelSize.x, y * m_PixelSize.y);
					window->draw(m_block);
					break;
				}
			}
		}
	}

	m_textbox.Draw(window);
}

void World::Setup()
{
	//Check if custom map exists
	std::ifstream reader("map.txt");
	m_bCustomMap = reader.good();

	if (!m_bCustomMap)
	{
		m_MapSize.x = 16;
		m_MapSize.y = 10;

		m_PixelSize.x = (int)m_ScreenSize.x / m_MapSize.x;
		m_PixelSize.y = (int)m_ScreenSize.y / m_MapSize.y;

		m_block.setSize(sf::Vector2f(m_PixelSize.x, m_PixelSize.y));
		m_block.setFillColor(sf::Color::Color(125, 125, 125));

		m_Map += "######....######";
		m_Map += "#..............#";
		m_Map += "#..............#";
		m_Map += "#..##########..#";
		m_Map += "#..............#";
		m_Map += "####........####";
		m_Map += "#..............#";
		m_Map += "#...########...#";
		m_Map += "#..............#";
		m_Map += "######....######";
	}
	else if (m_bCustomMap)
	{
		std::string line;

		int x = 0;
		int y = 0;

		while (std::getline(reader, line))
		{
			m_Map += line;

			//Sprema x i y pozicije mape iz file-a
			x = line.length();
			y++;
		}

		m_MapSize.x = x;
		m_MapSize.y = y;

		m_PixelSize.x = (int)m_ScreenSize.x / m_MapSize.x;
		m_PixelSize.y = (int)m_ScreenSize.y / m_MapSize.y;

		m_block.setSize(sf::Vector2f(m_PixelSize.x, m_PixelSize.y));
		m_block.setFillColor(sf::Color::Color(125, 125, 125));
	}
}

std::string* World::getMap()
{
	return &m_Map;
}

sf::Vector2i World::getMapSize()
{
	return m_MapSize;
}

sf::Vector2i World::getPixelSize()
{
	return m_PixelSize;
}

int* World::getScore()
{
	return &m_Score;
}

Textbox* World::getTextboxObject()
{
	return &m_textbox;
}

void World::Reset(sf::Vector2u screenSize)
{
	m_Score = 3;

	m_textbox.setPosition(screenSize.x - 265, screenSize.y - 75);
}

