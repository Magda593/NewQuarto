#include "Board.h"
#include <algorithm>
#include <cassert>

const std::optional<Piece> Board::BaseIterator::kInvalidPiece = Piece();
const char kEmptyBoardCell[] = "____";

Board::BaseIterator::BaseIterator(std::array<std::optional<Piece>, kSize>& data, size_t offset) :
	m_data(data), m_offset(offset)
{
	// empty
}

const std::optional<Piece>& Board::BaseIterator::operator*()
{
	assert(m_offset < kSize); 
	return m_data[m_offset].has_value() ? m_data[m_offset] : kInvalidPiece;
}

const std::optional<Piece>* Board::BaseIterator::operator->()
{
	return &**this;
}

bool Board::BaseIterator::operator!=(const BaseIterator& other)
{
	return m_offset != other.m_offset;
}

Board::LineIterator& Board::LineIterator::operator++()
{
	++m_offset; 
	return *this;
}

Board::LineIterator Board::LineIterator::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

Board::ColumnIterator& Board::ColumnIterator::operator++()
{
	m_offset += kWidth; 
	return *this;
}

Board::ColumnIterator Board::ColumnIterator::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

Board::MainDiagonalIterator& Board::MainDiagonalIterator::operator++()
{
	m_offset += kWidth + 1; 
	return *this;
}

Board::MainDiagonalIterator Board::MainDiagonalIterator::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

Board::SecondaryDiagonalIterator& Board::SecondaryDiagonalIterator::operator++()
{
	m_offset += kWidth - 1; 
	return *this;
}

Board::SecondaryDiagonalIterator Board::SecondaryDiagonalIterator::operator++(int)
{
	auto copy = *this;
	++(*this);
	return copy;
}

const std::optional<Piece>& Board::operator[](const Position& position) const
{
	const auto&[line, column] = position;

	if (line >= kHeight || column >= kWidth)
		throw std::out_of_range("Board index out of bound.");

	return m_pieces[line * kWidth + column];
}

std::optional<Piece>& Board::operator[](const Position& position)
{
	const auto&[line, column] = position;

	if (line >= kHeight || column >= kWidth)
		throw "Board index out of bound.";

	return m_pieces[line * kWidth + column];
}

std::pair<Board::LineIterator, Board::LineIterator> Board::GetLine(uint32_t index)
{
	return std::make_pair(LineIterator(m_pieces, index * kWidth), LineIterator(m_pieces, (index + 1) * kWidth));
}

std::pair<Board::ColumnIterator, Board::ColumnIterator> Board::GetColumn(uint32_t index)
{
	return std::make_pair(ColumnIterator(m_pieces, index), ColumnIterator(m_pieces, kSize + index));
}

std::pair<Board::MainDiagonalIterator, Board::MainDiagonalIterator> Board::GetMainDiagonal()
{
	return std::make_pair(MainDiagonalIterator(m_pieces, 0), MainDiagonalIterator(m_pieces, kSize + kWidth));
}

std::pair<Board::SecondaryDiagonalIterator, Board::SecondaryDiagonalIterator> Board::GetSecondaryDiagonal()
{
	return std::make_pair(SecondaryDiagonalIterator(m_pieces, kWidth - 1), SecondaryDiagonalIterator(m_pieces, kSize - 1));
}

bool Board::IsFull() const
{
	return std::all_of(
		m_pieces.begin(), 
		m_pieces.end(),
		[](const std::optional<Piece>& optionalPiece)
		{
			return optionalPiece.has_value();
		}
	);
	return false;
}

std::ostream & operator<<(std::ostream & os, const Board & board)
{
	Board::Position position;
	auto&[line, column] = position;

	for (line = 0; line < Board::kHeight; ++line)
	{
		for (column = 0; column < Board::kWidth; ++column)
		{
			if (board[position])
				os << *board[position];
			else
				os << kEmptyBoardCell;	// TODO: change this to invalid piece, when possible
			os << ' ';
		}
		os << std::endl;
	}

	return os;
}