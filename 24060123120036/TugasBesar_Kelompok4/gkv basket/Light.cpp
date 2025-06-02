#include "Light.h"

void Light::setup(bool headlightMode) const {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    
    constexpr GLfloat ambientLight[] = {0.45f, 0.45f, 0.45f, 1.0f};
    constexpr GLfloat diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
    constexpr GLfloat specularLight[] = {0.8f, 0.8f, 0.8f, 1.0f};
    
    if (!headlightMode) {
        constexpr GLfloat lightPosition[] = {50.0f, 0.0f, 50.0f, 0.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    }
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
}

void Light::enableHeadlight() const {
    constexpr GLfloat lightPosition[] = {100.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}
