#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

void tampilkanSegiEmpat(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_QUADS);
        glColor3f(0.2f, 0.0f, 0.4f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);

        glColor3f(0.6f, 0.1f, 0.7f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

    // Segi empat 1 (Merah) - Kiri Bawah
    glColor3f(0.8f, 0.0f, 0.0f);
    glRectf(-0.80, -0.30, -0.40, -0.70);

    // Segi empat 2 (Hijau) - Kanan Bawah
    glColor3f(0.0f, 0.6f, 0.2f);
    glRectf(0.20, -0.30, 0.60, -0.70);
    
    // Segi empat 3 - Tengah Bawah
    glColor3f(0.0f, 0.4f, 0.8f);
    glRectf(-0.30, -0.30, 0.10, -0.70);
    
    // Segi empat 4 (Kuning) - Tengah
    glColor3f(1.0f, 0.9f, 0.2f);
    glRectf(-0.05, 0.20, 0.35, -0.20);
    
    // Segi empat 4 (Kuning) - Tengah
    glColor3f(0.3098f, 0.5843f, 0.6157f);
    glRectf(-0.55, 0.20, -0.15, -0.20);
    
    // Segi empat 5 - (Putih) Atas
    glColor3f(0.9f, 0.9f, 0.9f);
    glRectf(-0.30, 0.70, 0.10, 0.30);

    glFlush();
}

void init() {
    glClearColor(0.690f, 0.188f, 0.321f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Segi Empat");
    init();
    glutDisplayFunc(tampilkanSegiEmpat);
    glutMainLoop();
    return 0;
}
