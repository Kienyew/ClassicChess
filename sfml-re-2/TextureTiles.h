#pragma once
#include <string>
#include <initializer_list>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

class TextureTiles
{
public:
	TextureTiles(const std::string& fname, unsigned int row, unsigned int col, unsigned int startX = 0, unsigned int startY = 0, unsigned int endx_offset = 0, unsigned int endy_offset = 0);
	~TextureTiles();
	std::pair<std::shared_ptr<sf::Texture>, sf::IntRect> operator[](sf::Vector2u index);

private:
	unsigned int startX, startY, width, height;
	std::shared_ptr<sf::Texture> texture_ptr;
};

