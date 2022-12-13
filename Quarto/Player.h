#pragma once

#include "Board.h"
#include "UnusedPieces.h"


class Player
{
public:
	Player(const std::string& name);

	friend std::ostream& operator << (std::ostream& os, const Player& player);

private:
	std::string m_name;
};

