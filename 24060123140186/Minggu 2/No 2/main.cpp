#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // GL_LINE_STRIP
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0); // Merah
        glVertex2f(-0.9, 0.9);
        glVertex2f(-0.7, 0.8);
        glVertex2f(-0.5, 0.9);
        glVertex2f(-0.3, 0.8);
    glEnd();

    // GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0, 0.0, 0.0); // Hitam
        glVertex2f(0.3, 0.9);
        glVertex2f(0.5, 0.8);
        glVertex2f(0.7, 0.9);
        glVertex2f(0.5, 1.0);
    glEnd();

    // GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 0.0, 1.0); // Pink
        glVertex2f(0.0, 0.5); // Titik pusat
        glVertex2f(-0.2, 0.7);
        glVertex2f(0.0, 0.9);
        glVertex2f(0.2, 0.7);
    glEnd();

    // GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0, 1.0, 0.0); // Kuning
        glVertex2f(-0.9, 0.1);
        glVertex2f(-0.7, 0.3);
        glVertex2f(-0.5, 0.1);
        glVertex2f(-0.3, 0.3);
        glVertex2f(-0.1, 0.1);
    glEnd();

    // GL_QUADS
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.5, 0.0); // Oranye
        glVertex2f(-0.9, -0.1);
        glVertex2f(-0.5, -0.1);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.9, -0.5);
    glEnd();

    // GL_QUAD_STRIP
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.5, 0.0, 0.5); // Ungu
        glVertex2f(0.1, -0.1);
        glVertex2f(0.1, -0.5);
        glVertex2f(0.5, -0.1);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.9, -0.1);
        glVertex2f(0.9, -0.5);
    glEnd();

    glFlush();
}

void init() {
    // Atur background putih dan sistem koordinat 2D
    glClearColor(0.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Primitives Demo");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

