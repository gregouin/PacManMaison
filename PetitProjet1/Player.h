#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "tilemap.h"

class Player
{

private : 
	sf::Vector2f m_position;
	sf::CircleShape m_sprite;
	sf::Vector2i m_targetPosition;
	

	int m_score;

	bool canAttack;
	sf::Clock CoolDown;
	
	void TakeACoin(Tilemap& tilemap);
	void TakeAPacGum(Tilemap& tilemap);

public :
	enum Direction
	{
		north = 0,
		south = 1,
		east = 2,
		west = 3,
		none = 4

	};
	Direction m_dir;
	Player();
	void targetTo(const Direction& dir);
	void move(Tilemap& tilemap);
	sf::CircleShape GetSprite() const;
	sf::Vector2f getPos() const;
	sf::Vector2i getTargetPos() const;
	sf::Vector2i getCurrentPos() const;

	bool GetCanAttack() const;

	int getScore();
	

};

