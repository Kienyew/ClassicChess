#pragma once
#include "Chess.h"
class Knight : public Chess
{
public:
	Knight(std::string name, ChessColor chessColor, sf::Vector2u initCoord, ChessBoard* onBoard);
	~Knight();

	virtual bool canMoveTo(sf::Vector2u coord) const override;
};

