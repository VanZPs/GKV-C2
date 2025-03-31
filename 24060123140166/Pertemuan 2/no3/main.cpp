#include <GL/freeglut.h>  

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  
}

void drawBlock(float x, float y, float size) {
    glBegin(GL_QUADS);
        glColor3f(0.7f, 0.3f, 0.1f);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
    glEnd();
}

void drawStackedCubes() {
    glClear(GL_COLOR_BUFFER_BIT);
    float size = 0.2f;
    drawBlock(-0.35f, -0.3f, size);
    drawBlock(-0.10f, -0.3f, size);
    drawBlock( 0.15f, -0.3f, size);
    drawBlock(-0.225f, -0.05f, size);
    drawBlock( 0.025f, -0.05f, size);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Piramida Kubus");

    init();  // Inisialisasi koordinat

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(drawStackedCubes);
    glutMainLoop();
    return 0;
}

