#include <GL/glut.h>

void GambarPrimitif() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // GL_LINE_STRIP (garis bersambung)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.5, 0.5);
    glVertex2f(-0.3, 0.7);
    glVertex2f(-0.1, 0.5);
    glEnd();
    
    // GL_LINE_LOOP (garis tertutup)
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.1, 0.5);
    glVertex2f(0.3, 0.7);
    glVertex2f(0.5, 0.5);
    glEnd();
    
    // GL_TRIANGLE_FAN (kipas segitiga)
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.4, 0.2);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-0.3, 0.0);
    glEnd();
    
    // GL_TRIANGLE_STRIP (strip segitiga)
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(0.1, 0.2);
    glVertex2f(0.2, 0.0);
    glVertex2f(0.3, 0.2);
    glVertex2f(0.4, 0.0);
    glEnd();
    
    // GL_QUADS (segi empat)
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4, -0.2);
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.2, -0.4);
    glVertex2f(-0.4, -0.4);
    glEnd();
    
    // GL_QUAD_STRIP (strip segi empat)
    glColor3f(0.5f, 0.0f, 0.5f);
    glBegin(GL_QUAD_STRIP);
    glVertex2f(0.2, -0.2);
    glVertex2f(0.4, -0.2);
    glVertex2f(0.2, -0.4);
    glVertex2f(0.4, -0.4);
    glEnd();
    
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Gambar Primitif");
    glutDisplayFunc(GambarPrimitif);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}

