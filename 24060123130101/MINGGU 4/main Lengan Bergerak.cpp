#include <GL/glut.h>

static int shoulder = 0, elbow = 0, wrist = 0, finger1 = 0, finger2 = 0, finger3 = 0, finger4 = 0, thumb = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Rotasi bahu
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    // Menggambar lengan atas
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Rotasi siku
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);

    // Menggambar lengan bawah
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    // Rotasi pergelangan tangan
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);

    // Menggambar telapak tangan
    glPushMatrix();
    glScalef(1.0, 0.4, 0.6);
    glutWireCube(1.0);
    glPopMatrix();

    // Menggambar jari-jari
    float fingerPositions[4][3] = {
        {0.3, 0.2, 0.2},
        {0.3, 0.2, 0.0},
        {0.3, 0.2, -0.2},
        {0.3, 0.2, -0.4}
    };
    int fingerRotations[4] = {finger1, finger2, finger3, finger4};
    
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(fingerPositions[i][0], fingerPositions[i][1], fingerPositions[i][2]);
        glRotatef((GLfloat)fingerRotations[i], 0.0, 0.0, 1.0);
        glTranslatef(0.2, 0.0, 0.0);
        glScalef(0.4, 0.1, 0.1);
        glutWireCube(1.0);
        glPopMatrix();
    }

    // Menggambar ibu jari
    glPushMatrix();
    glTranslatef(0.2, -0.1, 0.1);
    glRotatef((GLfloat)thumb, 0.0, 0.0, 1.0);
    glTranslatef(0.15, 0.0, 0.0);
    glScalef(0.3, 0.1, 0.1);
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
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;
        case 'f': finger1 = (finger1 + 5) % 360; break;
        case 'F': finger1 = (finger1 - 5) % 360; break;
        case 'g': finger2 = (finger2 + 5) % 360; break;
        case 'G': finger2 = (finger2 - 5) % 360; break;
        case 'h': finger3 = (finger3 + 5) % 360; break;
        case 'H': finger3 = (finger3 - 5) % 360; break;
        case 'j': finger4 = (finger4 + 5) % 360; break;
        case 'J': finger4 = (finger4 - 5) % 360; break;
        case 't': thumb = (thumb + 5) % 360; break;
        case 'T': thumb = (thumb - 5) % 360; break;
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
    glutCreateWindow("Robot Arm with Fingers");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}

