#include <GLUT/glut.h>

void drawWheel(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    
    // Ban luar
    glColor3f(0.0, 0.0, 0.0);
    glutSolidSphere(0.1, 20, 20);
    
    // Velg dalam
    glColor3f(0.6, 0.6, 0.6);
    glutSolidSphere(0.05, 20, 20);
    
    glPopMatrix();
}

void drawCar() {
    glPushMatrix();
    
    // Badan mobil
    glColor3f(0.13, 0.25, 0.25);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.2); // Titik kiri bawah
        glVertex2f(0.5, -0.2);  // Titik kanan bawah
        glVertex2f(0.6, 0.0);   // Titik kanan atas
        glVertex2f(-0.6, 0.0);  // Titik kiri atas
    glEnd();
    
    // Atap mobil
    glColor3f(0.08, 0.16, 0.16);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3, 0.0);  // Titik kiri bawah atap
        glVertex2f(0.3, 0.0);   // Titik kanan bawah atap
        glVertex2f(0.2, 0.2);   // Titik kanan atas atap
        glVertex2f(-0.2, 0.2);  // Titik kiri atas atap
    glEnd();
    
    // Jendela kiri (trapesium)
    glColor3f(0.5, 0.8, 1.0); // Warna biru muda untuk jendela
    glBegin(GL_POLYGON);
        glVertex2f(-0.25, 0.05); // Titik kiri bawah jendela kiri
        glVertex2f(-0.20, 0.15); // Titik kiri atas jendela kiri
        glVertex2f(-0.03, 0.15); // Titik kanan atas jendela kiri
        glVertex2f(-0.03, 0.05); // Titik kanan bawah jendela kiri
    glEnd();
    
    // Jendela kanan (trapesium)
    glColor3f(0.5, 0.8, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.04, 0.05); // Titik kiri bawah jendela kanan
        glVertex2f(0.04, 0.15); // Titik kiri atas jendela kanan
        glVertex2f(0.20, 0.15); // Titik kanan atas jendela kanan
        glVertex2f(0.25, 0.05); // Titik kanan bawah jendela kanan
    glEnd();
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0); // Translasi mobil ke posisi awal
    glRotatef(0, 0, 0, 1); //
    drawCar();
    glPopMatrix();
    
    // Ban dengan velg
    drawWheel(-0.3, -0.2); // Ban kiri
    drawWheel(0.3, -0.2);  // Ban kanan
    
    glutSwapBuffers();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mobil 2D Ladya");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
