// building.h - Definisi kelas bangunan dengan bayangan

#ifndef BUILDING_H
#define BUILDING_H

#include "common.h"

// Kelas untuk bangunan (kota)
class Building {
public:
    Position pos;
    float width, height, depth;
    Color color;
    
    Building(const Position& _pos, float _w, float _h, float _d, const Color& _color);
    
    void draw();
    void drawShadow(); // Method baru untuk menggambar bayangan
};

#endif // BUILDING_H
