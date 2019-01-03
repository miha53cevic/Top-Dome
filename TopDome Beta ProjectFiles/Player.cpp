#include "Player.h"

//#define DEBUG	//Enable debugging for player and bullet pos

Player::Player(const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize)
	: m_toggleJump(sf::Keyboard::Key::W, 1.0f)
	, m_toggleShoot(sf::Keyboard::Key::Space, 0.4f)
{
	m_player.setSize(sf::Vector2f(20, 20));
	//m_player.setSize(sf::Vector2f(pixelSize.x, pixelSize.y));
	m_player.setFillColor(sf::Color::Green);

	m_defaultPos = sf::Vector2f(mapSize.x / 2 * pixelSize.x, (mapSize.y / 2 + 1) * pixelSize.y);
	m_player.setPosition(m_defaultPos);

	m_fSpeed = 200.f;
	m_fGravity = 50.f;
	m_fJumpSpeed = 1000.f;
	m_fBulletSpeed = 500.0f;

	m_bLookingLeft = true;

	m_nMaxBullets = 3;
	m_nBulletDamage = 1;
}

void Player::Input(sf::Time Elapsed)
{
	//Gravity
	m_velocity.y += m_fGravity * Elapsed.asSeconds();

	//Keyboard checks
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//Change Looking Direction
		if (!m_bLookingLeft)
			m_bLookingLeft = true;

		m_velocity.x += -m_fSpeed * Elapsed.asSeconds();
		m_velocity.y += 0.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//Change Looking Direction
		if (m_bLookingLeft)
			m_bLookingLeft = false;

		m_velocity.x += m_fSpeed * Elapsed.asSeconds();
		m_velocity.y += 0.f;
	}

	//Jump
	if (m_toggleJump.isKeyPressed())
	{
		m_velocity.y += -m_fJumpSpeed * Elapsed.asSeconds();
	}

	//Shoot
	if (m_toggleShoot.isKeyPressed())
	{
		if (m_vecBullets.size() < m_nMaxBullets)
		{
			Bullet bullet(m_player.getPosition().x + m_player.getSize().x / 2, m_player.getPosition().y + m_player.getSize().y / 4);
			bullet.setVelocity(m_fBulletSpeed * Elapsed.asSeconds(), m_bLookingLeft);
			bullet.setBulletDamage(m_nBulletDamage);

			m_vecBullets.push_back(bullet);
		}
	}
}

