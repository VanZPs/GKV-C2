#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <cmath>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PI = 3.14159265358979323846f;

void drawCircle(float centerX, float centerY, float radius, int numSegments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        
        float theta = 2.0f * PI * float(i) / float(numSegments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(0.0f, 0.0f, 0.5f, 100);
    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width <= height) {
        gluOrtho2D(-1.0, 1.0, -1.0 * height / width, 1.0 * height / width);
    } else {
        gluOrtho2D(-1.0 * width / height, 1.0 * width / height, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Circle");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    
    return 0;
}

