#include <gl/glut.h>

void persegiStack() {
    glClear(GL_COLOR_BUFFER_BIT);

    // merah
    glColor3f(1.0, 0.0, 0.0); 
    glRectf(-0.8, -0.8, -0.4, -0.4);

	// hijau
    glColor3f(0.0, 1.0, 0.0); 
    glRectf(-0.4, -0.8, 0.0, -0.4);

	// biru
    glColor3f(0.0, 0.0, 1.0); 
    glRectf(0.0, -0.8, 0.4, -0.4);
	
	// kuning
    glColor3f(1.0, 1.0, 0.0); 
    glRectf(0.4, -0.8, 0.8, -0.4);

    // orange
    glColor3f(1.0, 0.5, 0.0); 
    glRectf(-0.6, -0.4, -0.2, 0.0);
	
	// ungu
    glColor3f(0.5, 0.0, 0.5); 
    glRectf(-0.2, -0.4, 0.2, 0.0);

	// cyan
    glColor3f(0.0, 1.0, 1.0); 
    glRectf(0.2, -0.4, 0.6, 0.0);

    // magenta
    glColor3f(1.0, 0.0, 1.0); 
    glRectf(-0.4, 0.0, 0.0, 0.4);
	
	// hijau muda
    glColor3f(0.2, 0.8, 0.2); 
    glRectf(0.0, 0.0, 0.4, 0.4);

    // putih
    glColor3f(1.0, 1.0, 1.0); // 
    glRectf(-0.2, 0.4, 0.2, 0.8);

    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000); 
    glutCreateWindow("Piramida Persegi Emuach");
    glutDisplayFunc(persegiStack);
    glutMainLoop();
    return 0;
}

