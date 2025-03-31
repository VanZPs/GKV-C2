#include <GL/glut.h>

static int shoulder = 0, elbow = 0, wrist = 0;
static int finger[5] = {0, 20, 10, -10, -20};

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawFinger() {
    glPushMatrix();
    glScalef(0.6, 0.1, 0.1);
    glutWireCube(1.0);
    glPopMatrix();
}

void drawPalm() {
    glPushMatrix();
    glScalef(0.8, 0.6, 0.1);
    glutWireCube(1.0);
    glPopMatrix();
}

void drawHand() {
    glPushMatrix();
    drawPalm();

    glPushMatrix();
    glTranslatef(-0.5, -0.2, 0.0);
    glRotatef(-30.0, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)finger[0], 0.0, 0.0, 1.0);
    drawFinger();
    glPopMatrix();

    for (int i = 1; i < 5; ++i) {
        glPushMatrix();
        glTranslatef(-0.4 + 0.2 * (i - 1), 0.4, 0.0);
        glRotatef((GLfloat)finger[i], 0.0, 0.0, 1.0);
        drawFinger();
        glPopMatrix();
    }
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
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
    drawHand();
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
    case 's': shoulder = (shoulder + 5) % 360; break;
    case 'S': shoulder = (shoulder - 5) % 360; break;
    case 'e': elbow = (elbow + 5) % 360; break;
    case 'E': elbow = (elbow - 5) % 360; break;
    case 'w': wrist = (wrist + 5) % 360; break;
    case 'W': wrist = (wrist - 5) % 360; break;
    case '1': finger[0] = (finger[0] + 5) % 360; break;
    case '2': finger[1] = (finger[1] + 5) % 360; break;
    case '3': finger[2] = (finger[2] + 5) % 360; break;
    case '4': finger[3] = (finger[3] + 5) % 360; break;
    case '5': finger[4] = (finger[4] + 5) % 360; break;
    case 27: exit(0); break;
    default: break;
    }
    glutPostRedisplay();
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

