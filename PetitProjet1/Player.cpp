#include "Player.h"

void Player::TakeACoin(Tilemap &tilemap)
{
	tilemap.GetCodeMap()[m_targetPosition.y][m_targetPosition.x] = ' ';
	m_score+=100;
	

}

void Player::TakeAPacGum(Tilemap& tilemap)
{
	tilemap.GetCodeMap()[m_targetPosition.y][m_targetPosition.x] = ' ';
	canAttack = true;
	std::cout << " PacMan peux manger" << std::endl;
	CoolDown.restart();
}

Player::Player()
{
	canAttack = false;
	CoolDown.start();

	m_sprite.setRadius(20);
	m_position = { 40,40 };
	m_sprite.setPosition(m_position);
	m_targetPosition = { 1,1 };
	m_score = 0;
	m_dir = none;
}

void Player::targetTo(const Direction& dir)
{
	sf::Vector2i currentTile(
		static_cast<int>(std::round(m_position.x / 40.0f)),
		static_cast<int>(std::round(m_position.y / 40.0f))
	);

	//lerp = { 0,0 };
	if (dir==m_dir)
	{
		return;
	}
	switch (dir)
	{
	case Player::north:
		m_dir = north;
		m_targetPosition = currentTile;
		break;
	case Player::south:
		m_dir = south;
		m_targetPosition = currentTile;
		break;
	case Player::east:
		m_dir = east;
		m_targetPosition = currentTile;
		break;
	case Player::west:
		m_dir = west;
		m_targetPosition = currentTile;
		break;
	default:
		break;
	}

}

void Player::move(Tilemap& tilemap)
{
	if (CoolDown.getElapsedTime().asSeconds()>=7)
	{
		std::cout << " PacMan peux plus manger" << std::endl;
		CoolDown.reset();
		CoolDown.stop();
		canAttack = false;
	}
	sf::Vector2i currentTile(
		static_cast<int>(std::round(m_position.x / 40.0f)),
		static_cast<int>(std::round(m_position.y / 40.0f))
	);

	if (currentTile == m_targetPosition) {
		if (tilemap.IsACoin(currentTile))
		{
			TakeACoin(tilemap);
		}
		else if (tilemap.IsAPacGum(currentTile))
		{
			TakeAPacGum(tilemap);
		}
		switch (m_dir)
		{
		case Player::north:
			m_targetPosition.y--;
			if (tilemap.IsAWall(m_targetPosition))
			{
				m_targetPosition.y++;
			}
			
			break;
		case Player::south:
			m_targetPosition.y++;
			if (tilemap.IsAWall(m_targetPosition))
			{
				m_targetPosition.y--;
			}
			break;
		case Player::east:
			m_targetPosition.x--;
			if (m_targetPosition.x <= -1)
			{
				m_targetPosition.x = 18;
				m_position.x = 18 * 40;
				m_sprite.setPosition(m_position);
				return;
			}
			if (tilemap.IsAWall(m_targetPosition))
			{
				m_targetPosition.x++;
			}


			break;
		case Player::west:
			m_targetPosition.x++;
			if (m_targetPosition.x >= 19)
			{
				m_targetPosition.x = 0;
				m_position.x = 0;
				m_sprite.setPosition(m_position);
				return;
			}
			if (tilemap.IsAWall(m_targetPosition))
			{
				m_targetPosition.x--;
			}
			break;
		default:
			break;
		}
	}
	
	


	sf::Vector2f b(m_targetPosition.x * 40.0f, m_targetPosition.y * 40.0f);
	sf::Vector2f delta = b - m_position;
	float vitesse = 2.0f;

	if (std::abs(delta.x) <= vitesse && std::abs(delta.y) <= vitesse) {
		m_position = b;
	}
	else {
		if (delta.x != 0.0f) m_position.x += (delta.x > 0 ? 1.0f : -1.0f) * vitesse;
		if (delta.y != 0.0f) m_position.y += (delta.y > 0 ? 1.0f : -1.0f) * vitesse;
	}

	
	m_sprite.setPosition(m_position);
}
	// ancienne version avec un mouvement lerp
	/*sf::Vector2f a = m_position;
	sf::Vector2f b;

	
	b.x = m_targetPosition.x * 40;
	b.y = m_targetPosition.y * 40;

	lerp.x = a.x + t.x * (b.x - a.x);;
	lerp.y = a.y + t.y * (b.y - a.y);;
	m_position = lerp;
	m_sprite.setPosition(m_position);*/


sf::CircleShape Player::GetSprite() const
{
	return m_sprite;
}

sf::Vector2f Player::getPos() const
{
	return m_position;
}

sf::Vector2i Player::getTargetPos() const 
{
	return m_targetPosition;
}

sf::Vector2i Player::getCurrentPos() const
{
	return sf::Vector2i(
		static_cast<int>(std::round(m_position.x / 40.0f)),
		static_cast<int>(std::round(m_position.y / 40.0f))
	);;
}

bool Player::GetCanAttack() const
{
	return canAttack;
}

int Player::getScore()
{
	return m_score;
}



