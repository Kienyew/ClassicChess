#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "Chess.h"
#include "ChessBoard.h"

class Queen : public Chess
{
public:
	Queen(std::string name, ChessColor chessColor, sf::Vector2u initCoord, ChessBoard* onBoard);
	~Queen();

	// Inherited via Chess
	virtual bool canMoveTo(sf::Vector2u coord) const override;
};

