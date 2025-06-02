// ring.cpp (Fixed) - Memperbaiki deteksi tabrakan dengan gedung

#include "ring.h"

Ring::Ring(const Position& _pos, float _radius, const Color& _color)
    : pos(_pos), radius(_radius), color(_color), collected(false) {}

void Ring::draw() {
    if (collected) return;
    
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    
    // Matikan pencahayaan untuk cincin agar lebih terlihat
    glDisable(GL_LIGHTING);
    
    // Tambahkan efek glow untuk cincin
    glColor3f(color.r * 0.7f, color.g * 0.7f, color.b * 0.7f);
    glutSolidTorus(radius/3.5f, radius * 1.1f, 20, 20);
    
    // Cincin utama (bercahaya)
    glColor3f(color.r, color.g, color.b);
    glutSolidTorus(radius/4.0f, radius, 20, 20);
    
    // Aktifkan kembali pencahayaan
    glEnable(GL_LIGHTING);
    
    glPopMatrix();
}

bool Ring::checkCollision(const Airplane& plane) {
    if (collected) return false;
    
    float dx = plane.pos.x - pos.x;
    float dy = plane.pos.y - pos.y;
    float dz = plane.pos.z - pos.z;
    
    float distance = sqrt(dx*dx + dy*dy + dz*dz);
    
    // Deteksi tabrakan yang lebih akurat
    if (distance < radius * 1.5f) {
        // Deteksi jika pesawat melewati bagian tengah cincin
        // Hitung vektor dari pusat cincin ke pesawat
        float vx = dx;
        float vy = dy;
        float vz = dz;
        
        // Normalisasi vektor
        float length = sqrt(vx*vx + vy*vy + vz*vz);
        if (length > 0) {
            vx /= length;
            vy /= length;
            vz /= length;
        }
        
        // Hitung jarak tegak lurus dari pusat cincin ke garis pesawat
        // (ini adalah cara sederhana, tidak sempurna)
        float perpDistance = sqrt(dx*dx + dy*dy + dz*dz - (vx*vx + vy*vy + vz*vz));
        
        // Jika jarak ini kurang dari radius cincin, maka pesawat lewat melalui cincin
        if (perpDistance < radius * 0.7f) {
            return true;
        }
    }
    
    return false;
}
