#include <gl/glut.h>

void Quads(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.1f);
	glVertex2f(-0.8, -0.3);
    glVertex2f(-0.8,  0.3);
    glVertex2f(-0.2,  0.3);
    glVertex2f(-0.2, -0.3);
    glEnd();
    glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Quads");
	glutDisplayFunc(Quads);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}
