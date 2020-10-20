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

void Glicko2::CalculateNewRating(GlickoRating playerRating, std::vector<GlickoRating> opponentRatings, std::vector<float> scores)
{
    // Step 0: Clear all variables or create new Glicko-2 object???

    // Step 1/2: Determine player rating and convert to Glicko-2 scale 
    player.u = _u(playerRating.m_Rating);
    player.phi = _phi(playerRating.m_Deviation);
    player.sigma = playerRating.m_Volatility;

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

    // Step 4: Compute quantity delta
    tmpSum = 0.0f;
    for (size_t i = 0; i < opponents.size(); i++)
    {
        tmpSum += (_g(opponents[i].phi) * (scores[i] - _E(player.u, opponents[i].u, opponents[i].phi)));
    }
    delta = v * tmpSum;

    // Step 5: Determine new volatility value, sigma'
    a = _a(player.sigma);
    float A = a;
    float B;
    if (powf(delta, 2) > (powf(player.sigma, 2) + v)) // delta^2 > sigma^2 + v
    {
        B = log(powf(delta, 2) - powf(player.phi, 2) - v);
    }
    else // delta^2 <= phi^2 + v
    {
        int k = 1;
        while (_f(a - k * tau) < 0)
        {
            k++;
        }
        B = a - k * tau;
    }

    float f_A = _f(A);
    float f_B = _f(B);

    float C;
    float f_C;
    while (abs(B - A) > e)
    {
        C = A + (A - B) * f_A / (f_B - f_A);
        f_C = _f(C);

        if ((f_C * f_B) < 0)
        {
            A = B;
            f_A = f_B;
        }
        else
        {
            f_A = f_A / 2;
        }

        B = C;
        f_B = f_C;
    }

    //sigma_prime = exp(A / 2);
    player_prime.sigma = exp(A / 2); 

    // Step 6: Update rating deviation to new pre-rating period value, phi*
    sigma_new = sqrt(powf(player.phi, 2) + powf(player_prime.sigma, 2));

    // Step 7: Update rating and deviation to new values, u' and phi'
    player_prime.phi = 1 / sqrt((1 / powf(sigma_new, 2)) + (1 / v));

    tmpSum = 0.0f;
    for (size_t i = 0; i < opponents.size(); i++)
    {
        tmpSum += (_g(opponents[i].phi) * (scores[i] - _E(player.u, opponents[i].u, opponents[i].phi)));
    }
    player_prime.u = player.u + powf(player_prime.phi, 2) * tmpSum;
}

float Glicko2::_u(float r)
{
    return (r - 1500.0f) / 173.7178f;
}

float Glicko2::_phi(float RD)
{
    return RD / 173.7178f;
}

float Glicko2::_r(float u)
{
    return 173.7178 * u + 1500.0f;
}

float Glicko2::_RD(float phi)
{
    return 173.7178 * phi;
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

float Glicko2::_f(float x)
{
    float A = exp(x) * (powf(delta, 2) - powf(player.phi, 2) - v - exp(x));
    float B = 2 * powf((powf(player.phi, 2) + v + exp(x)), 2);
    float C = x - a;
    float D = powf(tau, 2);

    return ((A / B) - (C / D));
}

