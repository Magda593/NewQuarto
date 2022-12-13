#include "Player.h"

#include <iostream>


int main()
{
	Piece piece(Piece::Body::Full, Piece::Color::Dark, Piece::Height::Short, Piece::Shape::Square);
	std::cout << "Full, Dark, Short, Square piece: " << piece << std::endl;

	Board board;
	std::cout << "Empty board:\n" << board << std::endl;

	board[{0, 0}] = std::move(piece);
	std::cout << "Moved piece to board:\n" << board << std::endl;

	UnusedPieces unusedPieces;
	std::cout << "All available pieces:\n" << unusedPieces << std::endl;
	unusedPieces.PickPiece("0001");
	std::cout << "Extracted \"0001\" remaining pieces after extracted:\n" << unusedPieces << std::endl;

	Player player("Player_1");
	std::cout << player<<std::endl;

    return 0;
}