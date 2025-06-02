// Versi lengkap dan diperbaiki dari cloud.cpp

#include "cloud.h"
#include "airplane.h"

Cloud::Cloud(const Position& _pos, float _size, float _speed)
    : pos(_pos), size(_size), speed(_speed) {}

void Cloud::draw() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    
    // Matikan pencahayaan untuk awan
    glDisable(GL_LIGHTING);
    
    // Warna awan (putih)
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Bentuk awan menggunakan beberapa bola
    // Bola pusat
    glutSolidSphere(size, 20, 20);
    
    // Bola tambahan untuk membentuk awan
    glPushMatrix();
    glTranslatef(size * 0.7f, 0.0f, 0.0f);
    glutSolidSphere(size * 0.8f, 16, 16);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-size * 0.7f, 0.0f, 0.0f);
    glutSolidSphere(size * 0.8f, 16, 16);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, size * 0.7f);
    glutSolidSphere(size * 0.8f, 16, 16);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -size * 0.7f);
    glutSolidSphere(size * 0.8f, 16, 16);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(size * 0.4f, size * 0.3f, 0.0f);
    glutSolidSphere(size * 0.6f, 16, 16);
    glPopMatrix();
    
    // Aktifkan kembali pencahayaan
    glEnable(GL_LIGHTING);
    
    glPopMatrix();
}

void Cloud::update() {
    // Gerakan awan
    pos.x += speed;
    
    // Jika awan keluar dari area game, kembalikan ke sisi lain
    if (pos.x > 100.0f) {
        pos.x = -100.0f;
    }
}

bool Cloud::checkCollision(const Airplane& plane) const {
    // Hitung jarak antara pesawat dan awan
    float dx = plane.pos.x - pos.x;
    float dy = plane.pos.y - pos.y;
    float dz = plane.pos.z - pos.z;
    
    // Jarak dalam 3D
    float distance = sqrt(dx*dx + dy*dy + dz*dz);
    
    // Deteksi tabrakan jika pesawat berada di dalam awan
    // Gunakan faktor yang lebih besar (1.5x ukuran awan) untuk membuat deteksi lebih sensitif
    return (distance < size * 1.5f);
}
