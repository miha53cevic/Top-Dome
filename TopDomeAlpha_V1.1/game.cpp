#include "game.h"

Game::Game(const sf::Vector2u& l_size, const std::string& l_name)
	: m_window(l_size, l_name)
	, m_world(m_window.getSize())
	, m_player(m_world.getMapSize(), m_world.getPixelSize())
	{}
Game::~Game() {}

Window* Game::getWindow()
{
	return &m_window;
}

World* Game::getWorld()
{
	return &m_world;
}

void Game::HandleInput()
{
	//input
	m_player.Input(m_elapsed);
}

void Game::Update()
{
	//Event System
	m_window.Update(*m_player.getJumpState(), *m_player.getShootState());
	m_world.Update();
	m_player.Update(*m_world.getMap(), m_world.getMapSize(), m_world.getPixelSize());

	m_spawner.Update(*m_world.getMap(), m_world.getMapSize(), m_world.getPixelSize(), m_elapsed, *m_world.getScore());
}

void Game::Render()
{
	//Draw something
	m_window.BeginDraw(sf::Color::White);
	
	m_world.Draw(m_window.getWindow());
	m_player.Draw(m_window.getWindow());
	m_spawner.Draw(m_window.getWindow());

	m_window.EndDraw();
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}