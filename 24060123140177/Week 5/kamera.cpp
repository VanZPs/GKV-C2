#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double rotAngle = 15;
double rotAngle1 = 15;

void init()
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    glRotated(rotAngle, 1, 0, 0);
    glRotated(rotAngle1, 0, 1, 0);

    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0, 0.1, 0.1);
    glutSolidTeapot(1);

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        rotAngle += 15;
        break;
    case GLUT_KEY_DOWN:
        rotAngle -= 15;
        break;
    case GLUT_KEY_LEFT:
        rotAngle1 -= 15;
        break;
    case GLUT_KEY_RIGHT:
        rotAngle1 += 15;
        break;
    case GLUT_KEY_F1:
        exit(0);
    }
    glutPostRedisplay();
}

int main()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("GLUT Example");
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    init();
    glutMainLoop();
    return 0;
}
