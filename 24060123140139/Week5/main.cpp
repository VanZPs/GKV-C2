#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double rotAngle = 0; 
double rotAngle1 = 0; 

void init() {
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
	0.0, 0.0, 5.0,
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

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': 
            rotAngle1 += 20; 
            break;
        case 's':
            rotAngle1 -= 20; 
            break;
        case 'd': 
            rotAngle += 20; 
            break;
        case 'a': 
            rotAngle -= 20; 
            break;
        case 'q':
            exit(0);
    }
    glutPostRedisplay();
}

int main() {
    glutInitDisplayMode(
		GLUT_DOUBLE | 
		GLUT_DEPTH | 
		GLUT_RGB);
    glutCreateWindow("GLUT Example");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}

