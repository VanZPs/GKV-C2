// bird.cpp - Implementasi kelas burung dengan deteksi tabrakan

#include "bird.h"
#include "airplane.h"

Bird::Bird(const Position& _pos, float _size, float _speed)
    : pos(_pos), size(_size), speed(_speed), wingAngle(0.0f) {}

void Bird::draw() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    
    // Matikan pencahayaan untuk burung
    glDisable(GL_LIGHTING);
    
    // Warna burung (hitam)
    glColor3f(0.1f, 0.1f, 0.1f);
    
    // Badan burung
    glPushMatrix();
    glScalef(size, size * 0.5f, size);
    glutSolidSphere(0.5f, 10, 10);
    glPopMatrix();
    
    // Kepala burung
    glPushMatrix();
    glTranslatef(size * 0.4f, size * 0.1f, 0.0f);
    glutSolidSphere(size * 0.3f, 10, 10);
    
    // Paruh
    glColor3f(1.0f, 0.7f, 0.0f);
    glPushMatrix();
    glTranslatef(size * 0.3f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glutSolidCone(size * 0.1f, size * 0.3f, 10, 10);
    glPopMatrix();
    
    glPopMatrix();
    
    // Sayap
    glColor3f(0.1f, 0.1f, 0.1f);
    
    // Sayap kiri
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, size * 0.2f);
    glRotatef(wingAngle, 1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(-size, 0.0f, size);
        glVertex3f(0.0f, 0.0f, size);
    glEnd();
    glPopMatrix();
    
    // Sayap kanan
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -size * 0.2f);
    glRotatef(-wingAngle, 1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(-size, 0.0f, -size);
        glVertex3f(0.0f, 0.0f, -size);
    glEnd();
    glPopMatrix();
    
    // Aktifkan kembali pencahayaan
    glEnable(GL_LIGHTING);
    
    glPopMatrix();
}

void Bird::update() {
    // Gerakan burung
    pos.x += speed;
    
    // Animasi sayap
    wingAngle += 5.0f;
    if (wingAngle > 30.0f) {
        wingAngle = -30.0f;
    }
    
    // Jika burung keluar dari area game, kembalikan ke sisi lain
    if (pos.x > 100.0f) {
        pos.x = -100.0f;
        // Ubah ketinggian secara acak saat respawn
        pos.y = 10.0f + (rand() % 10);
        pos.z = -50.0f + (rand() % 100);
    }
}

bool Bird::checkCollision(const Airplane& plane) const {
    // Hitung jarak antara pesawat dan burung
    float dx = plane.pos.x - pos.x;
    float dy = plane.pos.y - pos.y;
    float dz = plane.pos.z - pos.z;
    
    // Jarak dalam 3D
    float distance = sqrt(dx*dx + dy*dy + dz*dz);
    
    // Burung memiliki hitbox lebih kecil dibanding awan
    // Gunakan ukuran burung * 2 karena burung pada dasarnya lebih kecil dari pesawat
    return (distance < size * 2.0f);
}
