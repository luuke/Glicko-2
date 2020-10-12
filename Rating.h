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
    float rating;
    float deviation;
    float volatility;
};

#endif // __Rating_H

