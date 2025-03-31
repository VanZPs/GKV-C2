
 #include <GL/glut.h>

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // LINE STRIP
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 1.0f, 0.0f); 
    glVertex2f(-0.8f, 0.8f);
    glVertex2f(-0.6f, 0.6f);
    glVertex2f(-0.4f, 0.8f);
    glVertex2f(-0.2f, 0.6f);
    glEnd();

    // LINE LOOP
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex2f(0.2f, 0.8f);
    glVertex2f(0.4f, 0.6f);
    glVertex2f(0.6f, 0.8f);
    glVertex2f(0.4f, 1.0f);
    glEnd();

    // TRIANGLE FAN
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex2f(-0.6f, 0.2f);
    glVertex2f(-0.8f, 0.0f);
    glVertex2f(-0.6f, -0.2f);
    glVertex2f(-0.4f, 0.0f);
    glEnd();

    // TRIANGLE STRIP
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f, 1.0f, 0.0f); 
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.4f, 0.0f);
    glVertex2f(0.6f, 0.2f);
    glVertex2f(0.8f, 0.0f);
    glEnd();

    // QUAD STRIP
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex2f(-0.8f, -0.4f);
    glVertex2f(-0.6f, -0.6f);
    glVertex2f(-0.4f, -0.4f);
    glVertex2f(-0.2f, -0.6f);
    glEnd();

    // QUADS
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex2f(0.2f, -0.4f);
    glVertex2f(0.2f, -0.8f);
    glVertex2f(0.6f, -0.8f);
    glVertex2f(0.6f, -0.4f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Tugas 1 dan 2");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

