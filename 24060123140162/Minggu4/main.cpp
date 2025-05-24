
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

static int shoulder = 0, elbow = 0, wrist = 0;
static int thumb = 0, indexFinger = 0, middleFinger = 0, ringFinger = 0, pinkyFinger = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-1.3, 0.0, 0.0);
    
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(0.8, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, -0.25, 0.4);
    glRotatef(-30.0 + (GLfloat)thumb, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    glScalef(0.6, 0.08, 0.08);
    glutWireCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.4, 0.1, 0.25);
    glRotatef((GLfloat)indexFinger, 0.0, 0.0, 1.0);
    glTranslatef(0.35, 0.0, 0.0);
    glScalef(0.7, 0.08, 0.08);
    glutWireCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.4, 0.1, 0.0);
    glRotatef((GLfloat)middleFinger, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glScalef(0.8, 0.08, 0.08);
    glutWireCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.4, 0.1, -0.25);
    glRotatef((GLfloat)ringFinger, 0.0, 0.0, 1.0);
    glTranslatef(0.35, 0.0, 0.0);
    glScalef(0.7, 0.08, 0.08);
    glutWireCube(1.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.4, 0.1, -0.45);
    glRotatef((GLfloat)pinkyFinger, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glScalef(0.5, 0.07, 0.07);
    glutWireCube(1.0);
    glPopMatrix();
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();
            break;
        case 'S':
            shoulder = (shoulder - 5) % 360;
            glutPostRedisplay();
            break;
            
        case 'e':
            elbow = (elbow + 5) % 360;
            glutPostRedisplay();
            break;
        case 'E':
            elbow = (elbow - 5) % 360;
            glutPostRedisplay();
            break;
            
        case 'w':
            wrist = (wrist + 5) % 360;
            glutPostRedisplay();
            break;
        case 'W':
            wrist = (wrist - 5) % 360;
            glutPostRedisplay();
            break;
        
        case '1':
            thumb = (thumb + 5) % 90;
            glutPostRedisplay();
            break;
        case '!':
            thumb = (thumb - 5) % 90;
            if (thumb < 0) thumb += 90;
            glutPostRedisplay();
            break;
            
            
        case '2':
            indexFinger = (indexFinger + 5) % 90;
            glutPostRedisplay();
            break;
        case '@':
            indexFinger = (indexFinger - 5) % 90;
            if (indexFinger < 0) indexFinger += 90;
            glutPostRedisplay();
            break;
            
        case '3':
            middleFinger = (middleFinger + 5) % 90;
            glutPostRedisplay();
            break;
        case '#':
            middleFinger = (middleFinger - 5) % 90;
            if (middleFinger < 0) middleFinger += 90;
            glutPostRedisplay();
            break;
            
        case '4':
            ringFinger = (ringFinger + 5) % 90;
            glutPostRedisplay();
            break;
        case '$':
            ringFinger = (ringFinger - 5) % 90;
            if (ringFinger < 0) ringFinger += 90;
            glutPostRedisplay();
            break;
            
        case '5':
            pinkyFinger = (pinkyFinger + 5) % 90;
            glutPostRedisplay();
            break;
        case '%':
            pinkyFinger = (pinkyFinger - 5) % 90;
            if (pinkyFinger < 0) pinkyFinger += 90;
            glutPostRedisplay();
            break;
            
        case 'f':
            thumb = indexFinger = middleFinger = ringFinger = pinkyFinger = (thumb + 5) % 90;
            glutPostRedisplay();
            break;
        case 'F':
            thumb = indexFinger = middleFinger = ringFinger = pinkyFinger = (thumb - 5) % 90;
            if (thumb < 0) {
                thumb = indexFinger = middleFinger = ringFinger = pinkyFinger += 90;
            }
            glutPostRedisplay();
            break;
            
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
