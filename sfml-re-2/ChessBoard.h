#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "Node.h"
#include "Chess.h"

class Chess;

class ChessBoard : public sf::Drawable
{
	friend class Chess;

public:
	ChessBoard(size_t col, size_t row, float width, float height);
	~ChessBoard();
	Node& operator[](sf::Vector2u coord);
	sf::Vector2f nodeSize() { return { node_width, node_height }; };
	sf::Vector2u size() const { return { col, row }; }
	sf::Vector2f mapCoordToPos(sf::Vector2u coord) const { return { coord.x * node_width, coord.y * node_height }; }
	sf::Vector2u mapPosToCoord(sf::Vector2f pos) const;
	const Node* posInNode(sf::Vector2f pos);
	bool inBound(sf::Vector2u coord) const { return (coord.x >= 0 && coord.y >= 0 && coord.x < col && coord.y < row); }
	Chess* chessOn(sf::Vector2u coord);
	void printLayout();
	void resize(sf::Vector2f new_size);
	
	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

protected:
	std::vector<std::vector<Node>> nodesGrid;
	std::vector<std::vector<Chess*>> chessPtrGrid;
	void setChessOn(sf::Vector2u coord, Chess* chessptr);


private:
	size_t row, col;
	float node_width, node_height;


};

