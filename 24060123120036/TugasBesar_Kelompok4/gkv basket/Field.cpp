#include "Field.h"
#include "TextureManager.h"

void Field::draw() const {
    glPushMatrix();
        drawSkybox();         // Gambar skybox 
        drawDistantScenery(); // Kemudian objek jauh
        drawClouds();
        drawScenery();        // Pohon dan semak
        drawExtendedGround(); // Gambar tanah yang diperluas
        drawLines(7.0f);      // Garis lapangan
        drawFloor();          // Lantai lapangan utama (sekarang tanpa tekstur)
    glPopMatrix();
}

void Field::drawFloor() const {
    glPushMatrix();
        setupMaterial();

        glTranslatef(10.0f, -40.0f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glScalef(2.5f, 2.5f, 0.1f);
        glutSolidCube(70.0);
        
    glPopMatrix();
}


void Field::setupMaterial() const {
    constexpr GLfloat fieldAmbient[] = {0.6f, 0.45f, 0.3f, 1.0f};
    constexpr GLfloat fieldDiffuse[] = {0.7f, 0.55f, 0.4f, 1.0f};
    constexpr GLfloat fieldSpecular[] = {0.1f, 0.1f, 0.1f, 1.0f};
    constexpr GLfloat shinessField = 16.0f;
   
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fieldAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fieldDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fieldSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinessField);
}


void Field::drawLines(float r) const {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    
        glColor3f(0.9f, 0.9f, 0.9f);
      
        glTranslatef(-20.0f, -36.0f, 0.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glScalef(3.0f, 0.0f, 3.0f);
        glBegin(GL_LINE_STRIP);
            for (float i = 0.0f; i <= PI + 0.01f; i += PI/100.0f) {
                glVertex3f(3.2f * r * cos(i), 0.0f, 3.2f * r * sin(i));
            }
        glEnd();
        glBegin(GL_LINES);
            glVertex3f(-3.2f * r, 0.0f, -(r + 5.0f));
            glVertex3f(-3.2f * r, 0.0f, 0.0f);
            glVertex3f(3.2f * r, 0.0f, -(r + 5.0f));
            glVertex3f(3.2f * r, 0.0f, 0.0f);
        glEnd();
        
        glBegin(GL_LINES);
            glVertex3f(-4.1f * r, 0.0f, -(r + 5.0f));
            glVertex3f(4.1f * r, 0.0f, -(r + 5.0f));
        glEnd();
        
        glBegin(GL_LINES);
            glVertex3f(-r, 0.0f, -(r + 5.0f));
            glVertex3f(-r, 0.0f, 5.0f);
            glVertex3f(r, 0.0f, -(r + 5.0f));
            glVertex3f(r, 0.0f, 5.0f);
        glEnd();
        
        glTranslatef(0.0f, 0.0f, 5.0f);
        
        glBegin(GL_LINE_LOOP);
            for (float i = 0.0f; i <= PI + 0.01f; i += PI/100.0f) {
                glVertex3f(r * cos(i), 0.0f, r * sin(i));
            }
        glEnd();
    
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

// Definisi untuk Field::drawTree()
void Field::drawTree(float x, float y, float z) const {
    glPushMatrix();
        glTranslatef(x, y, z);

        GLfloat trunkAmbient[] = {0.4f, 0.2f, 0.0f, 1.0f};
        GLfloat trunkDiffuse[] = {0.5f, 0.25f, 0.05f, 1.0f};
        GLfloat trunkSpecular[] = {0.05f, 0.05f, 0.05f, 1.0f}; // Kurangi specular batang
        GLfloat trunkShininess = 2.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, trunkAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, trunkDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, trunkSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, trunkShininess);

        glPushMatrix();
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            GLUquadric* trunkQuad = gluNewQuadric();
            if (trunkQuad) {
                gluCylinder(trunkQuad, 2.0, 1.5, 15.0, 8, 1); // Kurangi detail silinder
                gluDeleteQuadric(trunkQuad);
            }
        glPopMatrix();

        GLfloat foliageAmbient[] = {0.1f, 0.35f, 0.1f, 1.0f};
        GLfloat foliageDiffuse[] = {0.2f, 0.5f, 0.2f, 1.0f};
        GLfloat foliageSpecular[] = {0.1f, 0.15f, 0.1f, 1.0f};
        GLfloat foliageShininess = 8.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, foliageAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, foliageDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, foliageSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, foliageShininess);
        
        glTranslatef(0.0f, 15.0f, 0.0f); // Posisi daun relatif terhadap dasar batang
        glutSolidSphere(8.0, 12, 12); // Kurangi detail bola daun

    glPopMatrix();
}

