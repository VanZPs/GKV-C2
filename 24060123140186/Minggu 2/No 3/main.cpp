#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Persegi 1 (Baris bawah, persegi paling kiri) - Warna Merah
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
      glVertex2f(-0.4f, -0.6f);
      glVertex2f(-0.2f, -0.6f);
      glVertex2f(-0.2f, -0.4f);
      glVertex2f(-0.4f, -0.4f);
    glEnd();

    // Persegi 2 (Baris bawah, persegi kedua) - Warna Hijau
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
      glVertex2f(-0.2f, -0.6f);
      glVertex2f( 0.0f, -0.6f);
      glVertex2f( 0.0f, -0.4f);
      glVertex2f(-0.2f, -0.4f);
    glEnd();

    // Persegi 3 (Baris bawah, persegi ketiga) - Warna Biru
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
      glVertex2f( 0.0f, -0.6f);
      glVertex2f( 0.2f, -0.6f);
      glVertex2f( 0.2f, -0.4f);
      glVertex2f( 0.0f, -0.4f);
    glEnd();

    // Persegi 4 (Baris bawah, persegi paling kanan) - Warna Kuning
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
      glVertex2f( 0.2f, -0.6f);
      glVertex2f( 0.4f, -0.6f);
      glVertex2f( 0.4f, -0.4f);
      glVertex2f( 0.2f, -0.4f);
    glEnd();

    // Persegi 5 (Baris tengah, persegi kiri) - Warna Oranye
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
      glVertex2f(-0.2f, -0.4f);
      glVertex2f( 0.0f, -0.4f);
      glVertex2f( 0.0f, -0.2f);
      glVertex2f(-0.2f, -0.2f);
    glEnd();

    // Persegi 6 (Baris tengah, persegi kanan) - Warna Ungu
    glColor3f(0.5f, 0.0f, 0.5f);
    glBegin(GL_QUADS);
      glVertex2f( 0.0f, -0.4f);
      glVertex2f( 0.2f, -0.4f);
      glVertex2f( 0.2f, -0.2f);
      glVertex2f( 0.0f, -0.2f);
    glEnd();

    // Persegi 7 (Baris atas, persegi tengah) - Warna Cyan
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
      glVertex2f(-0.1f, -0.2f);
      glVertex2f( 0.1f, -0.2f);
      glVertex2f( 0.1f,  0.0f);
      glVertex2f(-0.1f,  0.0f);
    glEnd();

    glFlush();
}

void init() {
    // Atur background menjadi pink
    glClearColor(1.0f, 0.75f, 0.8f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Atur koordinat 2D (kiri, kanan, bawah, atas)
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - 7 Persegi Berwarna Segitiga");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

