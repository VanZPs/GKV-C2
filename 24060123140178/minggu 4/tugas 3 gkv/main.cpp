#include <GL/glut.h>

static int shoulder = 0, elbow = 0, wrist = 0;
static int finger1 = 0, finger2 = 0, finger3 = 0, finger4 = 0, finger5 = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Bahu
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Siku
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Pergelangan tangan
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);
    glTranslatef(0.5, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.0, 0.4, 0.8);
    glutWireCube(1.0);
    glPopMatrix();

    // Jari-jari tangan
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(0.3, 0.2 - i * 0.1, 0.0);
        glRotatef((GLfloat)(i == 0 ? finger1 : i == 1 ? finger2 : i == 2 ? finger3 : i == 3 ? finger4 : finger5), 0.0, 0.0, 1.0);
        glTranslatef(0.2, 0.0, 0.0);
        glPushMatrix();
        glScalef(0.4, 0.1, 0.1);
        glutWireCube(1.0);
        glPopMatrix();
        glPopMatrix();
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
        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;
        case '1': finger1 = (finger1 + 5) % 360; break;
        case '!': finger1 = (finger1 - 5) % 360; break;
        case '2': finger2 = (finger2 + 5) % 360; break;
        case '@': finger2 = (finger2 - 5) % 360; break;
        case '3': finger3 = (finger3 + 5) % 360; break;
        case '#': finger3 = (finger3 - 5) % 360; break;
        case '4': finger4 = (finger4 + 5) % 360; break;
        case '$': finger4 = (finger4 - 5) % 360; break;
        case '5': finger5 = (finger5 + 5) % 360; break;
        case '%': finger5 = (finger5 - 5) % 360; break;
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

