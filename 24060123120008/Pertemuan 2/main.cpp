#include <gl/glut.h>

void glColorRGB(int r, int g, int b) {
	glColor3f(r / 255.0f, g / 255.0f, b / 255.0f);
}

void createSquare(float x, float y, float size) {
	glBegin(GL_QUADS);
		glColorRGB(91, 155, 213);
		glVertex2f(x, y);
		glVertex2f(x, y + size);
		glVertex2f(x + size, y + size);
		glVertex2f(x + size, y);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
		glColorRGB(74, 127, 175);
		glVertex2f(x, y);
		glVertex2f(x, y + size);
		glVertex2f(x + size, y + size);
		glVertex2f(x + size, y);
	glEnd();
}

void drawSquares() {
	float size = 0.2;
	
	createSquare(-0.35, -0.3, size);
	createSquare(-0.1, -0.3, size);
	createSquare(0.15, -0.3, size);
	createSquare(-0.225, -0.1, size);
	createSquare(0.025, -0.1, size);
}

void displaySquares() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawSquares();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Stacked Squares");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glutDisplayFunc(displaySquares);
	glutMainLoop();
	
	return 0;
}

