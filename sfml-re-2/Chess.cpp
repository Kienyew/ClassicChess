#include "Chess.h"
#include "ChessBoard.h"
#include <stdexcept>
#include <string>
#include <iostream>

Chess::Chess(std::string name, ChessColor chessColor, ChessBoard* boardptr) :
	m_name(name), chessColor(chessColor), boardptr(boardptr),  m_step(0), m_alive(true)
{

}


Chess::~Chess()
{
}

bool Chess::canMoveTo(sf::Vector2u coord) const
{
	if (!this->inBoard(coord)) return false;
	Chess* chessOnCoord = boardptr->chessOn(coord);
	return
		chessOnCoord == nullptr ||
		chessOnCoord->color() != this->color();
}

bool Chess::tryMoveTo(sf::Vector2u coord)
{
	if (!canMoveTo(coord))
		return false;

	Node& targetNode = (*boardptr)[coord];
	boardptr->setChessOn(this->coordinate, nullptr);
	boardptr->setChessOn(coord, this);
	setPosition(targetNode.getPosition());
	coordinate = coord;
	++m_step;
	return true;
}

inline bool Chess::inBoard(sf::Vector2u coord) const
{
	return boardptr->inBound(coord);
}

void Chess::kill(Chess* killed_by)
{
	boardptr->setChessOn(this->coordinate, killed_by);
	m_alive = false;
}

void Chess::resize(sf::FloatRect new_rect)
{
	sf::Vector2f scale = { .9f / 75.f * new_rect.width  , .9f / 75.f * new_rect.height };
	this->innerSprite.setScale(scale);
	this->innerSprite.setPosition({ new_rect.left , new_rect.top });
}

std::pair<std::shared_ptr<sf::Texture>, sf::Sprite>Chess::getChessSprite(ChessType chessType)
{
	decltype(chess_tiles.operator[]({ 0,0 })) ret;
	switch (chessType)
	{
	case WhiteKing:
		ret = chess_tiles[{0, 0}];
		break;
	case WhiteQueen:
		ret = chess_tiles[{1, 0}];
		break;
	case WhiteBishop:
		ret = chess_tiles[{2, 0}];
		break;
	case WhiteKnight:
		ret = chess_tiles[{3, 0}];
		break;
	case WhiteRok:
		ret = chess_tiles[{4, 0}];
		break;
	case WhitePawn:
		ret = chess_tiles[{5, 0}];
		break;
	case BlackKing:
		ret = chess_tiles[{0, 1}];
		break;
	case BlackQueen:
		ret = chess_tiles[{1, 1}];
		break;
	case BlackBishop:
		ret = chess_tiles[{2, 1}];
		break;
	case BlackKnight:
		ret = chess_tiles[{3, 1}];
		break;
	case BlackRok:
		ret = chess_tiles[{4, 1}];
		break;
	case BlackPawn:
		ret = chess_tiles[{5, 1}];
		break;
	}
	return { ret.first, sf::Sprite(*ret.first, ret.second) };
}

void Chess::initChessSprite(ChessType chessType)
{
	const auto& ret = Chess::getChessSprite(chessType);
	this->store_textureptr = ret.first;
	this->innerSprite = ret.second;
	sf::Vector2f scale = { .9f / 600.f * boardptr->node_width * boardptr->size().x , .9f / 600.f * boardptr->node_height * boardptr->size().y };
	this->innerSprite.setScale(scale);
}

void Chess::initPosition(sf::Vector2u coord)
{
	if (!Chess::canMoveTo(coord)) 
		throw std::runtime_error((this->name() + ": initPosition: " + "unable to initialize position.").c_str());

	Node& targetNode = (*boardptr)[coord];
	boardptr->setChessOn(coord, this);
	setPosition(targetNode.getPosition());
	coordinate = coord;

}

bool Chess::checkLine(sf::Vector2u targetCoord, sf::Vector2i dir) const
{
	sf::Vector2u checkCoord = coordinate;
	while (this->inBoard(checkCoord)) {
		checkCoord = { checkCoord.x + dir.x, checkCoord.y + dir.y };
		Chess* chessOn = boardptr->chessOn(checkCoord);
		if (chessOn != nullptr) {
			if (chessOn->color() == this->color() || checkCoord != targetCoord) {
				return false;
			}
		}
		
		if (targetCoord == checkCoord)
			return true;
	}

	return false;
	
}

TextureTiles Chess::chess_tiles("images/500px-Chess.png", 2, 6);

