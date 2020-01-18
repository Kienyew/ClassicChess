
#include <cstdlib>
#include <iostream>
#include <exception>
#include "King.h"

King::King(std::string name, ChessColor chessColor, sf::Vector2u initCoord, ChessBoard* onBoard) :
	Chess(name, chessColor, onBoard)
{
	this->initChessSprite((chessColor == White) ? WhiteKing : BlackKing);
	this->initPosition(initCoord);
}

bool King::canMoveTo(sf::Vector2u coord) const
{	
	bool success = Chess::canMoveTo(coord) &&
		std::abs(int(coordinate.x) - int(coord.x)) <= 1 &&
		std::abs(int(coordinate.y) - int(coord.y)) <= 1;

	return success;
}


King::~King()
{
}
