#include <GL/glut.h>
#include <cmath>

void drawWheel(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159 / 180;
        glVertex2f(0.1 * cos(angle), 0.1 * sin(angle));
    }
    glEnd();
    glPopMatrix();
}

void drawCar() {
    glPushMatrix();
    glTranslatef(-0.5, -0.3, 0);

    // Body bawah mobil
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.0, 0.0);
    glVertex2f(1.0, 0.0);
    glVertex2f(1.0, 0.3);
    glVertex2f(0.0, 0.3);
    glEnd();

    // Body atas mobil
    glColor3f(0.0, 0.0, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(0.2, 0.3);
    glVertex2f(0.8, 0.3);
    glVertex2f(0.6, 0.5);
    glVertex2f(0.4, 0.5);
    glEnd();

    // Roda depan dan belakang
    drawWheel(0.2, -0.05);
    drawWheel(0.8, -0.05);

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    drawCar();
    
    glutSwapBuffers();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(500, 500);
//    glutCreateWindow("Mobil 2D dengan OpenGL");
//    init();
//    glutDisplayFunc(display);
//    glutMainLoop();
//    return 0;
//}
