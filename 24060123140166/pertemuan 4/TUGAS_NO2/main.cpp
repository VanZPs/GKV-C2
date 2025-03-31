#include <GL/freeglut.h>

static int shoulder = 0, elbow = 0, wrist = 0, fingers = 0;
static float camRotX = 0.0, camRotY = 0.0, camZ = -5.0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, camZ);
    glRotatef(camRotX, 1.0, 0.0, 0.0);
    glRotatef(camRotY, 0.0, 1.0, 0.0);

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
    glTranslatef(0.5, 0.0, 0.0);

    glPushMatrix();
    glScalef(1.0, 0.5, 0.2);
    glutWireCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, 0.15, 0.0);
    glRotatef((GLfloat)fingers, 0.0, 0.0, 1.0);

    for (int i = -3; i <= 3; i += 2) {
        glPushMatrix();
        glTranslatef(0.0, 0.1 * i, 0.0);
        glScalef(0.5, 0.1, 0.1);
        glutWireCube(1.0);
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(-0.1, -0.2, 0.0);
    glRotatef(-20, 0.0, 0.0, 1.0);
    glScalef(0.4, 0.1, 0.1);
    glutWireCube(1.0);
    glPopMatrix();

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
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;
        case 'f': fingers = (fingers + 5) % 360; break;
        case 'F': fingers = (fingers - 5) % 360; break;
        case '+': camZ += 0.2; break;
        case '-': camZ -= 0.2; break;
        case 27: exit(0);
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: camRotY -= 5; break;
        case GLUT_KEY_RIGHT: camRotY += 5; break;
        case GLUT_KEY_UP: camRotX -= 5; break;
        case GLUT_KEY_DOWN: camRotX += 5; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robot Hand with Full Camera Control");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}

