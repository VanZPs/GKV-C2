#include <GLUT/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    float size = 0.2;
    float spacing = 0.05;

    float startX = -((3 * size) + (3 * spacing)) / 2;
    float y = -0.2;

    // Kubus bawah 1
    glColor3f(0.3, 0.6, 0.9);
    glBegin(GL_QUADS);
        glVertex2f(startX, y);
        glVertex2f(startX + size, y);
        glVertex2f(startX + size, y + size);
        glVertex2f(startX, y + size);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(startX, y);
        glVertex2f(startX + size, y);
        glVertex2f(startX + size, y + size);
        glVertex2f(startX, y + size);
    glEnd();

    // Kubus bawah 2
    float x2 = startX + size + spacing;
    glColor3f(0.6, 0.3, 0.9);
    glBegin(GL_QUADS);
        glVertex2f(x2, y);
        glVertex2f(x2 + size, y);
        glVertex2f(x2 + size, y + size);
        glVertex2f(x2, y + size);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x2, y);
        glVertex2f(x2 + size, y);
        glVertex2f(x2 + size, y + size);
        glVertex2f(x2, y + size);
    glEnd();

    // Kubus bawah 3
    float x3 = x2 + size + spacing;
    glColor3f(0.8, 0.5, 0.2);
    glBegin(GL_QUADS);
        glVertex2f(x3, y);
        glVertex2f(x3 + size, y);
        glVertex2f(x3 + size, y + size);
        glVertex2f(x3, y + size);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x3, y);
        glVertex2f(x3 + size, y);
        glVertex2f(x3 + size, y + size);
        glVertex2f(x3, y + size);
    glEnd();

    // Kubus bawah 4
    float x4 = x3 + size + spacing;
    glColor3f(0.9, 0.3, 0.5);
    glBegin(GL_QUADS);
        glVertex2f(x4, y);
        glVertex2f(x4 + size, y);
        glVertex2f(x4 + size, y + size);
        glVertex2f(x4, y + size);
    glEnd();
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x4, y);
        glVertex2f(x4 + size, y);
        glVertex2f(x4 + size, y + size);
        glVertex2f(x4, y + size);
    glEnd();

    // Kubus atas 1
    float x5 = startX + (size / 2) + (spacing / 2);
    glColor3f(0.5, 0.7, 1.0);
    glBegin(GL_QUADS);
        glVertex2f(x5, y + size);
        glVertex2f(x5 + size, y + size);
        glVertex2f(x5 + size, y + 2 * size);
        glVertex2f(x5, y + 2 * size);
    glEnd();
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x5, y + size);
        glVertex2f(x5 + size, y + size);
        glVertex2f(x5 + size, y + 2 * size);
        glVertex2f(x5, y + 2 * size);
    glEnd();

    // Kubus atas 2
    float x6 = x5 + size + spacing;
    glColor3f(1.0, 0.6, 0.8);
    glBegin(GL_QUADS);
        glVertex2f(x6, y + size);
        glVertex2f(x6 + size, y + size);
        glVertex2f(x6 + size, y + 2 * size);
        glVertex2f(x6, y + 2 * size);
    glEnd();
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x6, y + size);
        glVertex2f(x6 + size, y + size);
        glVertex2f(x6 + size, y + 2 * size);
        glVertex2f(x6, y + 2 * size);
    glEnd();

    // Kubus atas 3
    float x7 = x6 + size + spacing;
    glColor3f(0.6, 1.0, 0.6);
    glBegin(GL_QUADS);
        glVertex2f(x7, y + size);
        glVertex2f(x7 + size, y + size);
        glVertex2f(x7 + size, y + 2 * size);
        glVertex2f(x7, y + 2 * size);
    glEnd();
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x7, y + size);
        glVertex2f(x7 + size, y + size);
        glVertex2f(x7 + size, y + 2 * size);
        glVertex2f(x7, y + 2 * size);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Stacked Cubes");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
