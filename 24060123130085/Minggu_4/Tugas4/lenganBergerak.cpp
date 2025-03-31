#include <GL/glut.h>

// Rotasi untuk setiap bagian tangan pada sumbu X, Y, dan Z
GLfloat shoulderX = 0.0, shoulderY = 0.0, shoulderZ = 0.0;
GLfloat elbowX = 0.0, elbowY = 0.0, elbowZ = 0.0;
GLfloat palmX = 0.0, palmY = 0.0, palmZ = 0.0;
GLfloat fingerAngle[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0, 0.0, -5.0);
    
    // Shoulder
    glPushMatrix();
    glRotatef(shoulderX, 1.0, 0.0, 0.0);
    glRotatef(shoulderY, 0.0, 1.0, 0.0);
    glRotatef(shoulderZ, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    glutWireCube(1.0);
    
    // Elbow
    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(elbowX, 1.0, 0.0, 0.0);
    glRotatef(elbowY, 0.0, 1.0, 0.0);
    glRotatef(elbowZ, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    glutWireCube(1.0);
    
    // Palm
    glTranslatef(0.5, 0.0, 0.0);
    glRotatef(palmX, 1.0, 0.0, 0.0);
    glRotatef(palmY, 0.0, 1.0, 0.0);
    glRotatef(palmZ, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    glutWireCube(0.6);
    
    // Fingers
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(0.3, 0.2 - (i * 0.1), 0.0);
        glRotatef(fingerAngle[i], 0.0, 0.0, 1.0);
        glTranslatef(0.2, 0.0, 0.0);
        glutWireCube(0.4);
        glPopMatrix();
    }
    
    glPopMatrix();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q': shoulderX += 5; break;
        case 'Q': shoulderX -= 5; break;
        case 'w': shoulderY += 5; break;
        case 'W': shoulderY -= 5; break;
        case 'e': shoulderZ += 5; break;
        case 'E': shoulderZ -= 5; break;
        
        case 'a': elbowX += 5; break;
        case 'A': elbowX -= 5; break;
        case 's': elbowY += 5; break;
        case 'S': elbowY -= 5; break;
        case 'd': elbowZ += 5; break;
        case 'D': elbowZ -= 5; break;
        
        case 'z': palmX += 5; break;
        case 'Z': palmX -= 5; break;
        case 'x': palmY += 5; break;
        case 'X': palmY -= 5; break;
        case 'c': palmZ += 5; break;
        case 'C': palmZ -= 5; break;
        
        case '1': fingerAngle[0] += 5; break;
        case '!': fingerAngle[1] += 5; break;
        case '2': fingerAngle[2] += 5; break;
        case '@': fingerAngle[3] += 5; break;
        case '3': fingerAngle[4] += 5; break;
        case '#': fingerAngle[0] -= 5; break;
        case '4': fingerAngle[1] -= 5; break;
        case '$': fingerAngle[2] -= 5; break;
        case '5': fingerAngle[3] -= 5; break;
        case '%': fingerAngle[4] -= 5; break;
        
        case 27: exit(0); // Escape key
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Hand Model");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}