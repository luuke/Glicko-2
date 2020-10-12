#include "Rating.h"

Rating::Rating()
{
}

void Rating::SetRating(float r)
{
    m_Rating = (r - 1500.0f) / 173.7178f;
}

float Rating::GetRating(void)
{
    return m_Rating * 173.7178f + 1500.0f;
}

void Rating::SetDeviation(float rd)
{
    m_Deviation = rd / 173.7178f;
}

float Rating::GetDeviation(void)
{
    return m_Deviation * 173.7178f;
}
