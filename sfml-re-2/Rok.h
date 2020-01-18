#pragma once
#include "Chess.h"
class Rok :
	public Chess
{
public:
	Rok(std::string name, ChessColor chessColor, sf::Vector2u initCoord, ChessBoard* onBoard);
	~Rok();

	virtual bool canMoveTo(sf::Vector2u coord) const override;
};

