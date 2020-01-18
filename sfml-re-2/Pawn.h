#pragma once
#include "Chess.h"

class Pawn : public Chess
{
public:
	Pawn(std::string name, ChessColor chessColor, sf::Vector2u initCoord, ChessBoard* onBoard);
	~Pawn();

	virtual bool canMoveTo(sf::Vector2u targetCoord) const override;

};