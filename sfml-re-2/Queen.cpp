
#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Chess.h"
#include "ChessBoard.h"
#include "Queen.h"

Queen::Queen(std::string name, ChessColor chessColor, sf::Vector2u initCoord, ChessBoard * onBoard) :
	Chess(name, chessColor, onBoard)
{
	this->initChessSprite((chessColor == White) ? WhiteQueen : BlackQueen);
	this->initPosition(initCoord);
}



Queen::~Queen()
{
}

bool Queen::canMoveTo(sf::Vector2u targetCoord) const
{	
	bool success = Chess::canMoveTo(targetCoord);
	if (success){
		sf::Vector2i delta = sf::Vector2i(targetCoord) - sf::Vector2i(coordinate);
		success = success && (delta.x == 0 || delta.y == 0 || std::abs(delta.x) == std::abs(delta.y));

		if (success) {
			int mx = std::max(std::abs(delta.x), std::abs(delta.y));
			sf::Vector2i dir = { delta.x / mx, delta.y / mx };
			success = success && Chess::canMoveTo(targetCoord) && checkLine(targetCoord, dir);
		}
	}

	return success;
}
