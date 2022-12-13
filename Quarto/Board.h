#pragma once

#include "Piece.h"

#include <array>
#include <optional>

class Board
{
public:
	static const size_t kWidth = 4;
	static const size_t kHeight = 4;
	static const size_t kSize = kWidth * kHeight;

public:
	using Position = std::pair<uint8_t, uint8_t>;

    class BaseIterator
    {
        static const std::optional<Piece> kInvalidPiece;

    public:
		BaseIterator(std::array<std::optional<Piece>, kSize>& data, size_t offset);
		const std::optional<Piece>& operator *();
		const std::optional<Piece>* operator ->();
		bool operator != (const BaseIterator& other);

    protected:
        std::array<std::optional<Piece>, kSize>& m_data;
        size_t m_offset;
    };

    class LineIterator : public BaseIterator
    {
    public:
        using BaseIterator::BaseIterator;

        LineIterator& operator ++();
        LineIterator operator ++(int);
    };

    class ColumnIterator : public BaseIterator
    {
    public:
        using BaseIterator::BaseIterator;

        ColumnIterator& operator ++();
        ColumnIterator operator ++(int);
    };

    class MainDiagonalIterator : public BaseIterator
    {
    public:
        using BaseIterator::BaseIterator;

        MainDiagonalIterator& operator ++();
        MainDiagonalIterator operator ++(int);
    };

    class SecondaryDiagonalIterator : public BaseIterator
    {
    public:
        using BaseIterator::BaseIterator;

        SecondaryDiagonalIterator& operator ++();
        SecondaryDiagonalIterator operator ++(int);
    };

public:
	Board() = default;

	// Getter
	const std::optional<Piece>& operator[] (const Position& pos) const;
	// Getter and/or Setter
	std::optional<Piece>& operator[] (const Position& pos);

	std::pair<LineIterator, LineIterator> GetLine(uint32_t index);
    std::pair<ColumnIterator, ColumnIterator> GetColumn(uint32_t index);
    std::pair<MainDiagonalIterator, MainDiagonalIterator> GetMainDiagonal();
    std::pair<SecondaryDiagonalIterator, SecondaryDiagonalIterator> GetSecondaryDiagonal();

	bool IsFull() const;

	friend std::ostream& operator << (std::ostream& os, const Board& board);

private:
	std::array<std::optional<Piece>, kSize> m_pieces;
};

