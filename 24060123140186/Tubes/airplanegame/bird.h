// bird.h - Definisi kelas burung dengan deteksi tabrakan

#ifndef BIRD_H
#define BIRD_H

#include "common.h"
#include "airplane.h"

// Kelas untuk burung di langit
class Bird {
public:
    Position pos;
    float size;
    float speed;
    float wingAngle;
    
    Bird(const Position& _pos, float _size, float _speed);
    
    void draw();
    void update();
    
    // Fungsi deteksi tabrakan dengan pesawat
    bool checkCollision(const Airplane& plane) const;
};

#endif // BIRD_H
