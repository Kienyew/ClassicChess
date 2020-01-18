#include "TextureTiles.h"
#include <iostream>

typedef sf::Vector2i v2i;
typedef sf::Vector2u v2u;
typedef sf::Vector2f v2f;

TextureTiles::TextureTiles(const std::string & fname, unsigned int row, unsigned int col, unsigned int startX, unsigned int startY, unsigned int endx_offset, unsigned int endy_offset) : 
	startX(startX),
	startY(startY),
	texture_ptr(std::make_shared<sf::Texture>())

{
	texture_ptr->loadFromFile(fname);
	texture_ptr->setSmooth(true);
	v2u tx_size = texture_ptr->getSize();
	height = (tx_size.y - endx_offset - startY) / row;
	width = (tx_size.x - endx_offset - startX) / col;
}

TextureTiles::~TextureTiles()
{
}

std::pair<std::shared_ptr<sf::Texture>, sf::IntRect> TextureTiles::operator[](sf::Vector2u index)
{
	return { texture_ptr, sf::IntRect(startX + width * index.x, startY + height * index.y, width, height) };
}
