// Nama			: Ivan Pratomo Soelistio
// NIM			: 24060123120011
// Deskripsi	: Tugas praktikum membuat kubus bertingkat.

#include <GL/glut.h>

void Kubus(float x, float y, float size, float r, float g, float b) {
    glBegin(GL_QUADS);
        glColor3f(r, g, b);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size, y + size);
        glVertex2f(x, y + size);
    glEnd();
}

void KubusTingkat() {
    float size = 0.2;
    float colors[][3] = {
        {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0}, {1, 0, 1},
        {0, 1, 1}, {0.5, 0.5, 0}, {0.5, 0, 0.5}, {0, 0.5, 0.5}, {0.7, 0.3, 0.2},
        {0.3, 0.7, 0.2}, {0.2, 0.3, 0.7}, {0.6, 0.2, 0.4}, {0.4, 0.6, 0.2}
    };

    glClear(GL_COLOR_BUFFER_BIT);
    int i = 0;
    
    // Tingkat 5
    Kubus(-0.6, -0.7, size, colors[i][0], colors[i][1], colors[i++][2]);
    Kubus(-0.35, -0.7, size, colors[i][0], colors[i][1], colors[i++][2]);
    Kubus(-0.1, -0.7, size, colors[i][0], colors[i][1], colors[i++][2]);
    Kubus(0.15, -0.7, size, colors[i][0], colors[i][1], colors[i++][2]);
    Kubus(0.4, -0.7, size, colors[i][0], colors[i][1], colors[i++][2]);
    
    // Tingkat 4
    Kubus(-0.47, -0.5, size, colors[i][0], colors[i][1], colors[i++][2]);
    Kubus(-0.225, -0.5, size, colors[i][0], colors[i][1], colors[i++][2]);
    Kubus(0.025, -0.5, size, colors[i][0], colors[i][1], colors[i++][2]);
    Kubus(0.27, -0.5, size, colors[i][0], colors[i][1], colors[i++][2]);
    
    // Tingkat 3
    Kubus(-0.35, -0.3, size, colors[i][0], colors[i][1], colors[i++][2]);
    Kubus(-0.1, -0.3, size, colors[i][0], colors[i][1], colors[i++][2]);
    Kubus(0.15, -0.3, size, colors[i][0], colors[i][1], colors[i++][2]);
    
    // Tingkat 2
    Kubus(-0.225, -0.1, size, colors[i][0], colors[i][1], colors[i++][2]);
    Kubus(0.025, -0.1, size, colors[i][0], colors[i][1], colors[i++][2]);
    
    // Tingkat 1
    Kubus(-0.1, 0.1, size, colors[i][0], colors[i][1], colors[i++][2]);
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutCreateWindow("TUGAS KUBUS BERTINGKAT");
    glClearColor(1.0, 1.0, 0.6, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glutDisplayFunc(KubusTingkat);
    glutMainLoop();
    return 0;
}

