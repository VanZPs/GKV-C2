#include <GL/glut.h>

void TriangleStrip(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-0.5, -0.5);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(0.5, -0.5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.5, 0.5);
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("triangle Strip");
	glutDisplayFunc(TriangleStrip);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}
