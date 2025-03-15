//
//  main.cpp
//  Lingkaran
//
//  Created by aris on 15/03/25.
//

#include <glut/glut.h>
#include <opengl/gl.h>
#include <math.h>

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        #define PI 3.1415926535898
        glBegin(GL_LINE_LOOP);
            GLint circle_points = 100;
            int i;
            float angle;
            for (i = 0; i < circle_points; i++) {
                angle = 2 * PI * i / circle_points;
                glVertex2f(0.2 * cos(angle), 0.2 * sin(angle));
            }
        glEnd();
    glPopMatrix();
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Circle");
    glutDisplayFunc(RenderScene);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}
