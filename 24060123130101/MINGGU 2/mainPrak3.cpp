#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

float posX = 0.0, posY = 0.0, rotasi = 0.0;
void lingkaran(float x, float y, float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float sudut = i * 3.14159 / 180;
        glVertex2f(x + radius * cos(sudut), y + radius * sin(sudut));
    }
    glEnd();
}

void kotak(float x, float y, float lebar, float tinggi) {
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + lebar, y);
    glVertex2f(x + lebar, y + tinggi);
    glVertex2f(x, y + tinggi);
    glEnd();
}

void mobil() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); 

    glPushMatrix();  
    glTranslatef(posX, posY, 0);
    glRotatef(rotasi, 0, 0, 1);

    glColor3f(0, 0, 0);
    kotak(-4.5, -2, 1, 0.5);

    kotak(3.5, -2, 1, 0.5);

    glColor3f(1.0, 0.5, 0);
    kotak(-4, -2, 8, 2);

    glBegin(GL_POLYGON);
    glVertex2f(-3, 0);
    glVertex2f(3, 0);
    glVertex2f(2, 2);
    glVertex2f(-2, 2);
    glEnd();

    glColor3f(0.7, 0.9, 1);
    glBegin(GL_POLYGON);
    glVertex2f(-2.8, 0);
    glVertex2f(-0.5, 0);
    glVertex2f(-1, 1.5);
    glVertex2f(-2.2, 1.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.5, 0);
    glVertex2f(2.8, 0);
    glVertex2f(2.2, 1.5);
    glVertex2f(1, 1.5);
    glEnd();

    glPushMatrix();
    glTranslatef(-2.5, -2, 0);
    glRotatef(rotasi, 0, 0, 1);
    glColor3f(0, 0, 0);
    lingkaran(0, 0, 1);
    glColor3f(1, 1, 1);
    lingkaran(0, 0, 0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, -2, 0);
    glRotatef(rotasi, 0, 0, 1);
    glColor3f(0, 0, 0);
    lingkaran(0, 0, 1);
    glColor3f(1, 1, 1);
    lingkaran(0, 0, 0.5);
    glPopMatrix();

    glColor3f(0, 0, 0);
    kotak(0.3, 0.5, 0.5, 0.1);

    glPopMatrix();  
    glFlush();
}

void inisialisasi() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20, 20, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'w') posY += 0.5;
    if (key == 's') posY -= 0.5;
    if (key == 'a') posX -= 0.5;
    if (key == 'd') posX += 0.5;
    if (key == 'q') rotasi += 5;
    if (key == 'e') rotasi -= 5;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Mobil 2D");

    inisialisasi();
    glutDisplayFunc(mobil);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
