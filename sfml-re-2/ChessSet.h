// Just a map of <string chess_name: Chess* chess>
/*
Names:
	"${Color}${ChessType}[-${No.}]"

	eg:
		"WKg": WhiteKing
		"BQ": BlackQueen
		"WR-1": WhiteRok no.1
		"BK-2": BlackKnight no.2
*/

#include <map>
#include <string>
#include <functional>
#include "ChessBoard.h"
#include "Chesses.h"

#pragma once
class ChessSet: public sf::Drawable
{
public:
	ChessSet(ChessBoard* boardptr);
	~ChessSet();

	void iter(std::function<void(Chess*)> f);
	Chess* operator[](std::string chess_name) { return chessptr_map.at(chess_name); }


	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	std::map<std::string, Chess*> chessptr_map;

	
};

