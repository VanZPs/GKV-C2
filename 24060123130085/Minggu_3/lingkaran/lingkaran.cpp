#include <GL/glut.h>
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 0.0f);
    float radius = 0.5f;
    int num_segments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); 
    for (int i = 0; i <= num_segments; i++) {
        float angle = 2.0f * M_PI * i / num_segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Filled Circle with OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}