#include <gl/glut.h>
#include <cmath>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);
    
    glBegin(GL_LINES);
    for (float angle = 0; angle < 360; angle += 45) {
        float rad = angle * 3.14159 / 180.0;
        glVertex2f(0.0f, 0.0f);
        glVertex2f(cos(rad), sin(rad));
    }

    for (float i = -1.0; i <= 1.0; i += 0.2) {
        glVertex2f(-1.0f, i);
        glVertex2f(1.0f, i);
        glVertex2f(i, -1.0f);
        glVertex2f(i, 1.0f);
    }
    
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Garis Kreatif dengan GL_LINES");
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    glClearColor(0, 0, 0, 1);
    glutMainLoop();
    return 0;
}
