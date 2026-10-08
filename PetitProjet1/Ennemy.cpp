#include "Ennemy.h"
#include <cmath>
#include "a_starPath.h"
#include "tilemap.h"
#include <SFML/Graphics.hpp>
#include <iostream>


//note a moi : crée un static pour stocker les coordonées de blinky avec un if couleur rouge 

sf::RectangleShape Ennemy::GetSprite() const
{
	return m_sprite;
}


void Ennemy::move(const Player& player, const Ennemy& Blinky)
{
	sf::Vector2i targetPos;
	sf::Vector2i temp;
	switch (who)
	{
	case Ennemy::rouge:
		targetPos = player.getTargetPos();
		break;
	case Ennemy::rose:
		if ((this->getCurrentPos().x-player.getTargetPos().x)+ (this->getCurrentPos().y-player.getTargetPos().y)<3)
		{
			targetPos = player.getCurrentPos();
		}
		targetPos = player.getTargetPos();
		switch (player.m_dir)
		{
		case Player::north:
			targetPos.y -= 2;
			while (targetPos.y<0)
			{
				targetPos.y++;
			}
			break;
		case Player::south:
			targetPos.y += 2;
			while (targetPos.y > 20)
			{
				targetPos.y--;
			}
			break;
		case Player::east:
			targetPos.x -= 2;
			while (targetPos.x < 0)
			{
				targetPos.x++;
			}
			break;
		case Player::west:
			targetPos.x += 2;
			while (targetPos.x > 18)
			{
				targetPos.x--;
			}
			break;
		default:
			break;
		}

			if (Tilemap().GetCodeMap()[targetPos.y][targetPos.x] == '#')
			{
				sf::Vector2i Direction[] = { {1,0},{-1,0},{0,1},{0,-1} };
				for (sf::Vector2i dir : Direction)
				{
					sf::Vector2i voisin = { this->getCurrentPos().x + dir.x,this->getCurrentPos().y + dir.y };
					if (voisin.y >= 0 && voisin.y < 20 &&
						voisin.x >= 0 && voisin.x < 20 &&
						Tilemap().GetCodeMap()[voisin.y][voisin.x] != '#')
					{
						targetPos = voisin;
					}
				}
			}
		
		break;
	case Ennemy::bleu:

		targetPos = player.getTargetPos();
		
		temp = targetPos - Blinky.getCurrentPos();
		temp *= 2;
		targetPos += Blinky.getCurrentPos() - temp;
		if (targetPos.x >= 19)
		{
			targetPos.x = 18;
		}
		else if (targetPos.x < 0) {
			targetPos.x = 0;
		}
		if (targetPos.y >= 20)
		{
			targetPos.y = 19;
		}
		else if (targetPos.y < 0) {
			targetPos.y = 0;
		}
		//if (Tilemap().GetCodeMap()[targetPos.y][targetPos.x] == '#')
		//{
		//	sf::Vector2i Direction[] = { {1,0},{-1,0},{0,1},{0,-1} };
		//	for (sf::Vector2i dir : Direction)
		//	{
		//		sf::Vector2i voisin = { this->getCurrentPos().x + dir.x,this->getCurrentPos().y + dir.y };
		//		if (voisin.y >= 0 && voisin.y < 20 &&
		//			voisin.x >= 0 && voisin.x < 20 &&
		//			Tilemap().GetCodeMap()[voisin.y][voisin.x] != '#')
		//		{
		//			targetPos = voisin;
		//		}
		//	}
		//}
		std::cout << targetPos.x << " : " << targetPos.y << std::endl;
		break;
	case Ennemy::orange:
		//if ((this->getCurrentPos().x - player.getTargetPos().x) + (this->getCurrentPos().y - player.getTargetPos().y) < 8) {
		//	targetPos = sf::Vector2i(19, 2);
		//}
		//else
		//{
			targetPos = player.getTargetPos();
		//}
		
		break;
	default:
		break;
	}


	sf::Vector2f b(m_nextPosition.x * 40.0f, m_nextPosition.y * 40.0f);
	sf::Vector2f delta = b - m_pos;


	if (m_nextPosition.x <= 0 && m_nextPosition.y == 9)
	{
		m_pos = sf::Vector2f(18 * 40, 9 * 40);
		m_sprite.setPosition(m_pos);
		m_nextPosition = sf::Vector2i(17, 9);
	}
	if (m_nextPosition.x >= 18 && m_nextPosition.y == 9)
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
	Direction dir;
	if (!player.GetCanAttack())
	{
		dir = nextDirection(m_nextPosition, targetPos, Tilemap().GetCodeMap());
	}
	else
	{
		sf::Vector2i reverseTargetPos = sf::Vector2i(20 - player.getTargetPos().x, 20 - player.getTargetPos().y);
		dir = nextDirection(m_nextPosition, reverseTargetPos, Tilemap().GetCodeMap());
	}


	if (currentTile.x >= 0 && currentTile.x <= 5 && currentTile.y == 9 && dir == Direction::East && targetPos.x > 11)
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


void Ennemy::IsDead(const Player& player)
{
	if (player.getCurrentPos() == this->getCurrentPos())
	{
		std::cout << "fantome est mort " << std::endl;
		if (player.GetCanAttack()) {
			IsAlive = false;

		}
	}
}

sf::Vector2i Ennemy::getCurrentPos() const
{
	return sf::Vector2i(
		static_cast<int>(std::round(m_pos.x / 40.0f)),
		static_cast<int>(std::round(m_pos.y / 40.0f))
	);
}


Ennemy::Ennemy(const Couleur& couleur) : IsAlive(false), m_nextPosition(10, 10)
{
	who = couleur;

	m_targetPosition = sf::Vector2i(0, 0);



	m_sprite.setSize(sf::Vector2f(40.0f, 40.0f));



	switch (couleur)
	{
	case Couleur::rouge:
		m_sprite.setFillColor(sf::Color::Red);
		m_pos = { 400.0f,400.0f };
		m_sprite.setPosition(m_pos);
		break;
	case Couleur::rose:
		m_sprite.setFillColor(sf::Color::Magenta);
		m_pos = { 440.0f,400.0f };
		m_sprite.setPosition(m_pos);
		break;
	case Couleur::bleu:
		m_sprite.setFillColor(sf::Color::Cyan);
		m_pos = { 360.0f,400.0f };
		m_sprite.setPosition(m_pos);
		break;
	case Couleur::orange:
		m_sprite.setFillColor(sf::Color(255, 165, 0, 255));
		m_pos = { 320.0f,400.0f };
		m_sprite.setPosition(m_pos);
		break;
	default:
		break;
	}
}

Ennemy::~Ennemy()
{
}
