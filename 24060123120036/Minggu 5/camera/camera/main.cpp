//
//  main.cpp
//  camera
//
//  Created by aris on 01/04/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>

double cameraX = 0.0, cameraY = 0.0, cameraZ = 5.0; // Camera position
double rotAngleY = 0.0, rotAngleX = 0.0; // Rotation angles

void init()
{
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, cameraX, cameraY, cameraZ - 1, 0.0, 1.0, 0.0);
    
    glPushMatrix();
    glRotated(rotAngleY, 0, 1, 0);
    glRotated(rotAngleX, 1, 0, 0);

    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.1, 0.5, 1.0); // Changed teapot color to blueish
    glutSolidTeapot(1);
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
}

void keyboard(unsigned char k, int x, int y)
{
    switch (k)
    {
    case 'u':
        cameraZ -= 0.3; // Changed movement step
        break;
    case 'j':
        cameraZ += 0.3;
        break;
    case 'h':
        cameraX -= 0.3;
        break;
    case 'k':
        cameraX += 0.3;
        break;
    case 'o':
        cameraY += 0.3;
        break;
    case 'p':
        cameraY -= 0.3;
        break;
    case 'f':
        rotAngleY -= 10; // Increased rotation angle step
        break;
    case 'g':
        rotAngleY += 10;
        break;
    case 't':
        rotAngleX -= 10;
        break;
    case 'v':
        rotAngleX += 10;
        break;
    case 27: // Escape key
        exit(0);
    }
    glutPostRedisplay();
}

int main()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("Camera Movement");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}
