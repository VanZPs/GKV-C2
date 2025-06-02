#ifndef NUMBERS_H
#define NUMBERS_H

#include "platform.h"

class Numbers {
public:
    Numbers();
    ~Numbers() = default;

    void drawDigit(int number, float size) const;

    void drawNumber(int number, float size) const;
 
    bool drawTime(time_t start, float size);
    
    void drawSemaphore(time_t start, float size);

    void drawScore(int score) const;

    bool isTimeUp() const { return timeUp; }
    
private:
    bool timeUp;
};

#endif
