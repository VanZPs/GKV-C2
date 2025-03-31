
#include <windows.h>
#include <GL/glut.h>

void SegiEmpat(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 0.0f);
	glRectf(-0.18, 0.18, 0.18, -0.18);
	glFlush();
}
int main(int argc, char*argv[]){
	glutInit(&argc, argv);
	glutInitWindowSize(640,640);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Membuat Segi Empat");
	glutDisplayFunc(SegiEmpat);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}

