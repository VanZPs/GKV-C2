#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Warna Biru untuk Kubus
    glColor3f(0.3f, 0.5f, 0.8f);
    glBegin(GL_QUADS);

    // Lapisan bawah (4 kubus)
    glVertex2f(-0.8, -0.4); glVertex2f(-0.6, -0.4);
    glVertex2f(-0.6, -0.2); glVertex2f(-0.8, -0.2);

    glVertex2f(-0.4, -0.4); glVertex2f(-0.2, -0.4);
    glVertex2f(-0.2, -0.2); glVertex2f(-0.4, -0.2);

    glVertex2f(0.0, -0.4); glVertex2f(0.2, -0.4);
    glVertex2f(0.2, -0.2); glVertex2f(0.0, -0.2);

    glVertex2f(0.4, -0.4); glVertex2f(0.6, -0.4);
    glVertex2f(0.6, -0.2); glVertex2f(0.4, -0.2);

    // Lapisan tengah (3 kubus)
    glColor3f(0.2f, 0.6f, 0.9f);
    glVertex2f(-0.6, -0.1); glVertex2f(-0.4, -0.1);
    glVertex2f(-0.4, 0.1); glVertex2f(-0.6, 0.1);

    glVertex2f(-0.2, -0.1); glVertex2f(0.0, -0.1);
    glVertex2f(0.0, 0.1); glVertex2f(-0.2, 0.1);

    glVertex2f(0.2, -0.1); glVertex2f(0.4, -0.1);
    glVertex2f(0.4, 0.1); glVertex2f(0.2, 0.1);

    // Lapisan atas (2 kubus)
    glColor3f(0.1f, 0.4f, 0.7f);
    glVertex2f(-0.4, 0.2); glVertex2f(-0.2, 0.2);
    glVertex2f(-0.2, 0.4); glVertex2f(-0.4, 0.4);

    glVertex2f(0.0, 0.2); glVertex2f(0.2, 0.2);
    glVertex2f(0.2, 0.4); glVertex2f(0.0, 0.4);

    glEnd();

    // Bayangan (Efek 3D sederhana)
    glColor3f(0.1f, 0.1f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-0.8, -0.42); glVertex2f(0.6, -0.42);
    glVertex2f(0.6, -0.4); glVertex2f(-0.8, -0.4);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Kubus Bertingkat Kreatif");

    glClearColor(0.1, 0.1, 0.3, 1.0); // Background Biru Gelap
    gluOrtho2D(-1, 1, -1, 1);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

