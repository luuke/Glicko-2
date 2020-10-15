#include "GlickoRating.h"

GlickoRating::GlickoRating(float rating, float deviation, float volatility)
{
    SetRating(rating);
    SetDeviation(deviation);
    m_Volatility = volatility;
}

void GlickoRating::SetRating(float r)
{
    m_Rating = (r - 1500.0f) / 173.7178f;
}

float GlickoRating::GetRating(void)
{
    return m_Rating * 173.7178f + 1500.0f;
}

void GlickoRating::SetDeviation(float rd)
{
    m_Deviation = rd / 173.7178f;
}

float GlickoRating::GetDeviation(void)
{
    return m_Deviation * 173.7178f;
}
