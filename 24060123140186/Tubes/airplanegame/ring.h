// ring.h - Definisi kelas ring (cincin)

#ifndef RING_H
#define RING_H

#include "common.h"
#include "airplane.h"

// Kelas untuk rintangan (cincin)
class Ring {
public:
    Position pos;
    float radius;
    Color color;
    bool collected;
    
    Ring(const Position& _pos, float _radius, const Color& _color);
    
    void draw();
    
    // Deteksi jika pesawat melewati cincin
    bool checkCollision(const Airplane& plane);
};

#endif // RING_H
