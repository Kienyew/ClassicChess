#include <iostream>
#include "ChessSet.h"

ChessSet::ChessSet(ChessBoard * boardptr) :
	chessptr_map({
		{ "WKg", new King("WKg", White,{ 4, 7 }, boardptr) },
		{ "WQ", new Queen("WQ", White,{ 3, 7 }, boardptr) },
		{ "WB-1", new Bishop("WB-1", White,{ 2, 7 }, boardptr) },
		{ "WB-2", new Bishop("WB-2", White,{ 5, 7 }, boardptr) },
		{ "WK-1", new Knight("WK-1", White,{ 1, 7 }, boardptr) },
		{ "WK-2", new Knight("WK-2", White,{ 6, 7 }, boardptr) },
		{ "WR-1", new Rok("WR-1", White,{ 0, 7 }, boardptr) },
		{ "WR-2", new Rok("WR-2", White,{ 7, 7 }, boardptr) },
		{ "WP-1", new Pawn("WP-1", White,{ 0, 6 }, boardptr) },
		{ "WP-2", new Pawn("WP-2", White,{ 1, 6 }, boardptr) },
		{ "WP-3", new Pawn("WP-3", White,{ 2, 6 }, boardptr) },
		{ "WP-4", new Pawn("WP-4", White,{ 3, 6 }, boardptr) },
		{ "WP-5", new Pawn("WP-5", White,{ 4, 6 }, boardptr) },
		{ "WP-6", new Pawn("WP-6", White,{ 5, 6 }, boardptr) },
		{ "WP-7", new Pawn("WP-7", White,{ 6, 6 }, boardptr) },
		{ "WP-8", new Pawn("WP-8", White,{ 7, 6 }, boardptr) },
		{ "BKg", new King("BKg", Black,{ 4, 0 }, boardptr) },
		{ "BQ", new Queen("BQ", Black,{ 3, 0 }, boardptr) },
		{ "BB-1", new Bishop("BB-1", Black,{ 2, 0 }, boardptr) },
		{ "BB-2", new Bishop("BB-2", Black,{ 5, 0 }, boardptr) },
		{ "BK-1", new Knight("BK-1", Black,{ 1, 0 }, boardptr) },
		{ "BK-2", new Knight("BK-2", Black,{ 6, 0 }, boardptr) },
		{ "BR-1", new Rok("BR-1", Black,{ 0, 0 }, boardptr) },
		{ "BR-2", new Rok("BR-2", Black,{ 7, 0 }, boardptr) },
		{ "BP-1", new Pawn("BP-1", Black,{ 0, 1 }, boardptr) },
		{ "BP-2", new Pawn("BP-2", Black,{ 1, 1 }, boardptr) },
		{ "BP-3", new Pawn("BP-3", Black,{ 2, 1 }, boardptr) },
		{ "BP-4", new Pawn("BP-4", Black,{ 3, 1 }, boardptr) },
		{ "BP-5", new Pawn("BP-5", Black,{ 4, 1 }, boardptr) },
		{ "BP-6", new Pawn("BP-6", Black,{ 5, 1 }, boardptr) },
		{ "BP-7", new Pawn("BP-7", Black,{ 6, 1 }, boardptr) },
		{ "BP-8", new Pawn("BP-8", Black,{ 7, 1 }, boardptr) }

		})
{

}

ChessSet::~ChessSet()
{
	for (auto& pr : chessptr_map) {
		delete pr.second;
	}
}

void ChessSet::iter(std::function<void(Chess*)> f)
{
	for (auto& pr : chessptr_map) {
		f(pr.second);
	}
}

void ChessSet::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& pr : chessptr_map)
	{
		Chess* chess = pr.second;
		if (chess->alive()) {
			target.draw(*chess);
		}
	}
}
