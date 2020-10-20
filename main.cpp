#include <iostream>
#include <vector>
#include "Match.h"
#include "Glicko2.h"
#include "GlickoRating.h"
#include "Player.h"

int main()
{
    std::cout << "Glicko-2 system" << std::endl;

    // Create players
    Player p1{ 1 };
    p1.m_Rating.m_Rating = 1500.0f;
    p1.m_Rating.m_Deviation = 200.0f;
    p1.m_Rating.m_Volatility = 0.06f;

    Player o1{ 2 };
    o1.m_Rating.m_Rating = 1400.0f;
    o1.m_Rating.m_Deviation = 30.0f;
    o1.m_Rating.m_Volatility = 0.06f;

    Player o2{ 3 };
    o2.m_Rating.m_Rating = 1550.0f;
    o2.m_Rating.m_Deviation = 100.0f;
    o2.m_Rating.m_Volatility = 0.06f;

    Player o3{ 4 };
    o3.m_Rating.m_Rating = 1700.0f;
    o3.m_Rating.m_Deviation = 300.0f;
    o3.m_Rating.m_Volatility = 0.06f;

    // Setup matches
    std::vector<GlickoRating> opponentRatings{ o1.m_Rating, o2.m_Rating, o3.m_Rating };

    // Play matches
    std::vector<float> scores{ 1.0f, 0.0f, 0.0f };

    // Update ratings
    //      Get player rating
    //      Get match output
    //      Calculate new rating
    Glicko2 glicko;
    glicko.CalculateNewRating(p1.m_Rating, opponentRatings, scores);
    glicko.GetNewRating(p1.m_Rating);
    //      Set new player rating
    //m1.GetWinner().m_Rating.SetRating(winnerNewRating);
    //m1.GetLoser().m_Rating.SetRating(loserNewRating);


    std::cin.get();
}
