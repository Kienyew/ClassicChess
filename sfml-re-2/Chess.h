// Base class of all Chess type: [Pawn, King, Queen, Bishop, Rok, Knight]



#pragma once

#include <string>
#include <memory>
#include <utility>
#include <set>
#include <SFML\Graphics.hpp>
#include "ChessBoard.h"
#include "TextureTiles.h"


enum ChessType {
	WhiteKing, WhiteQueen, WhiteRok, WhiteKnight, WhiteBishop, WhitePawn,
	BlackKing, BlackQueen, BlackRok, BlackKnight, BlackBishop, BlackPawn
};

enum ChessColor {
	White, Black
};

class Chess : public sf::Drawable
{
public:
	Chess(std::string name, ChessColor chessColor, ChessBoard* boardptr);
	virtual ~Chess() = 0;
	sf::Vector2f getPosition() const { return innerSprite.getPosition(); };

	sf::Vector2u getCoordinate() const { return coordinate; }

	virtual bool canMoveTo(sf::Vector2u coord) const;

	bool tryMoveTo(sf::Vector2u coord);

	bool inBoard(sf::Vector2u coord) const;

	bool alive() { return m_alive; }

	const std::string& name() const { return m_name; }

	size_t step() const { return m_step; }

	ChessColor color() const { return chessColor; }

	void kill(Chess* killed_by);

	void resize(sf::FloatRect new_rect);

	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override { target.draw(innerSprite); }

	static std::pair<std::shared_ptr<sf::Texture>, sf::Sprite> getChessSprite(ChessType chessType);

protected:
	virtual void setPosition(sf::Vector2f pos) { innerSprite.setPosition(pos); };
	sf::Vector2u coordinate;
	std::shared_ptr<sf::Texture> store_textureptr;
	sf::Sprite innerSprite;
	ChessBoard * boardptr;
	void initChessSprite(ChessType chessType);
	void initPosition(sf::Vector2u coord);
	bool checkLine(sf::Vector2u targetCoord, sf::Vector2i dir) const;
	

private:
	std::string m_name;
	ChessColor chessColor;
	size_t m_step;
	bool m_alive;
	
	static TextureTiles chess_tiles;
};

