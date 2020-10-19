#include <cmath>
#include <vector>
#include "Glicko2.h"

void Glicko2::CalculateNewRating(GlickoRating playerRating, GlickoRating opponentRating, float playerScore)
{
    // Step 1/2: Determine player rating and convert to Glicko-2 scale 
    Glicko2Rating player{ _u(playerRating.m_Rating), _phi(playerRating.m_Deviation), playerRating.m_Volatility };
    Glicko2Rating opponent{ _u(opponentRating.m_Rating), _phi(opponentRating.m_Deviation), opponentRating.m_Volatility };

    // Step 3: Compute quantity v
    float tmp_v = _v(player.u, opponent.u, opponent.phi);

    // Step 4: Compute quantity delta
    float tmp_delta = _delta(player.u, opponent.u, opponent.phi, playerScore);

    // Step 5: Determine new volatility value, sigma'

}

float Glicko2::CalculateNewRating(GlickoRating playerRating, std::vector<GlickoRating> opponentRatings, std::vector<float> scores)
{
    // Step 0: Clear all variables or create new Glicko-2 object???

    // Step 1/2: Determine player rating and convert to Glicko-2 scale 
    Glicko2Rating player{ _u(playerRating.m_Rating), _phi(playerRating.m_Deviation), playerRating.m_Volatility };
    Glicko2Rating opponent;
    for (auto rating : opponentRatings)
    {
        opponent.u = _u(rating.m_Rating);
        opponent.phi = _phi(rating.m_Deviation);
        opponent.sigma = rating.m_Volatility;
        opponents.push_back(opponent);
    }

    // Step 3: Compute quantity v
    float tmpSum = 0.0f;
    float tmp_E;
    for (auto o : opponents)
    {
        tmp_E = _E(player.u, o.u, o.phi);
        tmpSum += (powf(_g(o.phi), 2) * tmp_E * (1 - tmp_E));
    }
    v = 1 / tmpSum;



    return 0.0f;
}

float Glicko2::_u(float r)
{
    return (r - 1500.0f) / 173.7178f;
}

float Glicko2::_phi(float RD)
{
    return RD / 173.7178f;
}

float Glicko2::_g(float phi)
{
    return (1 / sqrt(1 + ((3 * powf(phi, 2)) / (powf(pi, 2)))));
}

float Glicko2::_E(float u, float u_j, float phi_j)
{
    return (1 / (1 + expf(-1 * _g(phi_j) * (u - u_j))));
}

float Glicko2::_v(float u, float u_j, float phi_j)
{
    float tmp_g = _g(phi_j);
    float tmp_E = _E(u, u_j, phi_j);

    return powf((powf(tmp_g, 2)* tmp_E* (1 - tmp_E)), -1);
}

float Glicko2::_delta(float u, float u_j, float phi_j, float score)
{
    float tmp_v = _v(u, u_j, phi_j);
    float tmp_g = _g(phi_j);
    float tmp_E = _E(u, u_j, phi_j);

    return tmp_v * tmp_g * (score - tmp_E);
}

float Glicko2::_a(float sigma)
{
    return log(powf(sigma, 2));
}

float Glicko2::_f(float x, float delta, float phi, float v, float tau, float a)
{
    float A = exp(x) * (powf(delta, 2) - powf(phi, 2) - v - exp(x));
    float B = 2 * powf((powf(phi, 2) + v + exp(x)), 2);
    float C = x - a;
    float D = powf(tau, 2);

    return ((A / B) - (C / D));
}

