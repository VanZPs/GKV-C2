#include <GL/glut.h>
#include <cmath>

float posX = 0.0f;
float rotAngle = 0.0f;

void isilingkaran(int xc, int yc, int r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(xc, yc);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180;
        glVertex2i(xc + r * cos(angle), yc + r * sin(angle));
    }
    glEnd();
}

void Background() {
    //langit
    glColor3f(0.5, 0.8, 1.0);
    glBegin(GL_POLYGON);
    glVertex2i(0, 200);
    glVertex2i(400, 200);
    glVertex2i(400, 400);
    glVertex2i(0, 400);
    glEnd();

    //jalan
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2i(0, 0);
    glVertex2i(400, 0);
    glVertex2i(400, 100);
    glVertex2i(0, 100);
    glEnd();

    //garis putus-putus
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 0; i < 400; i += 40) {
        glBegin(GL_QUADS);
        glVertex2i(i, 45);
        glVertex2i(i + 20, 45);
        glVertex2i(i + 20, 55);
        glVertex2i(i, 55);
        glEnd();
    }
}

void mobil() {
    glPushMatrix();
    glTranslatef(posX, 0.0f, 0.0f);
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(50, 50);
    glVertex2i(350, 50);
    glVertex2i(380, 100);
    glVertex2i(20, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(100, 100);
    glVertex2i(300, 100);
    glVertex2i(260, 150);
    glVertex2i(140, 150);
    glEnd();

    //ban & velg
    glPushMatrix();
    glTranslatef(120, 40, 0);
    glRotatef(rotAngle, 0, 0, 1);
    glTranslatef(-120, -40, 0);
    glColor3f(0.0, 0.0, 0.0);
    isilingkaran(120, 40, 30);
    glColor3f(0.5, 0.5, 0.5);
    isilingkaran(120, 40, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(280, 40, 0);
    glRotatef(rotAngle, 0, 0, 1);
    glTranslatef(-280, -40, 0);
    glColor3f(0.0, 0.0, 0.0);
    isilingkaran(280, 40, 30);
    glColor3f(0.5, 0.5, 0.5);
    isilingkaran(280, 40, 20);
    glPopMatrix();

    //jendela
    glColor3f(0.9, 0.9, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(150, 100);
    glVertex2i(190, 100);
    glVertex2i(190, 140);
    glVertex2i(150, 140);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(210, 100);
    glVertex2i(250, 100);
    glVertex2i(250, 140);
    glVertex2i(210, 140);
    glEnd();

    //garis kuning
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(140, 90);
    glVertex2i(200, 90);
    glVertex2i(200, 95);
    glVertex2i(140, 95);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2i(220, 90);
    glVertex2i(280, 90);
    glVertex2i(280, 95);
    glVertex2i(220, 95);
    glEnd();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    Background();
    mobil();
    glFlush();
}

void update(int value) {
    posX += 2.0f;
    if (posX > 400) posX = -400;
    rotAngle -= 10.0f;
    if (rotAngle < -360.0f) rotAngle += 360.0f;
    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil 2D");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(50, update, 0);
    glutMainLoop();
    return 0;
}

