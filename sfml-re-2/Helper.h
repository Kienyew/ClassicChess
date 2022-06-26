#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class Helper
{
public:
	Helper() = delete;
	~Helper() = delete;
	static sf::Vector2u parseCoord(std::string str_coord);
};

