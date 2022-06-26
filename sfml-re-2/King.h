
#pragma once
#include <string>
#include <utility>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Chess.h"
#include "ChessBoard.h"

class King : public Chess
{
public:
	King(std::string name, ChessColor chessColor, sf::Vector2u initCoord, ChessBoard* onBoard);
	~King();
	virtual bool canMoveTo(sf::Vector2u coord) const override;

};

