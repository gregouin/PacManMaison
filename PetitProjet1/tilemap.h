#pragma once
#include <iostream>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>
class Tilemap
{

private:
	std::array<std::string, 20> m_codeMap;

public:
	Tilemap();
	sf::VertexArray LoadMap();
	bool IsAWall(const sf::Vector2i& pos);
	bool IsACoin(const sf::Vector2i& pos);
	bool IsAPacGum(const sf::Vector2i& pos);
	std::array<std::string, 20>& GetCodeMap();
	

};

