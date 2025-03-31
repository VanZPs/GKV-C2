#include<stdio.h>
#include<math.h>
#include <GL/glut.h>

void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void sun(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500, 0.0, 500); // window size
}
float bx = 10;


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Ground Color
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 150);
    glVertex2d(0, 150);
    glEnd();

    // road
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2d(0, 55);
    glVertex2d(500, 55);
    glVertex2d(500, 115);
    glVertex2d(0, 115);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2d(0, 60);
    glVertex2d(500, 60);
    glVertex2d(500, 110);
    glVertex2d(0, 110);
    glEnd();

    //sun design
    glColor3f(1.0f, 0.9f, 0.0f);
    sun(20, 20, 175, 450);


    glPushMatrix();
    glTranslatef(bx, 0, 0);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2d(410, 100);
    glVertex2d(490, 100);
    glVertex2d(485, 130);
    glVertex2d(410, 130);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2d(420, 130);
    glVertex2d(475, 130);
    glVertex2d(465, 160);
    glVertex2d(430, 160);
    glEnd();

    // car window
    glColor3f(0.86f, 0.86f, 0.86f);
    glBegin(GL_POLYGON);
    glVertex2d(425, 130);
    glVertex2d(445, 130);
    glVertex2d(445, 150);
    glVertex2d(430, 150);
    glEnd();

    // car window
    glColor3f(0.86f, 0.86f, 0.86f);
    glBegin(GL_POLYGON);
    glVertex2d(450, 130);
    glVertex2d(470, 130);
    glVertex2d(465, 150);
    glVertex2d(450, 150);
    glEnd();

    // car wheel
    glColor3f(0.0f, 0.0f, 0.0f);
    circle(10, 14, 435, 100);
    circle(10, 14, 465, 100);

    glColor3f(0.96f, 0.96f, 0.96f);
    circle(6, 10, 435, 100);
    circle(6, 10, 465, 100);

    glPopMatrix();
    bx += .05;
    if (bx > 0)
        bx = -500;
    glutPostRedisplay();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(300, 50);
    glutCreateWindow("Mobil");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}