// Every Plate in ChessBoard, maybe I shouldn't call it Node. whatever.

#pragma once
#include <SFML\Graphics.hpp>

class Node : public sf::Drawable
{
	friend void swap(Node&, Node&);
	friend class ChessBoard;
public:
	Node(sf::FloatRect float_rect, bool white = true);

	~Node();

	bool isWhite() { return white; }

	sf::Vector2f getSize() { return innerRect().getSize(); }

	sf::Vector2f getPosition() { return sf::Vector2f(rect.getPosition()); }

	void resize(sf::FloatRect new_rect);

	const sf::RectangleShape& innerRect() { return rect; }

	Node& operator=(const Node& rhs) {
		Node copy(*this);
		swap(*this, copy);
		return *this;
	}

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	bool white;
	sf::RectangleShape rect;
};

