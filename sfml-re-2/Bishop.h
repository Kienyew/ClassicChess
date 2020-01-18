#pragma once
#include "Chess.h"
class Bishop : public Chess
{
public:
	Bishop(std::string name, ChessColor chessColor, sf::Vector2u initCoord, ChessBoard* onBoard);
	~Bishop();

	virtual bool canMoveTo(sf::Vector2u coord) const override;
};

