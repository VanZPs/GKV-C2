#include "live.h"
#include <math.h>

// Initialize the game environment
void initEnvironment() {
    setupEnvironmentLighting();
    glClearColor(ENV_BACKGROUND_R, ENV_BACKGROUND_G, ENV_BACKGROUND_B, 1.0f);
}

// Setup lighting for the environment
void setupEnvironmentLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    GLfloat lightPos[] = {ENV_LIGHT_POS_X, ENV_LIGHT_POS_Y, ENV_LIGHT_POS_Z, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    GLfloat lightAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
}

// Draw the environment boundaries (walls)
void drawEnvironmentBoundaries() {
    glColor3f(ENV_BOUNDARY_COLOR_R, ENV_BOUNDARY_COLOR_G, ENV_BOUNDARY_COLOR_B);
    glBegin(GL_LINES);
    
    // Left wall
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_BOTTOM, ENV_WALL_FRONT); 
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_TOP, ENV_WALL_FRONT);
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_BOTTOM, ENV_WALL_BACK); 
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_TOP, ENV_WALL_BACK);
    
    // Right wall
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_BOTTOM, ENV_WALL_FRONT); 
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_TOP, ENV_WALL_FRONT);
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_BOTTOM, ENV_WALL_BACK); 
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_TOP, ENV_WALL_BACK);
    
    // Back wall
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_BOTTOM, ENV_WALL_BACK); 
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_BOTTOM, ENV_WALL_BACK);
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_TOP, ENV_WALL_BACK); 
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_TOP, ENV_WALL_BACK);
    
    // Front wall (partial - no bottom for ball entry)
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_TOP, ENV_WALL_FRONT); 
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_TOP, ENV_WALL_FRONT);
    
    // Connecting lines between front and back
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_BOTTOM, ENV_WALL_FRONT); 
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_BOTTOM, ENV_WALL_BACK);
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_BOTTOM, ENV_WALL_FRONT); 
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_BOTTOM, ENV_WALL_BACK);
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_TOP, ENV_WALL_FRONT); 
    glVertex3f(ENV_WALL_LEFT, ENV_WALL_TOP, ENV_WALL_BACK);
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_TOP, ENV_WALL_FRONT); 
    glVertex3f(ENV_WALL_RIGHT, ENV_WALL_TOP, ENV_WALL_BACK);
    
    glEnd();
}

// Check if a point is within environment bounds
bool isWithinEnvironmentBounds(float x, float y, float z) {
    return (x >= ENV_WALL_LEFT && x <= ENV_WALL_RIGHT &&
            y >= ENV_WALL_BOTTOM && y <= ENV_WALL_TOP &&
            z >= ENV_WALL_FRONT && z <= ENV_WALL_BACK);
}

// Draw environment floor with grid pattern
void drawEnvironmentFloor() {
    glColor3f(0.2f, 0.2f, 0.3f);
    glBegin(GL_LINES);
    
    // Grid lines parallel to X-axis
    for (float z = ENV_WALL_FRONT; z <= ENV_WALL_BACK; z += 1.0f) {
        glVertex3f(ENV_WALL_LEFT, ENV_WALL_BOTTOM, z);
        glVertex3f(ENV_WALL_RIGHT, ENV_WALL_BOTTOM, z);
    }
    
    // Grid lines parallel to Z-axis
    for (float x = ENV_WALL_LEFT; x <= ENV_WALL_RIGHT; x += 1.0f) {
        glVertex3f(x, ENV_WALL_BOTTOM, ENV_WALL_FRONT);
        glVertex3f(x, ENV_WALL_BOTTOM, ENV_WALL_BACK);
    }
    
    glEnd();
}

// Placeholder for future particle effects
void drawEnvironmentParticles() {
    // This could be used for visual effects like:
    // - Sparks when blocks are destroyed
    // - Ambient floating particles
    // - Impact effects
    // Currently empty, ready for future enhancements
}