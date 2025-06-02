// airplane.cpp (Fixed) - Memperbaiki kontrol dan tampilan pesawat dengan warna baru

#include "airplane.h"

Airplane::Airplane() : pos(0, 0, 0), rotationY(0), speed(0.5f) {}

void Airplane::draw() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rotationY, 0, 1, 0);
    
    // Matikan pencahayaan untuk pesawat agar warna terlihat jelas
    glDisable(GL_LIGHTING);
    
    // Badan pesawat (Lilac)
    glColor3f(0.86, 0.80, 0.92); // Warna lilac pastel
    glPushMatrix();
    glScalef(1.0f, 0.5f, 2.0f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Sayap (Coral)
    glColor3f(0.98, 0.80, 0.76); // Warna coral pastel
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glScalef(3.0f, 0.1f, 1.0f);
	glutSolidCube(1.0);
	glPopMatrix();
    
    // Ekor (Salmon)
    glColor3f(0.99, 0.80, 0.78); // Warna salmon pastel
	glPushMatrix();
	glTranslatef(0.0f, 0.3f, -0.8f);
	glScalef(0.8f, 0.4f, 0.1f);
	glutSolidCube(1.0);
	glPopMatrix();
    
    // Baling-baling dengan animasi yang lebih halus
    glColor3f(1.0f, 1.0f, 1.0f);
    static float propRotation = 0.0f;
    propRotation += 15.0f; // Kecepatan rotasi ditambah
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.2f);
    glRotatef(propRotation, 0, 0, 1);
    glScalef(0.8f, 0.1f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.2f);
    glRotatef(propRotation + 90.0f, 0, 0, 1);
    glScalef(0.8f, 0.1f, 0.1f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Dua baling-baling tambahan untuk efek visual lebih baik
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.2f);
    glRotatef(propRotation + 45.0f, 0, 0, 1);
    glScalef(0.6f, 0.08f, 0.08f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.2f);
    glRotatef(propRotation + 135.0f, 0, 0, 1);
    glScalef(0.6f, 0.08f, 0.08f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Tambahkan kokpit untuk pesawat
    glColor3f(0.1f, 0.7f, 1.0f); // Warna biru muda untuk kaca
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.2f);
    glScalef(0.6f, 0.3f, 0.7f);
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();
    
    // Aktifkan kembali pencahayaan
    glEnable(GL_LIGHTING);
    
    glPopMatrix();
}

void Airplane::moveForward() {
    float radians = rotationY * 3.14159 / 180.0;
    pos.x -= sin(radians) * speed;
    pos.z -= cos(radians) * speed;
}

void Airplane::turnLeft() {
    rotationY += 2.0f;
}

void Airplane::turnRight() {
    rotationY -= 2.0f;
}

void Airplane::moveUp() {
    pos.y += speed * 0.5f;
}

void Airplane::moveDown() {
    pos.y -= speed * 0.5f;
    
    // Mencegah pesawat terbang di bawah tanah
    if (pos.y < 0.5f) {
        pos.y = 0.5f;
    }
}
