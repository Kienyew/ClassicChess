#pragma once

#include <string>
#include <SFML\graphics.hpp>
#include "Helper.h"


sf::Vector2u Helper::parseCoord(std::string str_coord) {
	str_coord.erase(str_coord.find('['), 1);
	str_coord.erase(str_coord.find(']'), 1);
	size_t delim_pos = str_coord.find(',');
	return sf::Vector2u(std::stoul(str_coord.substr(0, delim_pos)), std::stoul(str_coord.substr(delim_pos + 1)));
}