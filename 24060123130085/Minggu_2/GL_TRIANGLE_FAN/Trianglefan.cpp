#include <GL/glut.h>

void TriangleFan(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex2f(0.0, 0.0);
	    glVertex2f(0.5, 0.0);
	    glColor3f(1.0f, 0.0f, 0.0f);
	    glVertex2f(0.0, 0.5);
	    glVertex2f(-0.5, 0.0);
	    glColor3f(1.0f, 0.0f, 0.0f);
	    glVertex2f(0.0, -0.5);
	    glVertex2f(0.5, 0.0);
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Triangle Fan");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutDisplayFunc(TriangleFan);
	glutMainLoop();
	return 0;
}
