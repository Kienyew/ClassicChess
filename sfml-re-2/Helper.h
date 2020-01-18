#pragma once
#include <string>
class Helper
{
public:
	Helper() = delete;
	~Helper() = delete;
	static sf::Vector2u parseCoord(std::string str_coord);
};

