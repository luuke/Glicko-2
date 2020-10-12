#include <cstdlib>
#include <ctime>
#include "Match.h"

Match::Match(Player& p1, Player& p2)
    : m_Player1(p1), m_Player2(p2)
{
    std::srand(std::time(NULL));
    int result = rand() % 2;

    if (result == 0)
    {
        m_Winner = &m_Player1;
        m_Loser = &m_Player2;
    }
    else
    {
        m_Winner = &m_Player2;
        m_Loser = &m_Player1;
    }
}

Player& Match::GetWinner(void)
{
    return *m_Winner;
}

Player& Match::GetLoser(void)
{
    return *m_Loser;
}