// Definisi untuk Field::drawBush()
void Field::drawBush(float x, float y, float z) const {
    glPushMatrix();
        glTranslatef(x, y, z); // y adalah pusat semak

        GLfloat bushAmbient[] = {0.05f, 0.25f, 0.05f, 1.0f};
        GLfloat bushDiffuse[] = {0.1f, 0.4f, 0.1f, 1.0f};
        GLfloat bushSpecular[] = {0.02f, 0.05f, 0.02f, 1.0f};
        GLfloat bushShininess = 3.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, bushAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, bushDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, bushSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, bushShininess);

        glutSolidSphere(5.0, 10, 10); // Kurangi detail semak
    glPopMatrix();
}

// Definisi untuk Field::drawScenery()
void Field::drawScenery() const {
    float groundLevel = -40.0f;

    drawTree(-70.0f, groundLevel, -100.0f);
    drawTree(-40.0f, groundLevel, -105.0f);
    drawTree(0.0f,   groundLevel, -100.0f);
    drawTree(40.0f,  groundLevel, -105.0f);
    drawTree(80.0f,  groundLevel, -100.0f);

    drawTree(-90.0f, groundLevel, -50.0f);
    drawTree(-95.0f, groundLevel, 0.0f);
    drawTree(-90.0f, groundLevel, 50.0f);
    
    drawTree(110.0f, groundLevel, -50.0f);
    drawTree(115.0f, groundLevel, 0.0f);
    drawTree(110.0f, groundLevel, 50.0f);

    drawBush(-70.0f, groundLevel + 2.5f, 95.0f);
    drawBush(-60.0f, groundLevel + 2.5f, 98.0f);
    drawBush(80.0f,  groundLevel + 2.5f, 95.0f);
    drawBush(70.0f,  groundLevel + 2.5f, 98.0f);
}

// Definisi untuk Field::drawCloud()
void Field::drawCloud(float x, float y, float z, float scale) const {
    glPushMatrix();
        glTranslatef(x, y, z);
        glScalef(scale, scale, scale);

        GLfloat cloudAmbient[] = {0.85f, 0.85f, 0.9f, 1.0f};
        GLfloat cloudDiffuse[] = {0.95f, 0.95f, 1.0f, 1.0f};
        GLfloat cloudSpecular[] = {0.05f, 0.05f, 0.1f, 1.0f};
        GLfloat cloudShininess = 2.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, cloudAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, cloudDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, cloudSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, cloudShininess);

        glutSolidSphere(10.0, 8, 8);
        
        glPushMatrix();
            glTranslatef(7.0f, 1.5f, 0.5f);
            glutSolidSphere(8.0, 6, 6);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-6.0f, 1.0f, -1.0f);
            glutSolidSphere(9.0, 7, 7);
        glPopMatrix();

    glPopMatrix();
}

// Definisi untuk Field::drawClouds()
void Field::drawClouds() const {
    drawCloud(-160.0f, 75.0f, -260.0f, 2.2f);
    drawCloud(60.0f, 85.0f, -310.0f, 2.6f);
    drawCloud(220.0f, 70.0f, -210.0f, 1.9f);
    drawCloud(-90.0f, 90.0f, 220.0f, 2.3f);
    drawCloud(160.0f, 90.0f, 160.0f, 2.1f);
    drawCloud(-270.0f, 65.0f, 60.0f, 2.4f);
    drawCloud(10.0f, 105.0f, 290.0f, 2.0f);
}

