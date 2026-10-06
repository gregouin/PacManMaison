#include "Ennemy.h"
#include <cmath>
#include "a_starPath.h"
#include "tilemap.h"
#include <SFML/Graphics.hpp>

sf::RectangleShape Ennemy::GetSprite() const
{
	return m_sprite;
}


void Ennemy::move(sf::Vector2i targetPos)
{
	sf::Vector2f b(m_nextPosition.x * 40.0f, m_nextPosition.y * 40.0f);
	sf::Vector2f delta = b - m_pos;


	if (m_nextPosition.x<=0 && m_nextPosition.y == 9)
	{
		m_pos = sf::Vector2f(18 * 40, 9*40);
		m_sprite.setPosition(m_pos);
		m_nextPosition = sf::Vector2i(17, 9);
	}
	if (m_nextPosition.x >= 18 && m_nextPosition.y ==9)
	{
		m_pos = sf::Vector2f(0 * 40, 9 * 40);
		m_sprite.setPosition(m_pos);
		m_nextPosition = sf::Vector2i(1, 9);
	}
	float vitesse = 1.7f;

	if (std::abs(delta.x) > vitesse || std::abs(delta.y) > vitesse) {
		if (delta.x != 0.0f) m_pos.x += (delta.x > 0.0f ? 1.0f : -1.0f) * vitesse;
		if (delta.y != 0.0f) m_pos.y += (delta.y > 0.0f ? 1.0f : -1.0f) * vitesse;


		m_sprite.setPosition(m_pos);

		return;
	}
	m_pos = b;
	m_sprite.setPosition(m_pos);

	sf::Vector2i currentTile(
		static_cast<int>(std::round(m_pos.x / 40.0f)),
		static_cast<int>(std::round(m_pos.y / 40.0f))
	);

	Direction dir = nextDirection(m_nextPosition, targetPos, Tilemap().GetCodeMap());

	if (currentTile.x >= 0 && currentTile.x <= 5 && currentTile.y ==9 && dir == Direction::East && targetPos.x > 11)
	{
		m_nextPosition.x--;
		return;
	}
	if (currentTile.x >= 13 && currentTile.x <= 18 && currentTile.y == 9 && dir == Direction::West && targetPos.x < 7)
	{
		m_nextPosition.x++;
		return;
	}
	switch (dir)
	{
	case Direction::North:
		m_nextPosition.y--;
		break;
	case Direction::south:
		m_nextPosition.y++;
		break;
	case Direction::East:
		m_nextPosition.x++;
		break;
	case Direction::West:
		m_nextPosition.x--;
		break;
	case Direction::None:
		break;
	default:
		break;
	}

}


Ennemy::Ennemy(const Couleur& couleur) : IsAlive(false), m_nextPosition(10,10)
{


	tt = { 0.04f,0.04f };
	m_targetPosition = sf::Vector2i(0,0);

	m_pos = { 400.0f,400.0f };

	m_sprite.setSize(sf::Vector2f(40.0f,40.0f));
	m_sprite.setPosition(m_pos);


	switch (couleur)
	{
	case Couleur::rouge:
		m_sprite.setFillColor(sf::Color::Red);
		break;
	case Couleur::rose:
		m_sprite.setFillColor(sf::Color::Magenta);
		break;
	case Couleur::bleu:
		m_sprite.setFillColor(sf::Color::Blue);
		break;
	case Couleur::orange:
		m_sprite.setFillColor(sf::Color(255,165,0,255));
		break;
	default:
		break;
	}
}

Ennemy::~Ennemy()
{
}
