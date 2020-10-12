#ifndef __Rating_H
#define __Rating_H

class Rating
{
public:
    Rating();

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

