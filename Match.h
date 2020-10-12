#ifndef __Match_H
#define __Match_H

#include "Player.h"

class Match
{
public:
    Match(Player& p1, Player& p2);

    Player& GetWinner(void);
    Player& GetLoser(void);

private:
    Player& m_Player1;
    Player& m_Player2;

    Player* m_Winner;
    Player* m_Loser;
};

#endif // __Match_H

