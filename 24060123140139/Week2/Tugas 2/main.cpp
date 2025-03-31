#include <GL/glut.h>

void drawPrimitives() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_STRIP);
        glColor3f(0, 1, 0); // Hijau
        glVertex2f(-0.9, 0.8);
        glVertex2f(-0.7, 0.6);
        glVertex2f(-0.5, 0.8);
        glVertex2f(-0.3, 0.6);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 0.5f, 0.0f); // Oranye
        glVertex2f(0.1, 0.8);
        glVertex2f(0.3, 0.6);
        glVertex2f(0.5, 0.8);
        glVertex2f(0.3, 1.0);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.5f, 0.5f, 0.5f); // Abu-abu
        glVertex2f(-0.7, 0.2); 
        glVertex2f(-0.9, 0.0);
        glVertex2f(-0.8, -0.2);
        glVertex2f(-0.6, -0.3);
        glVertex2f(-0.4, -0.2);
        glVertex2f(-0.3, 0.0);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0f, 0.0f, 1.0f); // Biru
        glVertex2f(0.2, 0.2);
        glVertex2f(0.4, 0.0);
        glVertex2f(0.6, 0.2);
        glVertex2f(0.8, 0.0);
        glVertex2f(1.0, 0.2);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0f); // Kuning
        glVertex2f(-0.9, -0.5);
        glVertex2f(-0.7, -0.7);
        glVertex2f(-0.5, -0.7);
        glVertex2f(-0.3, -0.5);
    glEnd();

    glBegin(GL_QUAD_STRIP);
        glColor3f(1.0f, 0.0f, 1.0f); // Magenta
        glVertex2f(0.2, -0.5);
        glVertex2f(0.2, -0.7);
        glVertex2f(0.4, -0.4);
        glVertex2f(0.4, -0.8);
        glVertex2f(0.6, -0.3);
        glVertex2f(0.6, -0.9);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutCreateWindow("Primitif Objek");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Latar belakang hitam
    glutDisplayFunc(drawPrimitives);
    glutMainLoop();
    return 0;
}

