// Nama		:	Ivan Pratomo Soelistio
// NIM		:	24060123120011

#include <GL/glut.h>
#include <cmath>

// Rotasi sudut
float angleX = 0.0f, angleY = 0.0f;

// Posisi kamera (dinamis)
float eyeX = 0, eyeY = 0, eyeZ = 5;
float centerX = 0, centerY = 0, centerZ = 0;
float upX = 0, upY = 1, upZ = 0;

// Variabel buat mengatur mouse drag
int lastMouseX, lastMouseY;
bool isDragging = false;

void drawMeja() {
    // Meja atas
    glPushMatrix();
    glColor3f(0.72f, 0.52f, 0.04f); // warnanya coklat muda
    glScalef(2.0f, 0.1f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Kaki meja
    float legX[] = {-0.9f, 0.9f};
    float legZ[] = {-0.4f, 0.4f};

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            glPushMatrix();
            glColor3f(0.36f, 0.25f, 0.20f); // coklat tua
            glTranslatef(legX[i], -0.55f, legZ[j]);
            glScalef(0.1f, 1.0f, 0.1f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);
    drawMeja();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8f, 0.8f, 0.9f, 1.0f);
}

void keyboard(unsigned char key, int x, int y) {
    upX = 0;
	upY = 1; 
	upZ = 0;
    switch (key) {
        case '1': eyeX = 0; eyeY = 0; eyeZ = 5; break;           // Front view
        case '2': eyeX = 5; eyeY = 0; eyeZ = 0; break;           // Side view
        case '3': eyeX = 0; eyeY = 5; eyeZ = 0; upZ = -1; break; // Plan view
        case '4': eyeX = 3; eyeY = 3; eyeZ = 3; break;           // Isometric
        case '5': eyeX = 4; eyeY = 2; eyeZ = 3; break;           // Dimetric
        case '6': eyeX = 5; eyeY = 2; eyeZ = 1; break;           // Trimetric
        case '7': eyeX = 0; eyeY = 2; eyeZ = 5; break;           // 1-point perspective
        case '8': eyeX = 3; eyeY = 2; eyeZ = 3; break;           // 2-point perspective
        case '9': eyeX = 3; eyeY = 3; eyeZ = 3; upX = 0; upY = 0; upZ = 1; break; // 3-point perspective
    }
    glutPostRedisplay();
}

// Tombol arah panah buat rotasi manual
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT: angleY -= 5; break;
        case GLUT_KEY_RIGHT: angleY += 5; break;
        case GLUT_KEY_UP: angleX -= 5; break;
        case GLUT_KEY_DOWN: angleX += 5; break;
    }
    glutPostRedisplay();
}

// Mouse klik
void mouseKlik(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            isDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        } else {
            isDragging = false;
        }
    }
}

// Mouse drag buat rotasi dinamis manual
void motionDrag(int x, int y) {
    if (isDragging) {
        angleY += (x - lastMouseX) * 0.5f;
        angleX += (y - lastMouseY) * 0.5f;
        lastMouseX = x;
        lastMouseY = y;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Meja 3D");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys); // tombol panah
    glutMouseFunc(mouseKlik);
    glutMotionFunc(motionDrag);
    glutMainLoop();
    return 0;
}

