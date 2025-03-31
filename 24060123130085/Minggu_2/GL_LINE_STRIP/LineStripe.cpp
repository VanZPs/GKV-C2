#include <GL/glut.h>

void LineStrip(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0f);
	glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(0.7f, 0.3f);
		glVertex2f(0.1f, 0.0f);
		glVertex2f(0.5f, 0.1f);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.25, 0.2f);
	glEnd();
	glFlush();
	
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Garis dengan line strip");
	glutDisplayFunc(LineStrip);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}
