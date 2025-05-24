#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double rotAngle = 10;  
double rotAngle1 = 10; 

// Inisialisasi OpenGL
void init() {
    glClearColor(0, 0, 0, 0);
    glClearDepth(1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0.0, 0.0, 5.0,  // posisi kamera
        0.0, 0.0, 0.0,  // titik pusat pandangan
        0.0, 1.0, 0.0); // arah atas
}

// Fungsi display untuk menggambar objek
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glRotated(rotAngle, 0, 1, 0);   // rotasi sumbu Y
    glRotated(rotAngle1, 1, 0, 0);  // rotasi sumbu X

    glEnable(GL_COLOR_MATERIAL);
    glColor3f(1.0, 0.1, 0.1);       // warna merah
    glutSolidTeapot(1);            // gambar teapot

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

// Fungsi keyboard untuk tombol biasa
void keyboard(unsigned char k, int x, int y) {
    switch (k) {
        case 'r':
            rotAngle = 0;
            rotAngle1 = 0;
            break;
        case 'q':
            exit(0);
    }
    glutPostRedisplay();
}

// Fungsi keyboard untuk tombol spesial (panah)
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            rotAngle -= 10;
            break;
        case GLUT_KEY_RIGHT:
            rotAngle += 10;
            break;
        case GLUT_KEY_UP:
            rotAngle1 += 10;
            break;
        case GLUT_KEY_DOWN:
            rotAngle1 -= 10;
            break;
    }
    glutPostRedisplay();
}

// Main program
int main() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutCreateWindow("GLUT Teapot Rotasi");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys); // untuk tombol panah
    init();
    glutMainLoop();
    return 0;
}