// Definisi untuk Field::drawExtendedGround()
void Field::drawExtendedGround() const {
    glPushMatrix();
        GLfloat groundAmbient[] = {0.15f, 0.35f, 0.1f, 1.0f};
        GLfloat groundDiffuse[] = {0.25f, 0.45f, 0.15f, 1.0f};
        GLfloat groundSpecular[] = {0.01f, 0.01f, 0.01f, 1.0f};
        GLfloat groundShininess = 1.0f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, groundAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, groundDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, groundSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, groundShininess);
        
        glTranslatef(0.0f, -40.5f, 0.0f);
        glBegin(GL_QUADS);
            glNormal3f(0.0f, 1.0f, 0.0f);
            glVertex3f(-500.0f, 0.0f, -500.0f);
            glVertex3f( 500.0f, 0.0f, -500.0f);
            glVertex3f( 500.0f, 0.0f,  500.0f);
            glVertex3f(-500.0f, 0.0f,  500.0f);
        glEnd();
    glPopMatrix();
}

// Definisi untuk Field::drawDistantScenery()
void Field::drawDistantScenery() const {
    glPushMatrix();
    // Pegunungan
    GLfloat mountainAmbient[] = {0.35f, 0.33f, 0.30f, 1.0f};
    GLfloat mountainDiffuse[] = {0.45f, 0.43f, 0.40f, 1.0f};
    GLfloat mountainSpecular[] = {0.02f, 0.02f, 0.02f, 1.0f};
    GLfloat mountainShininess = 1.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, mountainAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mountainDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mountainSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, mountainShininess);

    float mountainBaseY = -40.0f;
    
    glPushMatrix();
        glTranslatef(120.0f, mountainBaseY, -480.0f);
        glScalef(90.0f, 220.0f, 90.0f);
        glutSolidCone(1.0, 1.0, 8, 2);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-70.0f, mountainBaseY, -500.0f);
        glScalef(110.0f, 270.0f, 110.0f);
        glutSolidCone(1.0, 1.0, 8, 2);
    glPopMatrix();
     
    glPushMatrix();
        glTranslatef(270.0f, mountainBaseY, -430.0f);
        glScalef(130.0f, 190.0f, 130.0f);
        glutSolidCone(1.0, 1.0, 8, 2);
    glPopMatrix();

    glPopMatrix();
}

// Definisi untuk Field::drawSkybox()
void Field::drawSkybox() const {
    glPushMatrix();
    glPushAttrib(GL_ENABLE_BIT | GL_TEXTURE_BIT | GL_LIGHTING_BIT | GL_DEPTH_BUFFER_BIT | GL_POLYGON_BIT | GL_FOG_BIT);

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glColor3f(0.678f, 0.847f, 0.902f);
    glDepthMask(GL_FALSE);
    glDisable(GL_FOG);    
    float s = 580.0f;
    // Depan (Z negatif)
    glBindTexture(GL_TEXTURE_2D, TextureManager::tex_sky_front);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-s, -s, -s); // Disesuaikan UV agar gambar tidak terbalik
        glTexCoord2f(1.0f, 0.0f); glVertex3f( s, -s, -s);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( s,  s, -s);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-s,  s, -s);
    glEnd();
    // Belakang (Z positif)
    glBindTexture(GL_TEXTURE_2D, TextureManager::tex_sky_back);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( s, -s,  s);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-s, -s,  s);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-s,  s,  s);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( s,  s,  s);
    glEnd();
    // Kiri (X negatif)
    glBindTexture(GL_TEXTURE_2D, TextureManager::tex_sky_left);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-s, -s,  s);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-s, -s, -s);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-s,  s, -s);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-s,  s,  s);
    glEnd();
    // Kanan (X positif)
    glBindTexture(GL_TEXTURE_2D, TextureManager::tex_sky_right);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( s, -s, -s);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( s, -s,  s);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( s,  s,  s);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( s,  s, -s);
    glEnd();
    // Atas (Y positif)
    glBindTexture(GL_TEXTURE_2D, TextureManager::tex_sky_up);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-s,  s, -s);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( s,  s, -s); // UVs disesuaikan agar langit atas benar
        glTexCoord2f(1.0f, 0.0f); glVertex3f( s,  s,  s);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-s,  s,  s);
    glEnd();
    // Bawah (Y negatif)
    glBindTexture(GL_TEXTURE_2D, TextureManager::tex_sky_down);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-s, -s, -s);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-s, -s,  s); // UVs disesuaikan
        glTexCoord2f(1.0f, 1.0f); glVertex3f( s, -s,  s);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( s, -s, -s);
    glEnd();

    glDepthMask(GL_TRUE);
    glPopAttrib();
    glPopMatrix();
}
