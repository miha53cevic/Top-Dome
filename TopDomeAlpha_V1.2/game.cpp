#include "game.h"

Game::Game(const sf::Vector2u& l_size, const std::string& l_name)
	: m_window(l_size, l_name)
	, m_state(State::Playing)
	, m_world(m_window.getSize())
	, m_player(m_world.getMapSize(), m_world.getPixelSize())
	, m_bPaused(false)
	{}
Game::~Game() {}

Window* Game::getWindow()
{
	return &m_window;
}

void Game::Restart()
{
	m_state = State::Playing;

	m_player.Reset();
	m_world.Reset(m_window.getSize());
	m_spawner.Reset();
}

void Game::HandleInput()
{
	//input
	m_player.Input(m_elapsed);

	if (m_state == State::GameOver)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Restart();
		}
	}
}

void Game::Update()
{
	//Event System
	m_window.Update(*m_player.getJumpState(), *m_player.getShootState(), m_bPaused);
	
	if (m_state == State::Playing)
	{
		//Check if game is over
		int* Score = m_world.getScore();

		if (*Score <= 0)
		{
			m_state = State::GameOver;
		}

		//Update Everything
		m_world.Update();
		m_player.Update(*m_world.getMap(), m_world.getMapSize(), m_world.getPixelSize());
		m_spawner.Update(*m_world.getMap(), m_world.getMapSize(), m_world.getPixelSize(), m_elapsed, *m_world.getScore(), *m_player.getBulletVector(), &m_player);
	}

	//Pause Game Logic
	if (m_bPaused && m_state != State::GameOver)
	{
		m_state = State::Pause;
	}
	else if (!m_bPaused && m_state != State::GameOver)
	{
		m_state = State::Playing;
	}
}

void Game::Render()
{
	//Draw something
	m_window.BeginDraw(sf::Color::White);
	
	m_world.Draw(m_window.getWindow());
	m_player.Draw(m_window.getWindow());
	m_spawner.Draw(m_window.getWindow());

	if (m_state == State::GameOver)
	{
		m_world.getTextboxObject()->setPosition(m_window.getSize().x / 3, m_window.getSize().y / 3);
		m_world.getTextboxObject()->setText("\t  Wave: " + std::to_string(m_spawner.getNumberOfEnemies() - 3) + "\n\n\tGame Over\n\nSPACE to Reset");
		m_world.getTextboxObject()->Draw(m_window.getWindow());
	}

	m_window.EndDraw();
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}