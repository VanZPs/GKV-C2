#include <GL/freeglut.h>   

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // GL_LINE_STRIP
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.8, 0.8);
        glVertex2f(-0.6, 0.6);
        glVertex2f(-0.4, 0.8);
    glEnd();

    // GL_LINE_LOOP
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.2, 0.8);
        glVertex2f(0.0, 0.6);
        glVertex2f(0.2, 0.8);
        glVertex2f(0.0, 1.0);
    glEnd();

    // GL_TRIANGLE_FAN
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-0.8, 0.2);
        glVertex2f(-0.6, 0.4);
        glVertex2f(-0.4, 0.2);
        glVertex2f(-0.6, 0.0);
    glEnd();

    // GL_TRIANGLE_STRIP
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-0.2, 0.2);
        glVertex2f(0.0, 0.4);
        glVertex2f(0.2, 0.2);
        glVertex2f(0.4, 0.4);
    glEnd();

    // GL_QUADS
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
        glVertex2f(-0.8, -0.4);
        glVertex2f(-0.4, -0.4);
        glVertex2f(-0.4, -0.8);
        glVertex2f(-0.8, -0.8);
    glEnd();

    // GL_QUAD_STRIP
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_QUAD_STRIP);
        glVertex2f(0.0, -0.4);
        glVertex2f(0.2, -0.6);
        glVertex2f(0.4, -0.4);
        glVertex2f(0.6, -0.6);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100); // Posisi awal jendela
    glutCreateWindow("OpenGL Shapes");

    init();  // Panggil init() untuk mengatur koordinat
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

