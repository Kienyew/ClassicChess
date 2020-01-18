
#include <iostream>
#include <cstdlib>
#include "Pawn.h"


Pawn::Pawn(std::string name, ChessColor chessColor, sf::Vector2u initCoord, ChessBoard * onBoard) :
	Chess(name, chessColor, onBoard)
{
	this->initChessSprite((chessColor == White) ? WhitePawn : BlackPawn);
	this->initPosition(initCoord);
}

Pawn::~Pawn()
{
}

bool Pawn::canMoveTo(sf::Vector2u targetCoord) const
{
	if (!Chess::canMoveTo(targetCoord)) return false;
		sf::Vector2i delta = sf::Vector2i(targetCoord) - sf::Vector2i(coordinate);

		if (color() == White) {
			if (delta.y >= 0) return false;
		}
		else {
			if (delta.y <= 0) return false;
		}

		size_t dy_abs = std::abs(delta.y);
		size_t dx_abs = std::abs(delta.x);
		if (dy_abs == 2) 
		{
			if (delta.x != 0) return false;
			if (this->step() != 0) return false;
			if (boardptr->chessOn(sf::Vector2u(this->coordinate.x, this->coordinate.y + delta.y / 2)) != nullptr) return false;
			if (boardptr->chessOn(sf::Vector2u(this->coordinate.x, this->coordinate.y + delta.y)) != nullptr) return false;

			return true;
		}else if (dy_abs == 1) 
		{
			Chess* chessOn = boardptr->chessOn(targetCoord);
			if (dx_abs == 0) {
				if (chessOn != nullptr) return false;
			}
			else if (dx_abs == 1) {
				if (chessOn == nullptr) return false;
			}

			return true;
		}
		
		return false;
		
	}

