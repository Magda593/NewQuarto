#include "BoardStateChecker.h"
#include <numeric>

BoardStateChecker::State BoardStateChecker::Check(const Board& b, const Board::Position& position)
{
	Board& board = const_cast<Board&>(b);
	const auto&[lineIndex, columnIndex] = position;

	auto reducer = [](const Piece& piece1, const std::optional<Piece>& piece2)
	{
		return piece1.Intersection(piece2.value());
	};

	{
		auto [first, last] = board.GetLine(lineIndex);
		Piece piece = std::accumulate(first, last, (first++)->value(), reducer);
		if (piece.HasAnyFeatureSet())
			return State::Win;
	}

	{
		auto [first, last] = board.GetColumn(columnIndex);
		Piece piece = std::accumulate(first, last, (first++)->value(), reducer);
		if (piece.HasAnyFeatureSet())
			return State::Win;
	}

	if(lineIndex == columnIndex)
	{
		auto [first, last] = board.GetMainDiagonal();
		Piece piece = std::accumulate(first, last, (first++)->value(), reducer);
		if (piece.HasAnyFeatureSet())
			return State::Win;
	}
	else if(lineIndex == (Board::kWidth - columnIndex - 1))
	{
		auto [first, last] = board.GetSecondaryDiagonal();
		Piece piece = std::accumulate(first, last, (first++)->value(), reducer);
		if (piece.HasAnyFeatureSet())
			return State::Win;
	}

	if (board.IsFull())
		return State::Draw;

    return State::None;
}