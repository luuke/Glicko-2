#include <sstream>
#include "Player.h"

Player::Player(uint32_t id)
    : m_ID(id)
{
}

std::string Player::GetName(void)
{
    std::stringstream ss;
    ss << "Player_" << m_ID;
    return ss.str();
}
