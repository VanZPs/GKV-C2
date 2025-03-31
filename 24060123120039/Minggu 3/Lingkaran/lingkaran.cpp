#include <GL/glut.h>
#include <cmath>

const float PI = 3.14159265358979323846f;

void drawCircle(float radius, int num_segments, float x_pos, float y_pos) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = x_pos + radius * cosf(theta);
        float y = y_pos + radius * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

// Fungsi untuk menampilkan
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f); 
    drawCircle(0.15f, 36, 0.0f, 0.3f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawCircle(0.15f, 36, -0.2f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    drawCircle(0.15f, 36, 0.2f, 0.0f);
    glFlush();
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("Tiga Lingkaran Piramida");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    
    glutMainLoop();
    
    return 0;
}
