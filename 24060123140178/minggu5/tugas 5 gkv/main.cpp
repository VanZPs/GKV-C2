#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double rotAngle = 10; 
double rotAngle1 = 10; 
double angleStep = 10; 

void init() {
    glClearColor(0, 0, 0, 0); 
    glClearDepth(1.0); 
    glEnable(GL_DEPTH_TEST); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 
              0.0, 0.0, 0.0, 
              0.0, 1.0, 0.0); 
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

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: rotAngle -= angleStep; break; 
        case GLUT_KEY_RIGHT: rotAngle += angleStep; break; 
        case GLUT_KEY_UP: rotAngle1 += angleStep; break; 
        case GLUT_KEY_DOWN: rotAngle1 -= angleStep; break; 
        case GLUT_KEY_F1: exit(0);
    }
    glutPostRedisplay(); 
}

int main(int argc, char **argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("GLUT Example");

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys); 
    init(); 
    glutMainLoop(); 
    return 0;
}

