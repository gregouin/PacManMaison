#include "Ennemy.h"
#include <cmath>
#include "a_starPath.h"
#include "tilemap.h"

sf::RectangleShape Ennemy::GetSprite() const
{
	return m_sprite;
}


void Ennemy::move(sf::Vector2i targetPos)
{
	sf::Vector2f b(m_nextPosition.x * 40.0f, m_nextPosition.y * 40.0f);
	sf::Vector2f delta = b - m_pos;

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


Ennemy::Ennemy(const Couleur& couleur, Player& player) : m_player(player), IsAlive(false), m_nextPosition(10,10)
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
