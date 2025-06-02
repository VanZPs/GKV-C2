//
//  main.cpp
//  TranslasiObjek
//
//  Created by aris on 15/03/25.
//

#include <glut/glut.h>
void SegiEmpat(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glTranslatef(-0.50, 0.50, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(-0.18, 0.18, 0.18, -0.18);
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Segi Empat");
    glutDisplayFunc(SegiEmpat);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}
