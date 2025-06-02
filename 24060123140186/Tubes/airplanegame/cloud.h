// cloud.h - Definisi kelas awan dengan deteksi tabrakan

#ifndef CLOUD_H
#define CLOUD_H

#include "common.h"
#include "airplane.h"

// Kelas untuk awan di langit
class Cloud {
public:
    Position pos;
    float size;
    float speed;
    
    Cloud(const Position& _pos, float _size, float _speed);
    
    void draw();
    void update();
    
    // Fungsi deteksi tabrakan dengan pesawat
    bool checkCollision(const Airplane& plane) const;
};

#endif // CLOUD_H
