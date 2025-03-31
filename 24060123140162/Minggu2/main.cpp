#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

void jendela(void) {
    // membersihkan layar dan menset warna
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}


void point(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.25, 0.25, 0.0);
    glEnd();
    glFlush();
}

void Garis(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.00, 0.20, 0.0);
    glVertex3f(0.00, -0.20, 0.00);
    glEnd();
    glFlush();
}

void Segitiga(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.10, -0.10, 0.00);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.10, -0.10, 0.00);
    glColor3f(0.0f, 0.0f, 0.1f);
    glVertex3f(0.00, 0.10, 0.00);
    glEnd();
    glFlush();
    
}

void tampilkanSegiEmpat(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Segi empat 1 (kuning) - Kiri
    glColor3f(0.5f, 0.5f, 0.0f);
    glRectf(-0.80, 0.20, -0.40, -0.20);

    // Segi empat 2 (merah) - Tengah
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(-0.30, 0.20, 0.10, -0.20);

    // Segi empat 3 (biru) - Kanan
    glColor3f(0.0f, 0.0f, 1.0f);
    glRectf(0.20, 0.20, 0.60, -0.20);

    // Segi empat tambahan
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(-0.50, 0.60, -0.10, 0.20);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(0.00, 0.60, 0.40, 0.20);
    

    glFlush();
}

int main (int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Segiempat");
    
    glutDisplayFunc(tampilkanSegiEmpat);
    glClearColor(0.478f, 0.451f, 0.820f, 1.0f);
    glutMainLoop();
    

    
    
    
    
    return 0;
}
