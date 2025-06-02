//
//  main.cpp
//  Mobil
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
    
    // Body of the car
    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_POLYGON);
        glVertex2f(-0.4, -0.2);
        glVertex2f(0.4, -0.2);
        glVertex2f(0.4, 0.0);
        glVertex2f(-0.4, 0.0);
    glEnd();
    
    // Top part of the car
    glColor3f(0.0, 0.0, 1.0); // Blue
    glBegin(GL_POLYGON);
        glVertex2f(-0.2, 0.0);
        glVertex2f(0.2, 0.0);
        glVertex2f(0.15, 0.15);
        glVertex2f(-0.15, 0.15);
    glEnd();
    
    // Wheels
    glPushMatrix();
        glTranslatef(-0.25, -0.25, 0.0);
        glColor3f(0.0, 0.0, 0.0); // Black outer wheel
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0.0, 0.0);
            for (int i = 0; i <= 100; i++) {
                float angle = 2.0f * 3.1415926f * i / 100;
                glVertex2f(0.07 * cos(angle), 0.07 * sin(angle));
            }
        glEnd();
        glColor3f(1.0, 1.0, 1.0); // White inner wheel
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0.0, 0.0);
            for (int i = 0; i <= 100; i++) {
                float angle = 2.0f * 3.1415926f * i / 100;
                glVertex2f(0.03 * cos(angle), 0.03 * sin(angle));
            }
        glEnd();
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(0.25, -0.25, 0.0);
        glColor3f(0.0, 0.0, 0.0); // Black outer wheel
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0.0, 0.0);
            for (int i = 0; i <= 100; i++) {
                float angle = 2.0f * 3.1415926f * i / 100;
                glVertex2f(0.07 * cos(angle), 0.07 * sin(angle));
            }
        glEnd();
        glColor3f(1.0, 1.0, 1.0); // White inner wheel
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0.0, 0.0);
            for (int i = 0; i <= 100; i++) {
                float angle = 2.0f * 3.1415926f * i / 100;
                glVertex2f(0.03 * cos(angle), 0.03 * sin(angle));
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
    glutCreateWindow("2D Car");
    glutDisplayFunc(RenderScene);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}
