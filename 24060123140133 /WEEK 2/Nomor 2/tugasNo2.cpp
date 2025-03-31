#include <GLUT/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Dinding rumah (GL_QUADS)
    glBegin(GL_QUADS);
        glColor3f(   1, 0.75, 0.93);
        glVertex2f(-0.4, -0.4);
        glVertex2f(0.4, -0.4);
        glVertex2f(0.4, 0.2);
        glVertex2f(-0.4, 0.2);
    glEnd();
 
    // Atap rumah (GL_TRIANGLE_FAN)
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.52, 0.3, 0.53);
        glVertex2f(0.0, 0.6);
        glVertex2f(-0.5, 0.2);
        glVertex2f(0.5, 0.2);
    glEnd();
    
    // Pintu (GL_QUAD_STRIP)
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.3, 0.2, 0.1);
        glVertex2f(0.0, -0.4);
        glVertex2f(0.2, -0.4);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.2, 0.0);
    glEnd();
    
    // Jendela (GL_QUADS)
    glBegin(GL_QUADS);
        glColor3f(0.77, 0.9, 0.88);
        glVertex2f(-0.3, -0.1);
        glVertex2f(-0.1, -0.1);
        glVertex2f(-0.1, 0.1);
        glVertex2f(-0.3, 0.1);
    glEnd();
    
    // Bingkai jendela (GL_LINE_LOOP)
    glColor3f(0.36, 0.49, 0.47);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.3, -0.1);
        glVertex2f(-0.1, -0.1);
        glVertex2f(-0.1, 0.1);
        glVertex2f(-0.3, 0.1);
    glEnd();
    
    // Jalan menuju rumah (GL_QUADS)
    glBegin(GL_QUADS);
        glColor3f(0.81, 0.89, 1);
        glVertex2f(0.0, -0.4);
        glVertex2f(0.2, -0.4);
        glVertex2f(0.55, -0.9);
        glVertex2f(-0.35, -0.9);   
    glEnd();
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL House");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
