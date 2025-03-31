#include <GL/glut.h>

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.5f, 0.0f); 
    glRectf(-0.3, -0.3, -0.1, -0.1);
    glColor3f(0.5f, 0.0f, 0.5f);
    glRectf(-0.1, -0.3, 0.1, -0.1);
    glColor3f(0.0f, 1.0f, 1.0f); 
    glRectf(0.1, -0.3, 0.3, -0.1);

    glColor3f(1.0f, 0.0f, 1.0f); 
    glRectf(-0.2, -0.1, 0.0, 0.1);
    glColor3f(0.5f, 0.5f, 0.5f); 
    glRectf(0.0, -0.1, 0.2, 0.1);

    glColor3f(0.0f, 0.0f, 0.0f); 
    glRectf(-0.1, 0.1, 0.1, 0.3);
    
    glColor3f(1.0f, 0.0f, 1.0f); 
    glRectf(-0.2, 0.3, 0.0, 0.5);
    glColor3f(0.5f, 0.5f, 0.5f); 
    glRectf(0.0, 0.3, 0.2, 0.5);
    
    glColor3f(1.0f, 0.5f, 0.0f); 
    glRectf(-0.3, 0.5, -0.1, 0.7);
    glColor3f(0.5f, 0.0f, 0.5f);
    glRectf(-0.1, 0.5, 0.1, 0.7);
    glColor3f(0.0f, 1.0f, 1.0f); 
    glRectf(0.1, 0.5, 0.3, 0.7);
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Piramida 10 Kubus");
    glutDisplayFunc(display);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glutMainLoop();
    return 0;
}

