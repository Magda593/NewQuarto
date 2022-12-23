#include "Game.h"
#include"Board.h"
#include"Player.h"
#include "UnusedPieces.h"
#include "BoardStateChecker.h"

void Game::Run()
{
	Board board;
	UnusedPieces unusedPieces;

	std::string playerName;
	std::cout << "First player name: ";
	std::cin >> playerName;
	Player firstPlayer(playerName);

	std::cout << "Second player name: ";
	std::cin >> playerName;
	Player secondPlayer(playerName);

	std::reference_wrapper<Player> pickingPlayer = firstPlayer;
	std::reference_wrapper<Player> placingPlayer = secondPlayer;

	while (true)
	{
		system("cls");
		std::cout << "Board: \n" << board << std::endl;
		std::cout << "UnusedPieces: " << unusedPieces << std::endl;
		std::cout << pickingPlayer << ", you should pick a piece for " << placingPlayer << std::endl;

		Piece pickedPiece;
		while (true)
		{
			try
			{
				pickedPiece = std::move(pickingPlayer.get().PickPiece(std::cin, unusedPieces));
				break;
			}
			catch (const char* errorMessage)
			{
				std::cout << errorMessage;
			}
		}

		std::cout << placingPlayer << ", you should place the piece on the board.\n";
		Board::Position placingPosition;
		while (true)
		{
			try
			{
				placingPosition = placingPlayer.get().PlacedPiece(std::cin, std::move(pickedPiece),board);
				break;
			}
			catch (const char* errorMessage)
			{
				std::cout << errorMessage;
			}
		}
		BoardStateChecker::State state = BoardStateChecker::Check(board, placingPosition);
		if (state == BoardStateChecker::State::Win)
		{
			std::cout << "Good job " << placingPlayer << ", you won the game.\n";
			break;
		}
		else if (state == BoardStateChecker::State::Draw)
		{
			std::cout << "Damn, it ended in a draw, better luck next time.\n";
			break;
		}
		std::swap(pickingPlayer, placingPlayer);

	}
}
