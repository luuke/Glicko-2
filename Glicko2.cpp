#include <cmath>
#include "Glicko2.h"

void Glicko2::CalculateNewRating(GlickoRating playerRating, GlickoRating opponentRating, float playerScore)
{
    // Step 1/2: Determine player rating and convert to Glicko-2 scale 
    Glicko2Rating player{ u(playerRating.m_Rating), phi(playerRating.m_Deviation), playerRating.m_Volatility };
    Glicko2Rating opponent{ u(opponentRating.m_Rating), phi(opponentRating.m_Deviation), opponentRating.m_Volatility };

    // Step 3: Compute quantity v
    float tmp_v = v(player.u, opponent.u, opponent.phi);
}

float Glicko2::u(float r)
{
    return (r - 1500.0f) / 173.7178f;
}

float Glicko2::phi(float RD)
{
    return RD / 173.7178f;
}

float Glicko2::g(float phi)
{
    return (1 / sqrt(1 + ((3 * powf(phi, 2)) / (powf(pi(), 2)))));
}

float Glicko2::E(float u, float u_j, float phi_j)
{
    return (1 / (1 + expf(-1 * g(phi_j) * (u - u_j))));
}

float Glicko2::v(float u, float u_j, float phi_j)
{
    float tmp_g = g(phi_j);
    float tmp_E = E(u, u_j, phi_j);

    return powf((powf(tmp_g, 2)* tmp_E* (1 - tmp_E)), -1);
}
