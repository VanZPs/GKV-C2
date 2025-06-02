// building.cpp - Implementasi kelas bangunan dengan bayangan natural

#include "building.h"

Building::Building(const Position& _pos, float _w, float _h, float _d, const Color& _color)
    : pos(_pos), width(_w), height(_h), depth(_d), color(_color) {}

void Building::draw() {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    
    glColor3f(color.r, color.g, color.b);
    
    glPushMatrix();
    glScalef(width, height, depth);
    glutSolidCube(1.0);
    glPopMatrix();
    
    // Jendela
    glColor3f(0.0f, 0.0f, 0.0f);
    float windowSize = 0.2f;
    float windowSpacing = 0.4f;
    
    // Jendela depan
    for (float y = -height/2 + windowSize; y < height/2; y += windowSpacing) {
        for (float x = -width/2 + windowSize; x < width/2; x += windowSpacing) {
            glPushMatrix();
            glTranslatef(x, y, depth/2 + 0.01f);
            glScalef(windowSize, windowSize, 0.01f);
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
    
    // Jendela belakang
    for (float y = -height/2 + windowSize; y < height/2; y += windowSpacing) {
        for (float x = -width/2 + windowSize; x < width/2; x += windowSpacing) {
            glPushMatrix();
            glTranslatef(x, y, -depth/2 - 0.01f);
            glScalef(windowSize, windowSize, 0.01f);
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
    
    glPopMatrix();
}

void Building::drawShadow() {
    // Matikan pencahayaan untuk bayangan
    glDisable(GL_LIGHTING);
    
    glPushMatrix();
    
    // Parameter proyeksi bayangan yang natural
    float shadowLength = height * 1.5f;  // Panjang bayangan
    float lightAngle = 60.0f * 3.14159f / 180.0f; // Sudut cahaya (60 derajat dari horizontal)
    float lightDirection = 225.0f * 3.14159f / 180.0f; // Arah cahaya (dari barat daya)
    
    // Hitung offset bayangan berdasarkan sudut dan arah cahaya
    float shadowOffsetX = shadowLength * cos(lightDirection) * cos(lightAngle);
    float shadowOffsetZ = shadowLength * sin(lightDirection) * cos(lightAngle);
    
    // Aktifkan blending untuk transparansi
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Nonaktifkan depth writing untuk bayangan
    glDepthMask(GL_FALSE);
    
    // Posisi dasar bayangan (tepat di tanah)
    float groundY = 0.005f;
    
    // Titik-titik dasar gedung
    float baseX1 = pos.x - width/2;
    float baseX2 = pos.x + width/2;
    float baseZ1 = pos.z - depth/2;
    float baseZ2 = pos.z + depth/2;
    
    // Titik-titik proyeksi bayangan (lebih pendek untuk natural look)
    float shadowScale = 0.3f; // Bayangan mengecil di ujung
    float shadowCenterX = pos.x + shadowOffsetX;
    float shadowCenterZ = pos.z + shadowOffsetZ;
    float shadowW = width * shadowScale;
    float shadowD = depth * shadowScale;
    
    float shadowX1 = shadowCenterX - shadowW/2;
    float shadowX2 = shadowCenterX + shadowW/2;
    float shadowZ1 = shadowCenterZ - shadowD/2;
    float shadowZ2 = shadowCenterZ + shadowD/2;
    
    // Gambar bayangan sebagai satu bentuk polygon yang menyatu
    glBegin(GL_TRIANGLES);
    
    // Warna bayangan dengan gradasi
    float shadowAlpha = 0.4f;
    float shadowAlphaFade = 0.1f;
    
    // Bagian bayangan yang dekat dengan gedung (lebih gelap)
    glColor4f(0.1f, 0.1f, 0.2f, shadowAlpha);
    
    // Segitiga 1: depan-kiri ke belakang-kiri ke tengah bayangan
    glVertex3f(baseX1, groundY, baseZ2);      // depan-kiri gedung
    glVertex3f(baseX1, groundY, baseZ1);      // belakang-kiri gedung
    glColor4f(0.2f, 0.2f, 0.3f, shadowAlphaFade);
    glVertex3f(shadowCenterX, groundY, shadowCenterZ); // tengah bayangan (fade)
    
    // Segitiga 2: belakang-kiri ke belakang-kanan ke tengah bayangan
    glColor4f(0.1f, 0.1f, 0.2f, shadowAlpha);
    glVertex3f(baseX1, groundY, baseZ1);      // belakang-kiri gedung
    glVertex3f(baseX2, groundY, baseZ1);      // belakang-kanan gedung
    glColor4f(0.2f, 0.2f, 0.3f, shadowAlphaFade);
    glVertex3f(shadowCenterX, groundY, shadowCenterZ); // tengah bayangan (fade)
    
    // Segitiga 3: belakang-kanan ke depan-kanan ke tengah bayangan
    glColor4f(0.1f, 0.1f, 0.2f, shadowAlpha);
    glVertex3f(baseX2, groundY, baseZ1);      // belakang-kanan gedung
    glVertex3f(baseX2, groundY, baseZ2);      // depan-kanan gedung
    glColor4f(0.2f, 0.2f, 0.3f, shadowAlphaFade);
    glVertex3f(shadowCenterX, groundY, shadowCenterZ); // tengah bayangan (fade)
    
    // Segitiga 4: depan-kanan ke depan-kiri ke tengah bayangan
    glColor4f(0.1f, 0.1f, 0.2f, shadowAlpha);
    glVertex3f(baseX2, groundY, baseZ2);      // depan-kanan gedung
    glVertex3f(baseX1, groundY, baseZ2);      // depan-kiri gedung
    glColor4f(0.2f, 0.2f, 0.3f, shadowAlphaFade);
    glVertex3f(shadowCenterX, groundY, shadowCenterZ); // tengah bayangan (fade)
    
    glEnd();
    
    // Tambahan: bayangan halus di sekitar ujung untuk efek blur
    glBegin(GL_TRIANGLE_FAN);
    
    // Pusat dengan transparansi rendah
    glColor4f(0.3f, 0.3f, 0.4f, shadowAlphaFade * 0.5f);
    glVertex3f(shadowCenterX, groundY, shadowCenterZ);
    
    // Lingkaran di sekitar ujung bayangan untuk efek soft edge
    int segments = 8;
    float blurRadius = (shadowW + shadowD) * 0.25f;
    
    for (int i = 0; i <= segments; i++) {
        float angle = i * 2.0f * 3.14159f / segments;
        float x = shadowCenterX + blurRadius * cos(angle);
        float z = shadowCenterZ + blurRadius * sin(angle);
        
        glColor4f(0.4f, 0.4f, 0.5f, 0.05f); // Hampir transparan
        glVertex3f(x, groundY, z);
    }
    
    glEnd();
    
    // Aktifkan kembali depth writing
    glDepthMask(GL_TRUE);
    
    // Matikan blending
    glDisable(GL_BLEND);
    
    glPopMatrix();
    
    // Aktifkan kembali pencahayaan
    glEnable(GL_LIGHTING);
}
