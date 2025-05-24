#include <GL/glut.h>
#include <cmath>


void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); 
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); 
        float x = r * cosf(theta);
        float y = r * sinf(theta); 
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f); 
    drawCircle(0.0f, 0.0f, 0.5f, 50); 

    glFlush();
}


void init() {
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // Warna background putih
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Lingkaran OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

