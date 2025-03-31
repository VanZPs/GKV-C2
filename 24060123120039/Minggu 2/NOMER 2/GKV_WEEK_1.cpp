#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // GL_LINE_STRIP
    glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.8, 0.8);
        glVertex2f(-0.6, 0.6);
        glVertex2f(-0.4, 0.8);
        glVertex2f(-0.2, 0.6);
    glEnd();

    // GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-0.8, 0.4);
        glVertex2f(-0.6, 0.2);
        glVertex2f(-0.4, 0.4);
        glVertex2f(-0.2, 0.2);
    glEnd();

    // GL_TRIANGLE_FAN
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(0.0, 0.5);
        glVertex2f(0.2, 0.7);
        glVertex2f(0.4, 0.6);
        glVertex2f(0.3, 0.4);
        glVertex2f(0.1, 0.3);
    glEnd();

    // GL_TRIANGLE_STRIP
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(0.0, -0.2);
        glVertex2f(0.2, 0.0);
        glVertex2f(0.4, -0.2);
        glVertex2f(0.6, 0.0);
    glEnd();

    // GL_QUADS
    glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 1.0);
        glVertex2f(-0.8, -0.6);
        glVertex2f(-0.6, -0.6);
        glVertex2f(-0.6, -0.8);
        glVertex2f(-0.8, -0.8);
    glEnd();

    // GL_QUAD_STRIP
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.0, 1.0, 1.0);
        glVertex2f(-0.2, -0.8);
        glVertex2f(0.0, -0.6);
        glVertex2f(0.2, -0.8);
        glVertex2f(0.4, -0.6);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Shapes");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

