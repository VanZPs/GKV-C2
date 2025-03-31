#include <GL/glut.h>
static int shoulder = 0, elbow = 0, wrist = 0;
static int thumbBase = 0, indexBase = 0, middleBase = 0, ringBase = 0, pinkyBase = 0;

void init(void) {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void drawFingerJoint(float length, float width, float height) {
    glPushMatrix();
    glScalef(length, width, height);
    glutWireCube(1.0);
    glPopMatrix();
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glTranslatef (-1.0, 0.0, 0.0);
    glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef (2.0, 0.4, 1.0);
    glutWireCube (1.0);
    glPopMatrix();
    
    glTranslatef (1.0, 0.0, 0.0);
    glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
    glTranslatef (1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef (2.0, 0.4, 1.0);
    glutWireCube (1.0);
    glPopMatrix();
    
    // Telapak tangan
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat) wrist, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(0.8, 1.2, 0.5);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Jari-jari
    glPushMatrix();
    glTranslatef(0.4, 0.5, 0.0);
    glRotatef((GLfloat) indexBase, 0.0, 0.0, 1.0);
    drawFingerJoint(0.4, 0.15, 0.15);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.4, 0.2, 0.0);
    glRotatef((GLfloat) middleBase, 0.0, 0.0, 1.0);
    drawFingerJoint(0.4, 0.15, 0.15);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.4, -0.15, 0.0);
    glRotatef((GLfloat) ringBase, 0.0, 0.0, 1.0);
    drawFingerJoint(0.4, 0.15, 0.15);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.4, -0.45, 0.0);
    glRotatef((GLfloat) pinkyBase, 0.0, 0.0, 1.0);
    drawFingerJoint(0.3, 0.12, 0.12);
    glPopMatrix();
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;
        case 'i': indexBase = (indexBase + 5) % 90; break;
        case 'I': indexBase = (indexBase - 5) % 90; break;
        case 'm': middleBase = (middleBase + 5) % 90; break;
        case 'M': middleBase = (middleBase - 5) % 90; break;
        case 'r': ringBase = (ringBase + 5) % 90; break;
        case 'R': ringBase = (ringBase - 5) % 90; break;
        case 'p': pinkyBase = (pinkyBase + 5) % 90; break;
        case 'P': pinkyBase = (pinkyBase - 5) % 90; break;
        case 27: exit(0); break;
        default: break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (700, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
