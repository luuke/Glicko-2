#include "Rating.h"

Rating::Rating()
{
}

void Rating::SetRating(float r)
{
    rating = (r - 1500.0f) / 173.7178f;
}

float Rating::GetRating(void)
{
    return rating * 173.7178f + 1500.0f;
}

void Rating::SetDeviation(float rd)
{
    deviation = rd / 173.7178f;
}

float Rating::GetDeviation(void)
{
    return deviation * 173.7178f;
}
