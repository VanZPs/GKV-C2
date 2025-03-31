#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>


// GL_LINE_STRIP
void LineStrip(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(0.2f, 0.0f, 0.4f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);

        glColor3f(0.6f, 0.1f, 0.7f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.9, 0.7);
    glVertex2f(-0.7, 0.3);
    glVertex2f(-0.5, 0.7);
    glVertex2f(-0.3, 0.3);
    glVertex2f(-0.1, 0.7);
    glVertex2f( 0.1, 0.3);
    glVertex2f( 0.3, 0.7);
    glVertex2f( 0.5, 0.3);
    glVertex2f( 0.7, 0.7);
    glVertex2f( 0.9, 0.3);
    glEnd();
    glFlush();
}

int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("LINE STRIP");
    glutDisplayFunc(LineStrip);
    glClearColor(0.478f, 0.451f, 0.820f, 1.0f);
    glutMainLoop();
    return 0;
}

// LINE LOOP
void LineLoop(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(0.2f, 0.0f, 0.4f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);

        glColor3f(0.6f, 0.1f, 0.7f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.9, 0.7);
    glVertex2f(-0.7, 0.3);
    glVertex2f(-0.5, 0.7);
    glVertex2f(-0.3, 0.3);
    glVertex2f(-0.1, 0.7);
    glVertex2f( 0.1, 0.3);
    glVertex2f( 0.3, 0.7);
    glVertex2f( 0.5, 0.3);
    glVertex2f( 0.7, 0.7);
    glVertex2f( 0.9, 0.3);
    glEnd();

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("LINE LOOP");
    glutDisplayFunc(LineLoop);
    glClearColor(0.478f, 0.451f, 0.820f, 1.0f); // Warna latar belakang
    glutMainLoop();
    return 0;
}


// TRIANGLE FAN
void TriangleFan(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.0, 0.7);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.7, 0.0);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.0, -0.7);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.7, 0.0);
    glEnd();
    glFlush();
}

int main(int argc, char*argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("TRIANGLE FAN");
    glutDisplayFunc(TriangleFan);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}

// TRIANGLE STRIP
void TriangleStrip(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(-0.6, 0.2);
        glVertex2f(-0.6, -0.2);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(-0.4, 0.4);
        glVertex2f(-0.4, -0.4);
        glVertex2f(-0.2, 0.6);
        glVertex2f(-0.2, -0.6);
    glEnd();
    glFlush();
}

int main(int argc, char*argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("TRIANGLE STRIP");
    glutDisplayFunc(TriangleStrip);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}

// QUADS
void Quads(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(0.5, 0.0, 0.5);
        glVertex2f(-0.8, 0.8);
        glVertex2f(-0.4, 0.8);
        glColor3f(1.0, 0.5, 0.0);
        glVertex2f(-0.4, 0.4);
        glVertex2f(-0.8, 0.4);
    glEnd();
    glFlush();
}

int main(int argc, char*argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("QUADS");
    glutDisplayFunc(Quads);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}

//QUAD STRIP
void QuadStrip(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUAD_STRIP);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.6, -0.6);
        glVertex2f(-0.6, -0.2);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-0.2, -0.6);
        glVertex2f(-0.2, -0.2);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(0.2, -0.6);
        glVertex2f(0.2, -0.2);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(0.6, -0.6);
        glVertex2f(0.6, -0.2);
    glEnd();
    glFlush();
}

int main(int argc, char*argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("QUAD STRIP");
    glutDisplayFunc(QuadStrip);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}
