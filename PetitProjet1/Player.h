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
	sf::Vector2f t;
	sf::Vector2f lerp;
	sf::Vector2i m_targetPosition;
	

	int m_score;
	
	void TakeACoin(Tilemap& tilemap);

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
	sf::CircleShape GetSprite();
	sf::Vector2f getPos();
	sf::Vector2i getTargetPos();

	int getScore();
	

};

