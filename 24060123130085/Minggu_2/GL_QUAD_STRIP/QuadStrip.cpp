#include <gl/glut.h>

void QuadsStrip(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2f(-0.8, -0.5);  
    glVertex2f(-0.8,  0.5);  
    glVertex2f(-0.4, -0.5);  
    glVertex2f(-0.4,  0.5); 
	glColor3f(0.0f, 0.0f, 0.5f); 
    glVertex2f( 0.0, -0.5);  
    glVertex2f( 0.0,  0.5);  
    glVertex2f( 0.4, -0.5);
    glEnd();
    glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Quad Strip");
	glutDisplayFunc(QuadsStrip);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}
