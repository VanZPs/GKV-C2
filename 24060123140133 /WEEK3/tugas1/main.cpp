#include <GLUT/glut.h>
#include <cmath>

void drawCircle(float x, float y, float radius) {
    int segments = 100; // Jumlah segmen untuk membentuk lingkaran halus
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Titik tengah lingkaran
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.13, 0.25, 0.25);
    drawCircle(0.0, 0.0, 0.5);
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
    glutCreateWindow("Lingkaran");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
