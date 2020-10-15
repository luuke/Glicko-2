#ifndef __Glicko2_H
#define __Glicko2_H

#include "GlickoRating.h"

class Glicko2
{
    struct Glicko2Rating
    {
        float u;
        float phi;
        float sigma;
    };

public:
    void CalculateNewRating(GlickoRating playerRating, GlickoRating opponentRating, float playerScore);

private:
    float u(float r);
    float phi(float RD);


};

#endif // __Glicko2_H

