/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>


#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 1. GL_LINE_STRIP (Garis Bersambung)
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0); // Merah
    glVertex2f(-0.8, 0.8);
    glVertex2f(-0.6, 0.6);
    glVertex2f(-0.4, 0.8);
    glEnd();

    // 2. GL_LINE_LOOP (Garis Melingkar)
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 1.0, 0.0); // Hijau
    glVertex2f(-0.3, 0.8);
    glVertex2f(-0.1, 0.6);
    glVertex2f(0.1, 0.8);
    glVertex2f(-0.1, 1.0);
    glEnd();

    // 3. GL_TRIANGLE_FAN (Kipas Segitiga)
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 0.0, 1.0); // Biru
    glVertex2f(0.5, 0.8); // Titik pusat
    glVertex2f(0.4, 0.6);
    glVertex2f(0.6, 0.6);
    glVertex2f(0.7, 0.7);
    glVertex2f(0.6, 0.9);
    glEnd();

    // 4. GL_TRIANGLE_STRIP (Pita Segitiga)
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0, 1.0, 0.0); // Kuning
    glVertex2f(-0.8, 0.3);
    glVertex2f(-0.6, 0.1);
    glVertex2f(-0.4, 0.3);
    glVertex2f(-0.2, 0.1);
    glVertex2f(0.0, 0.3);
    glEnd();

    // 5. GL_QUADS (4 Sisi Terpisah)
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.5, 0.0); // Oranye
    glVertex2f(0.2, 0.3);
    glVertex2f(0.4, 0.3);
    glVertex2f(0.4, 0.1);
    glVertex2f(0.2, 0.1);
    glEnd();

    // 6. GL_QUAD_STRIP (Pita 4 Sisi)
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.5, 0.0, 0.5); // Ungu
    glVertex2f(-0.8, -0.3);
    glVertex2f(-0.6, -0.1);
    glVertex2f(-0.4, -0.3);
    glVertex2f(-0.2, -0.1);
    glVertex2f(0.0, -0.3);
    glVertex2f(0.2, -0.1);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Latar belakang putih
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Primitif OpenGL");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

