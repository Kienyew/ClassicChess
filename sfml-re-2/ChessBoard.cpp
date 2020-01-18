#include "Node.h"
#include "ChessBoard.h"
#include <vector>
#include <iostream>
#include <exception>


ChessBoard::ChessBoard(size_t col, size_t row, float width, float height):
	col(col), row(row), node_width(width / col), node_height(height / row)
{
	for (int c = 0; c < int(col); ++c) {
		nodesGrid.emplace_back();
		chessPtrGrid.emplace_back();
		for (int r = 0; r < int(row); ++r) {
			nodesGrid[c].emplace_back(sf::FloatRect(c * node_width, r * node_height, node_width, node_height), (r + c) % 2 == 0);
			chessPtrGrid[c].push_back(nullptr);
		}
	}
}

ChessBoard::~ChessBoard()
{
}

Node & ChessBoard::operator[](sf::Vector2u coord)
{
	if (!inBound(coord))
		throw std::exception("Coordinate out of bound.");

	return nodesGrid[coord.x][coord.y];
}

sf::Vector2u ChessBoard::mapPosToCoord(sf::Vector2f pos) const
{
	
	size_t i = size_t(pos.x / node_width);
	size_t j = size_t(pos.y / node_height);
	if (inBound({ i, j })) return { i,j };
	else return { col + 1, row + 1 };
}

const Node * ChessBoard::posInNode(sf::Vector2f pos)
{
	size_t i = size_t((node_width * col) / pos.x);
	size_t j = size_t((node_height * row) / pos.y);

	if (inBound({ i, j })) 
		return &this->operator[]({ i, j });
	else
		return nullptr;
}

Chess * ChessBoard::chessOn(sf::Vector2u coord)
{
	if (!inBound(coord)) throw std::exception("chessOn: coordinate not in bound.");
	return chessPtrGrid[coord.x][coord.y];
}

void ChessBoard::printLayout()
{
	sf::Vector2u board_size = this->size();
	for (size_t row = 0; row< board_size.y; ++row) {
		for (size_t col = 0; col < board_size.x; ++col) {
			Chess* targetChess = this->chessOn({ col, row });
			const std::string& targetChessName = (targetChess == nullptr ? "" : targetChess->name());
			int whitespace_length = 11 - targetChessName.length();
			whitespace_length = (whitespace_length < 0) ? 0 : whitespace_length;
			std::cout << targetChessName + std::string(whitespace_length, ' ') << " ";
		}
		std::cout << std::endl;
	}
}

void ChessBoard::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& nodes: nodesGrid) {
		for (auto& node : nodes) {
			target.draw(node);
		}
	}
}

void ChessBoard::setChessOn(sf::Vector2u coord, Chess * chessptr)
{
	if (!inBound(coord)) throw std::exception("setChessPtr: coordinate not in bound.");
	chessPtrGrid[coord.x][coord.y] = chessptr;
}

void ChessBoard::resize(sf::Vector2f new_size) 
{
	node_width = new_size.x / col;
	node_height = new_size.y / row;

	for (size_t c = 0; c < nodesGrid.size(); ++c) {
		for (size_t r = 0; r < nodesGrid[c].size(); ++r) {
			Node& node = nodesGrid[c][r];
			node.resize(sf::FloatRect(c * node_width, r * node_height, node_width, node_height));
		}
			
	}

}
