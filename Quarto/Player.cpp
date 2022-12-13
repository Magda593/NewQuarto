#include "Player.h"

#include <string>

Player::Player(const std::string& name) :
	m_name(name)
{
	// Empty
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os << player.m_name;
}
