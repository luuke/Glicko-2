#ifndef __Player_H
#define __Player_H

#include <stdint.h>
#include <string>
#include "Rating.h"

class Player
{
public:
    Player(uint32_t id);

    Rating m_Rating;

    std::string GetName(void);
private:
    uint32_t m_ID;
};

#endif // __Player_H

