#include <GL/glut.h>

static int shoulder = 0, elbow = 0;
static int finger[5] = {0, 0, 0, 0, 0};

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawFinger(float x, float y, int angle) {
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef((GLfloat)angle, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.4, 0.1, 0.1);
    glutWireCube(1.0);
    glPopMatrix();
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

    // Menggambar lima jari
    for (int i = 0; i < 5; i++) {
        drawFinger(1.1, 0.2 - (i * 0.2), finger[i]);
    }

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
        case '1': finger[0] = (finger[0] + 5) % 360; break;
        case '!': finger[0] = (finger[0] - 5) % 360; break;
        case '2': finger[1] = (finger[1] + 5) % 360; break;
        case '@': finger[1] = (finger[1] - 5) % 360; break;
        case '3': finger[2] = (finger[2] + 5) % 360; break;
        case '#': finger[2] = (finger[2] - 5) % 360; break;
        case '4': finger[3] = (finger[3] + 5) % 360; break;
        case '$': finger[3] = (finger[3] - 5) % 360; break;
        case '5': finger[4] = (finger[4] + 5) % 360; break;
        case '%': finger[4] = (finger[4] - 5) % 360; break;
        case 27: exit(0); break;
        default: return;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robot Arm with Fingers");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
