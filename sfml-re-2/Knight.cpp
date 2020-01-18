#include <iostream>
#include <algorithm>
#include "Knight.h"




Knight::Knight(std::string name, ChessColor chessColor, sf::Vector2u initCoord, ChessBoard * onBoard) :
	Chess(name, chessColor, onBoard)
{
	this->initChessSprite((chessColor == White) ? WhiteKnight : BlackKnight);
	this->initPosition(initCoord);
}

Knight::~Knight()
{
}

bool Knight::canMoveTo(sf::Vector2u targetCoord) const
{
	if (!Chess::canMoveTo(targetCoord)) return false;
	
	sf::Vector2i delta = sf::Vector2i(targetCoord) - sf::Vector2i(coordinate);
	const auto& mnmx = std::minmax({ std::abs(delta.x), std::abs(delta.y) });
	return (mnmx.first == 1 && mnmx.second == 2);


}



