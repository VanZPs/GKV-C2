#include "Hoop.h"

void Hoop::draw() const {
    glPushMatrix();
    
    //hoop position
    glTranslatef(-50.0f, -10.0f, 0.0f);
    
    // Ring
    glPushMatrix();
        setupMaterial("ring");
        
        glTranslatef(6.0f, 20.0f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glutSolidTorus(0.5, 5.0, 10, 10);
    glPopMatrix();

    // Backboard
    glPushMatrix();
        setupMaterial("table");
    
        glTranslatef(0.0f, 24.0f, 0.0f);
        glScalef(2.0f, 19.0f, 19.0f);
        glutSolidCube(1.0);
    glPopMatrix();
    
    // Support bar 1
    glPushMatrix();
        setupMaterial("bars");
        
        glTranslatef(-10.0f, 0.0f, 6.0f);
        glScalef(1.0f, 48.0f, 4.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Support bar 2
    glPushMatrix();
        setupMaterial("bars");
        
        glTranslatef(-10.0f, 0.0f, -6.0f);
        glScalef(1.0f, 48.0f, 4.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Horizontal support bar 1
    glPushMatrix();
        setupMaterial("bars");
        
        glTranslatef(-5.0f, 24.0f, 6.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glScalef(1.0f, 10.0f, 4.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    // Horizontal support bar 2
    glPushMatrix();
        setupMaterial("bars");
     
        glTranslatef(-5.0f, 24.0f, -6.0f);
        glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
        glScalef(1.0f, 10.0f, 4.0f);
        glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}

void Hoop::setupMaterial(const std::string& partName) const {
    constexpr GLfloat tableAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
    constexpr GLfloat tableDiffuse[] = {0.9f, 0.9f, 0.9f, 1.0f};
    constexpr GLfloat tableSpecular[] = {0.8f, 0.8f, 0.8f, 1.0f};
    constexpr GLfloat shinessTable = 40.0f;
   
    constexpr GLfloat hoopAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    constexpr GLfloat hoopDiffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
    constexpr GLfloat hoopSpecular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    constexpr GLfloat shinessHoop = 20.0f;
    
    if (partName == "table") {
        glMaterialfv(GL_FRONT, GL_AMBIENT, tableAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tableDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tableSpecular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinessTable);
    } else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, hoopAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, hoopDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, hoopSpecular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinessHoop);
    }
}
