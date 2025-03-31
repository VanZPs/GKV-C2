#include <GL/freeglut.h>

void myInit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.0, 0.5);
        glVertex2f(0.5, 0.5);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Titik & Garis OpenGL");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

