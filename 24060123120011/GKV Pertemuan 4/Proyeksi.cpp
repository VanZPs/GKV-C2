//#include <GL/glut.h>
//
//GLfloat xRotated, yRotated, zRotated;
//
//void Display(void) {
//    glClear(GL_COLOR_BUFFER_BIT);
//    glLoadIdentity();
//    glTranslatef(0.0, 0.0, -4.0);
//    glRotatef(xRotated, 1.0, 0.0, 0.0);
//    glRotatef(yRotated, 0.0, 1.0, 0.0);
//    glRotatef(zRotated, 0.0, 0.0, 1.0);
//    glScalef(2.0, 1.0, 1.0);
//    glutWireCube(1.0);
//    glutSwapBuffers();
//}
//
//void Reshape(int x, int y) {
//    if (y == 0 || x == 0) return;
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);
//    glMatrixMode(GL_MODELVIEW);
//    glViewport(0, 0, x, y);
//}
//
//void Idle(void) {
//    xRotated += 0.03;
//    yRotated += 0.01;
//    zRotated += -0.04;
//    glutPostRedisplay(); // Meminta redisplay tanpa pemanggilan langsung
//}
//
//int main(int argc, char **argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(300, 300);
//    glutCreateWindow("Cube example");
//    xRotated = yRotated = zRotated = 0.0;
//    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glutDisplayFunc(Display);
//    glutReshapeFunc(Reshape);
//    glutIdleFunc(Idle);
//    glutMainLoop();
//    return 0;
//}
