#ifndef __Rating_H
#define __Rating_H

class Rating
{
public:
    Rating(float rating = 1500.0f, float deviation = 350.0f, float volatility = 0.06f);

    void SetRating(float r);
    float GetRating(void);

    void SetDeviation(float rd);
    float GetDeviation(void);

private:
    float m_Rating;
    float m_Deviation;
    float m_Volatility;
};

#endif // __Rating_H

