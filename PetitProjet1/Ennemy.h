#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

enum Couleur
{
	rouge = 0,
	rose = 1,
	bleu = 2,
	orange = 3

};


class Ennemy
{
private:
	sf::Vector2f m_pos;

	sf::RectangleShape m_sprite;

	sf::Vector2i m_targetPosition;

	sf::Vector2i m_nextPosition;

	sf::Vector2f tt;
	sf::Vector2f lerp;

	bool IsAlive;



public:

	sf::RectangleShape GetSprite() const;
	void move(sf::Vector2i targetpos);
	
	Ennemy(const Couleur& couleur) ;
	~Ennemy();


};

