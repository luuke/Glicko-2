#ifndef __GlickoRating_H
#define __GlickoRating_H

class GlickoRating
{
public:
    GlickoRating(float rating = 1500.0f, float deviation = 350.0f, float volatility = 0.06f);

    void SetRating(float r);
    float GetRating(void);

    void SetDeviation(float rd);
    float GetDeviation(void);

private:
    float m_Rating;
    float m_Deviation;
    float m_Volatility;
};

#endif // __GlickoRating_H

