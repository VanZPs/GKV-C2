#include <GLUT/glut.h>

void drawSquare(float x, float y, float size, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
    glEnd();
}

void drawStackedSquares() {
    // Lapisan bawah (3 persegi)
    drawSquare(-0.3f, -0.3f, 0.2f, 1.0f, 0.0f, 0.0f); // Merah
    drawSquare(-0.1f, -0.3f, 0.2f, 0.0f, 1.0f, 0.0f); // Hijau
    drawSquare(0.1f, -0.3f, 0.2f, 0.0f, 0.0f, 1.0f); // Biru

    // Lapisan tengah (2 persegi)
    drawSquare(-0.2f, -0.1f, 0.2f, 1.0f, 1.0f, 0.0f); // Kuning
    drawSquare(0.0f, -0.1f, 0.2f, 1.0f, 0.0f, 1.0f); // Ungu

    // Lapisan atas (1 persegi lebih tinggi)
    drawSquare(-0.1f, 0.1f, 0.2f, 0.5f, 0.5f, 0.5f); // Abu-Abu

    // Bagian paling atas (persegi kecil sebagai puncak)
    drawSquare(-0.05f, 0.3f, 0.1f, 1.0f, 0.5f, 0.0f); // Orange
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawStackedSquares();
    glFlush();
}

void init() {
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f); // Warna biru muda sebagai background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.5, 0.5, -0.5, 0.5);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Stacked Squares Tower");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
