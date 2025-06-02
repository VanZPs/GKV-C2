// airplane.h - Definisi kelas pesawat pemain

#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "common.h" // common.h sudah menyertakan <GL/glut.h>

// Kelas untuk pesawat pemain
class Airplane {
public:
    Position pos;
    float rotationY;
    float speed;

    GLuint textureID; // ID untuk tekstur pesawat

    Airplane();

    // Menggambar pesawat
    void draw();

    // Pergerakan pesawat
    void moveForward();
    void turnLeft();
    void turnRight();
    void moveUp();
    void moveDown();

    // Fungsi untuk memuat tekstur
    void loadTexture(const char* filename);
};

#endif // AIRPLANE_H