void Player::Update(std::string& map, const sf::Vector2i& mapSize, const sf::Vector2i& pixelSize)
{
	/*///////////////////////////////////////////////////////////////////////////////////////////

		- Igracevu poziciju se mora pretvoriti iz pravih kordinata ekrana u kordinate u stringu Map
		- To se dobi tako da se stvarna pozicija dijeli sa širinom i visinom polja string-a
		  Te se van uzima cijeli broj INT, te zato ako je recimo duzina svake kocke unutar stringa 10 je
		  igrac ako je na kordinatama x = 8, y = 0 i dalje na prvoj kocki jer 8 / 10 daje 0.neke decimale, a
		  INT to zaokruzi na 0 te kada je x = 10 tada je 10 / 10 = 1 te je na prvoj kocki u stringu itd...

	*////////////////////////////////////////////////////////////////////////////////////////////

	auto getTile = [&](float x, float y) -> char
	{
		int nX, nY;
		nX = x / pixelSize.x;
		nY = y / pixelSize.y;

		#ifdef DEBUG
				printf_s("X = %d, Y = %d\n", nX, nY);
		#endif


		return map[(nY * mapSize.x) + nX];
	};

	/*////////////////////////////////////////////////////////////////////////////////////////////

		Collision Detection
		- Ako se karakter krece na lijevu stranu znaci -X mora se gledati dvije tocke karaktera ako
		  mu je oblik kocka. Prvo gornji lijevi kut te zatim doljni lijevi kut jer u bilo kojem trenutku
		  igrac ako dodiruje zid mora ga dodirivati sa barem jednom od tih dvije tocke ako se te tocke nalaze
		  na mjestu gdje vise igrac ne moze ici stavlja se njegova akceleracija ili velocity na 0

		- Ta provjera se radi tako da se gleda tocka na kojoj ce igrac biti ako bi se pomaknuo

	*/////////////////////////////////////////////////////////////////////////////////////////////

	//	X - Axis
	if (m_velocity.x <= 0)
	{
		if (getTile(m_player.getPosition().x + m_velocity.x, m_player.getPosition().y) != '.' || getTile(m_player.getPosition().x + m_velocity.x, m_player.getPosition().y + m_player.getSize().y) != '.')
		{
			m_velocity.x = 0.f;
		}
	}
	else
	{
		if (getTile(m_player.getPosition().x + m_player.getSize().x + m_velocity.x, m_player.getPosition().y) != '.' || getTile(m_player.getPosition().x + m_player.getSize().x + m_velocity.x, m_player.getPosition().y + m_player.getSize().y) != '.')
		{
			m_velocity.x = 0.f;
		}
	}

	//	Y - Axis
	if (m_velocity.y <= 0)
	{
		if (getTile(m_player.getPosition().x, m_player.getPosition().y + m_velocity.y) != '.' || getTile(m_player.getPosition().x + m_player.getSize().x, m_player.getPosition().y + m_velocity.y) != '.')
		{
			m_velocity.y = 0.f;
		}
	}
	else
	{
		if (getTile(m_player.getPosition().x, m_player.getPosition().y + m_player.getSize().y + m_velocity.y) != '.' || getTile(m_player.getPosition().x + m_player.getSize().x, m_player.getPosition().y + m_player.getSize().y + m_velocity.y) != '.')
		{
			m_velocity.y = 0.f;
		}
	}

	//Move Player by velocity
	m_player.move(m_velocity.x, m_velocity.y);

	//Reset Horizontal Speed && Keep Vertical
	m_velocity.x = 0.f;



	//Update Bullet
	for (auto &i : m_vecBullets)
	{
		i.Update();
	}

	//Bullet Collision && Deletion
	std::vector<Bullet>::iterator iter;
	for (iter = m_vecBullets.begin(); iter != m_vecBullets.end();)
	{
		if (iter->getDir())
		{
			if (getTile(iter->getBullet()->getPosition().x + iter->getVelocity(), iter->getBullet()->getPosition().y) != '.' || getTile(iter->getBullet()->getPosition().x + iter->getVelocity(), iter->getBullet()->getPosition().y + iter->getBullet()->getSize().y) != '.')
			{
				iter = m_vecBullets.erase(iter);
			}
			else
				iter++;
		}
		else
		{
			if (getTile(iter->getBullet()->getPosition().x + iter->getBullet()->getSize().x + iter->getVelocity(), iter->getBullet()->getPosition().y) != '.' || getTile(iter->getBullet()->getPosition().x + iter->getBullet()->getSize().x + iter->getVelocity(), iter->getBullet()->getPosition().y + iter->getBullet()->getSize().y) != '.')
			{
				iter = m_vecBullets.erase(iter);
			}
			else iter++;
		}
	}

	

	//Player Out Of Map
	if (int(m_player.getPosition().y / pixelSize.y) == mapSize.y - 1 || int(m_player.getPosition().y / pixelSize.y) <= 0)
	{
		m_player.setPosition(m_defaultPos);
	}
}

void Player::Draw(sf::RenderWindow* window)
{
	//Draw Player
	window->draw(m_player);

	//Draw Bullets
	for (auto &i : m_vecBullets)
	{
		window->draw(*i.getBullet());
	}
}

std::vector<Bullet>* Player::getBulletVector()
{
	return &m_vecBullets;
}

void Player::Reset()
{
	m_vecBullets.clear();

	m_bLookingLeft = true;

	m_player.setPosition(m_defaultPos);

	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;
	
	m_fSpeed = 200.f;
}

void Player::changeSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

void Player::changeBulletSpeed(float speed)
{
	m_fBulletSpeed = speed;
}

void Player::changeMaxBullets(int max)
{
	m_nMaxBullets = max;
}

void Player::changeBulletDamage(int damage)
{
	m_nBulletDamage = damage;
}