#ifndef BALL_H
#define BALL_H

#include "platform.h"

class Ball {
public:
    Ball();
    ~Ball() = default;
    
    //inisialisasi posisi bola
    void initPosition(std::mt19937& rng);
    
    // menggambar bola dengan posisi dan rotasi terkini
    void draw(float ballRotation) const;
    
    //update posisi bola
    void updatePosition(float time, float angle, float ballStrength);
    
    void setBackboardFlag(bool flag);
    bool checkBackboardCollision() const;
    bool checkFloorCollision() const;
    
    // gambar shooting assistance
    void drawShootAssistance(float ballStrength, float angle) const;

    float getX() const { return xPos; }
    float getY() const { return yPos; }
    BallType getType() const { return type; }
    
private:
    float xPos;
    float yPos;
    BallType type;
    float velocityX;
    float velocityY;
    bool backboardCollision;
};

#endif
