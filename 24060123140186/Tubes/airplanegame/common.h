// common.h - Struktur data dan definisi umum

#ifndef COMMON_H
#define COMMON_H

#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Struktur untuk posisi 3D
struct Position {
    float x, y, z;
    Position(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}
};

// Struktur untuk warna RGB
struct Color {
    float r, g, b;
    Color(float _r = 1.0f, float _g = 1.0f, float _b = 1.0f) : r(_r), g(_g), b(_b) {}
};

#endif // COMMON_H
