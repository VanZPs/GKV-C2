/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>


#include <GL/glut.h>

void drawCube(float x, float y, float r, float g, float b) {
    // Gambar permukaan kubus
    glBegin(GL_QUADS);
    glColor3f(r, g, b);  // Warna sesuai parameter
    glVertex2f(x, y);
    glVertex2f(x + 0.2f, y);
    glVertex2f(x + 0.2f, y + 0.2f);
    glVertex2f(x, y + 0.2f);
    glEnd();

    // Gambar garis tepi
    glLineWidth(2.0f);  // Tebal garis
    glColor3f(0.0f, 0.0f, 0.0f);  // Warna hitam untuk tepi
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + 0.2f, y);
    glVertex2f(x + 0.2f, y + 0.2f);
    glVertex2f(x, y + 0.2f);
    glEnd();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawCube(-0.3f, -0.3f, 1.0f, 0.0f, 0.0f); 
    drawCube(-0.05f, -0.3f, 0.0f, 1.0f, 0.0f);
    drawCube(0.2f, -0.3f, 0.0f, 0.0f, 1.0f); 

    drawCube(-0.175f, -0.1f, 1.0f, 1.0f, 0.0f); 
    drawCube(0.075f, -0.1f, 1.0f, 0.0f, 1.0f); 

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
    glutCreateWindow("Kubus Bertingkat");
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}

