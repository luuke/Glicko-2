#include "Glicko2.h"

void Glicko2::CalculateNewRating(GlickoRating playerRating, GlickoRating opponentRating, float playerScore)
{
    // Step 1/2: Determine player rating and convert to Glicko-2 scale 
    Glicko2Rating player{ u(playerRating.m_Rating), phi(playerRating.m_Deviation), playerRating.m_Volatility };
    Glicko2Rating opponent{ u(opponentRating.m_Rating), phi(opponentRating.m_Deviation), opponentRating.m_Volatility };

}

float Glicko2::u(float r)
{
    return (r - 1500.0f) / 173.7178f;
}

float Glicko2::phi(float RD)
{
    return RD / 173.7178f;
}


