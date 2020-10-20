#ifndef __Glicko2_H
#define __Glicko2_H

#include <vector>
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
    enum class Score
    {
        Win,
        Draw,
        Loss
    };

    void CalculateNewRating(GlickoRating playerRating, GlickoRating opponentRating, float playerScore);
    void CalculateNewRating(GlickoRating playerRating, std::vector<GlickoRating> opponentRatings, std::vector<float> scores);
    void GetNewRating(GlickoRating& playerRating);

private:
    const float pi = 2 * std::asin(1.0f);
    const float e = 0.000001f; // convergence tolerance
    const float tau = 0.5f; // volatility change constrain, reasonable range: 0.3 - 1.2

    float v; // quantity v
    float delta; // quantity delta
    float a;
    float sigma_new;
    //float sigma_prime;
    //float u_prime;
    //float phi_prime;

    Glicko2Rating player;
    Glicko2Rating player_prime;
    std::vector<Glicko2Rating> opponents; 

    float _u(float r);
    float _phi(float RD);
    float _r(float u);
    float _RD(float phi);
    float _g(float phi);
    float _E(float u, float u_j, float phi_j);
    float _v(float u, float u_j, float phi_j);
    float _delta(float u, float u_j, float phi_j, float score);
    float _a(float sigma);
    float _f(float x);
};

#endif // __Glicko2_H

