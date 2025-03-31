#include <GL/glut.h>
#include <cmath>

void lingkaran(int xc, int yc, int r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(xc, yc);
    int segments = 100; 
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159265f * i / segments;
        glVertex2i(xc + r * cos(angle), yc + r * sin(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.5, 0.8);
    glPushMatrix();
    glTranslatef(50.0f, -50.0f, 0.0f); 
    lingkaran(200, 200, 100);
    glPopMatrix();
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lingkaran");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

