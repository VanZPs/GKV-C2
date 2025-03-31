#include <gl/glut.h>

void Line(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(5.f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3f(0.0f, .0f, 1.0f);
	glVertex3f(0.5, 0.5, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Line");
	glutDisplayFunc(Line);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}
