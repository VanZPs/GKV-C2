#include <gl/glut.h>

void TowerDefend(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
		glColor3f(0.71f, 0.69f, 0.69f);
		
		//atas kiri
		glVertex2f(-0.2, 0.39);
		glVertex2f(-0.1, 0.39);
		glVertex2f(-0.1, 0.49);
		glVertex2f(-0.2, 0.49);
		
		//atas tengah
		glVertex2f(0.05, 0.39);
		glVertex2f(-0.05, 0.39);
		glVertex2f(-0.05, 0.49);
		glVertex2f(0.05, 0.49);
		
		//atas kanan
		glVertex2f(0.2, 0.39);
		glVertex2f(0.1, 0.39);
		glVertex2f(0.1, 0.49);
		glVertex2f(0.2, 0.49);
		
		//blok 1
		glVertex2f(0.2, 0.33);
		glVertex2f(-0.2, 0.33);
		glVertex2f(-0.2, 0.38);
		glVertex2f(0.2, 0.38);
		
		//Trapesium 
		glVertex2f(0.15, 0.26);
		glVertex2f(-0.15, 0.26);
		glVertex2f(-0.2, 0.32);
		glVertex2f(0.2, 0.32);
		
		//1
		glVertex2f(0.15, 0.25);
		glVertex2f(0.05, 0.25);
		glVertex2f(0.05, 0.15);
		glVertex2f(0.15, 0.15);
		
		//2
		glVertex2f(0.04, 0.25);
		glVertex2f(-0.06, 0.25);
		glVertex2f(-0.06, 0.15);
		glVertex2f(0.04, 0.15);
		
		//3
		glVertex2f(-0.07, 0.25);
		glVertex2f(-0.15, 0.25);
		glVertex2f(-0.15, 0.05);
		glVertex2f(-0.07, 0.05);
		
		//4
		glVertex2f(-0.06, 0.14);
		glVertex2f(0.15, 0.14);
		glVertex2f(0.15, 0.05);
		glVertex2f(-0.06, 0.05);
		
		//5
		glVertex2f(0.15, 0.04);
		glVertex2f(0.05, 0.04);
		glVertex2f(0.05, -0.15);
		glVertex2f(0.15, -0.15);
		
		//6
		glVertex2f(0.04, 0.04);
		glVertex2f(-0.15, 0.04);
		glVertex2f(-0.15, -0.05);
		glVertex2f(0.04, -0.05);
		
		//7
		glVertex2f(0.04, -0.06);
		glVertex2f(-0.05, -0.06);
		glVertex2f(-0.05, -0.15);
		glVertex2f(0.04, -0.15);
		
		//8
		glVertex2f(-0.06, -0.06);
		glVertex2f(-0.15, -0.06);
		glVertex2f(-0.15, -0.25);
		glVertex2f(-0.06, -0.25);

		//9
		glVertex2f(-0.05, -0.16);
		glVertex2f(0.15, -0.16);
		glVertex2f(0.15, -0.25);
		glVertex2f(-0.05, -0.25);
		
		//blok3
		glColor3f(0.71f, 0.69f, 0.69f);
		glVertex2f(0.2, -0.26);
		glVertex2f(-0.2, -0.26);
		glVertex2f(-0.2, -0.32);
		glVertex2f(0.2, -0.32);
		
		//blok4
		glVertex2f(0.25, -0.33);
		glVertex2f(-0.25, -0.33);
		glVertex2f(-0.25, -0.4);
		glVertex2f(0.25, -0.4);
	
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500,500);
	glutCreateWindow("Tower Defend");
	glutDisplayFunc(TowerDefend);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}
