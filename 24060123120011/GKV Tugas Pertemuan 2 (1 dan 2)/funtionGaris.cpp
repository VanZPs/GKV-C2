// Nama			:	Ivan Pratomo Soelistio
// NIM			:	24060123120011
// Deskripsi	:	Mencoba function bawaan untuk membuat primitive object

#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Set color to white
    glColor3f(1.0f, 1.0f, 1.0f);

    // GL_LINE_STRIP
    glPushMatrix();
    glTranslatef(-0.8f, 0.6f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.2f, 0.0f);
    glEnd();
    glPopMatrix();

    // GL_LINE_LOOP
    glPushMatrix();
    glTranslatef(0.2f, 0.6f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.0f, 0.0f);
    glEnd();
    glPopMatrix();

    // GL_TRIANGLE_FAN
    glPushMatrix();
    glTranslatef(-0.6f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // center
    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.15f, 0.15f);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(-0.15f, 0.15f);
    glVertex2f(-0.2f, 0.0f);
    glVertex2f(-0.15f, -0.15f);
    glVertex2f(0.0f, -0.2f);
    glVertex2f(0.15f, -0.15f);
    glVertex2f(0.2f, 0.0f); // close loop
    glEnd();
    glPopMatrix();

    // GL_TRIANGLE_STRIP
    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(-0.2f, 0.1f);
    glVertex2f(0.0f, -0.1f);
    glVertex2f(0.0f, 0.1f);
    glVertex2f(0.2f, -0.1f);
    glVertex2f(0.2f, 0.1f);
    glEnd();
    glPopMatrix();

    // GL_QUADS
    glPushMatrix();
    glTranslatef(-0.7f, -0.6f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.2f, -0.2f);
    glVertex2f(-0.2f,  0.0f);
    glVertex2f( 0.0f,  0.0f);
    glVertex2f( 0.0f, -0.2f);
    glEnd();
    glPopMatrix();

    // GL_QUAD_STRIP
    glPushMatrix();
    glTranslatef(0.2f, -0.6f, 0.0f);
    glBegin(GL_QUAD_STRIP);
    glVertex2f(-0.2f, -0.2f);
    glVertex2f(-0.2f,  0.0f);
    glVertex2f( 0.0f, -0.2f);
    glVertex2f( 0.0f,  0.0f);
    glVertex2f( 0.2f, -0.2f);
    glVertex2f( 0.2f,  0.0f);
    glEnd();
    glPopMatrix();

    glFlush();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Primitive Examples");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
	return 0;
}
