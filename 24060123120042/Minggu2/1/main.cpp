/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <GL/glut.h>


void LimaSegiEmpat(void){
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, .0f); glRectf(-0.80, 0.20, -0.40, -0.20);
    glColor3f(0.0f, 0.0f, 0.0f); glRectf(-0.30, 0.20, 0.10, -0.20);
    glColor3f(0.0f, 1.0f, 0.0f); glRectf(0.20, 0.20, 0.60, -0.20);
    glColor3f(1.0f, 0.0f, 0.0f); glRectf(-0.50, 0.60, -0.10, 0.20);
    glColor3f(1.0f, 0.0f, 0.0f); glRectf(0.0, 0.60, 0.40, 0.20);
    glColor3f(1.0f, 1.0f, 0.0f); glRectf(-0.25, 1.0, 0.15, 0.60);	
	glColor3f(1.0f, 0.0f, 0.0f); glRectf(-0.50, -0.20, -0.10, -0.60);
    glColor3f(1.0f, 0.0f, 0.0f); glRectf(0.00, -0.20, 0.40, -0.60);
    glColor3f(1.0f, 1.0f, 0.0f); glRectf(-0.25, -0.60, 0.15, -1.00);
	glFlush();

}
int main(int argc, char*argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(740,740);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Membuat Lima Segi Empat");
	glutDisplayFunc(LimaSegiEmpat);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}

	
