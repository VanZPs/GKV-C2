//
//  main.cpp
//  tugasp22
//
//  Created by aris on 10/03/25.
//

#include <GLUT/glut.h>

void drawShapes() {
    // **1. Garis Strip (GL_LINE_STRIP)**
    glColor3f(1.0f, 0.0f, 0.0f); // Merah
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.8f, 0.8f);
        glVertex2f(-0.6f, 0.9f);
        glVertex2f(-0.4f, 0.7f);
        glVertex2f(-0.2f, 0.8f);
    glEnd();

    // **2. Garis Loop (GL_LINE_LOOP)**
    glColor3f(0.0f, 1.0f, 0.0f); // Hijau
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.2f, 0.8f);
        glVertex2f(0.4f, 0.9f);
        glVertex2f(0.6f, 0.7f);
        glVertex2f(0.8f, 0.8f);
    glEnd();

    // **3. Kipas Segitiga (GL_TRIANGLE_FAN)**
    glColor3f(0.0f, 0.0f, 1.0f); // Biru
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-0.6f, 0.3f); // Titik pusat
        glVertex2f(-0.8f, 0.2f);
        glVertex2f(-0.7f, 0.1f);
        glVertex2f(-0.6f, 0.0f);
        glVertex2f(-0.5f, 0.1f);
        glVertex2f(-0.4f, 0.2f);
    glEnd();

    // **4. Strip Segitiga (GL_TRIANGLE_STRIP)**
    glColor3f(1.0f, 1.0f, 0.0f); // Kuning
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0.4f, 0.3f);
        glVertex2f(0.5f, 0.1f);
        glVertex2f(0.6f, 0.3f);
        glVertex2f(0.7f, 0.1f);
        glVertex2f(0.8f, 0.3f);
    glEnd();

    // **5. Persegi (GL_QUADS)**
    glColor3f(1.0f, 0.5f, 0.0f); // Orange
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, -0.3f);
        glVertex2f(-0.1f, -0.3f);
        glVertex2f(-0.1f, -0.1f);
        glVertex2f(-0.3f, -0.1f);
    glEnd();

    // **6. Strip Persegi Panjang (GL_QUAD_STRIP)**
    glColor3f(0.5f, 0.0f, 0.5f); // Ungu
    glBegin(GL_QUAD_STRIP);
        glVertex2f(0.2f, -0.3f);
        glVertex2f(0.4f, -0.3f);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(0.4f, -0.1f);
        glVertex2f(0.2f, 0.1f);
        glVertex2f(0.4f, 0.1f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawShapes();
    glFlush();
}

void init() {
    glClearColor(0.8f, 0.9f, 1.0f, 1.0f); // Background biru muda
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Primitives Example");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
