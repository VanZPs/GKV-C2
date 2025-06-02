//
//  main.cpp
//  UpdateKodeLengan
//
//  Created by aris on 20/03/25.
//

#include <GLUT/glut.h>
#include <cstdlib>

static int shoulder = 0, elbow = 0, wrist = 0;
static int fingers[5] = {0, 0, 0, 0, 0};

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawFinger(float xOffset, int angle) {
    glPushMatrix();
    glTranslatef(xOffset, 0.2, 0.0);
    glRotatef((GLfloat)angle, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.6, 0.2, 0.2);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    // Bahu
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Siku
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat) elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Pergelangan tangan
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat) wrist, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.0, 0.4, 0.8);
    glutWireCube(1.0);
    glPopMatrix();

    // Telapak tangan
    glTranslatef(0.5, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.0, 0.3, 0.6);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Jari-jari
    drawFinger(-0.3, fingers[0]);  // Jempol
    drawFinger(-0.1, fingers[1]);  // Telunjuk
    drawFinger(0.1, fingers[2]);   // Jari tengah
    drawFinger(0.3, fingers[3]);   // Jari manis
    drawFinger(0.5, fingers[4]);   // Kelingking

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;
        case '1': fingers[0] = (fingers[0] + 5) % 90; break;
        case '!': fingers[0] = (fingers[0] - 5) % 90; break;
        case '2': fingers[1] = (fingers[1] + 5) % 90; break;
        case '@': fingers[1] = (fingers[1] - 5) % 90; break;
        case '3': fingers[2] = (fingers[2] + 5) % 90; break;
        case '#': fingers[2] = (fingers[2] - 5) % 90; break;
        case '4': fingers[3] = (fingers[3] + 5) % 90; break;
        case '$': fingers[3] = (fingers[3] - 5) % 90; break;
        case '5': fingers[4] = (fingers[4] + 5) % 90; break;
        case '%': fingers[4] = (fingers[4] - 5) % 90; break;
        case 27: exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robot Arm with Hand and Fingers");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
