#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>

double rotAngle = 10;
double rotAngle1 = 10;

void init() {
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotated(rotAngle, 0, 1, 0);
    glRotated(rotAngle1, 1, 0, 0);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0, 0.1, 0.1);
    glutSolidTeapot(1);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            rotAngle += 10;
            break;
        case 's':
            rotAngle -= 10;
            break;
        case 'd':
            rotAngle1 += 10;
            break;
        case 'a':
            rotAngle1 -= 10;
            break;
        case 'q':
            exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("FreeGLUT Example");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

