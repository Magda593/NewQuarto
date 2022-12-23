#pragma once

#include "Board.h"
#include "UnusedPieces.h"


class Player
{
public:
	Player(const std::string& name);

	friend std::ostream& operator << (std::ostream& os, const Player& player);
	Piece PickPiece(std::istream& in, UnusedPieces& unusedPieces);
	Board::Position PlacedPiece(std::istream &in, Piece piece, Board &board);



private:
	std::string m_name;
};

