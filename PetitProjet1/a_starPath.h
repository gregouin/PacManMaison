#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

enum class Direction{North, south, East, West , None};

int heuristique(sf::Vector2i a, sf::Vector2i b);

Direction nextDirection(sf::Vector2i start, sf::Vector2i end, std::array<std::string, 20> map);


