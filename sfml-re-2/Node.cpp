#include "Node.h"
#include <SFML\Graphics.hpp>
#include <utility>

Node::Node(sf::FloatRect float_rect, bool white) :
	rect({ float_rect.width, float_rect.height }),
	white(white)
{
	resize(float_rect);
	if (white) {
		rect.setFillColor(sf::Color(200, 200, 200));
	}
	else {
		rect.setFillColor(sf::Color(50, 50, 50));
	}
}


Node::~Node()
{
}

void Node::resize(sf::FloatRect new_rect)
{
	rect.setPosition({ new_rect.left, new_rect.top });
	rect.setSize({ new_rect.width, new_rect.height });
}

void Node::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(rect);
}
