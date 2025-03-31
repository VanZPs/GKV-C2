// Nama	:	Ivan Pratomo Soelistio
// NIM	:	24060123120011

#include <stdlib.h>  
#include <stdio.h>   
#include <math.h>    
#include <GL/glut.h> 

double rotAngle = 10;
double rotAngle1 = 10;

void init() {
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);

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

// Modifikasi tombol untuk nggerakin kameranya pake panah dan juga mengubah sudut gesernya menjadi 10
void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        rotAngle -= 10;
        break;
    case GLUT_KEY_RIGHT:
        rotAngle += 10;
        break;
    case GLUT_KEY_UP:
        rotAngle1 += 10;
        break;
    case GLUT_KEY_DOWN:
        rotAngle1 -= 10;
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'q') {
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("GLUT Example - Teapot Rotation");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    init();
    glutMainLoop();
    return 0;
}

