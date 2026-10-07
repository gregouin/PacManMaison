#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"




class Ennemy
{


public:

	sf::RectangleShape GetSprite() const;
	void move(const Player& player, const Ennemy& Blinky);

	void IsDead(const Player& player);

	sf::Vector2i getCurrentPos() const;
	
	enum Couleur
	{
		rouge = 0,
		rose = 1,
		bleu = 2,
		orange = 3

	};

	Ennemy(const Couleur& couleur) ;
	~Ennemy();

private:

	Couleur who;

	sf::Vector2f m_pos;

	sf::RectangleShape m_sprite;

	sf::Vector2i m_targetPosition;

	sf::Vector2i m_nextPosition;

	sf::Vector2f tt;
	sf::Vector2f lerp;

	bool IsAlive;


};

