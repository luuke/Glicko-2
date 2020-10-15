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
    constexpr float pi() { return (2 * std::asin(1.0)); }

    float u(float r);
    float phi(float RD);
    float g(float phi);
    float E(float u, float u_j, float phi_j);
    float v(float u, float u_j, float phi_j);
};

#endif // __Glicko2_H

