// Nama	:	Ivan Pratomo Soelistio
// NIM	:	24060123120011

#include <stdlib.h>  // Standard definitions
#include <stdio.h>   // C I/O (for sprintf)
#include <math.h>    // Standard definitions
#include <GL/glut.h> // OpenGL Utility Toolkit

double rotAngle = 10;  // Rotation angle (Global)
double rotAngle1 = 10; // Rotation angle (Global)

//------------------------------------------------------------------
// init
// Sets up some default OpenGL values.
//------------------------------------------------------------------
void init()
{
    glClearColor(0, 0, 0, 0); // Background color
    glClearDepth(1.0);        // Background depth value

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 1000); // Setup a perspective projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,  // Eye position
              0.0, 0.0, 0.0,  // Look-at position
              0.0, 1.0, 0.0); // Up direction
}

//------------------------------------------------------------------
// display callback function
// This is called each time the application needs to redraw itself.
// Most of the OpenGL work is done through this function.
//------------------------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
    glPushMatrix();                                     // Save the current camera transform

    glRotated(rotAngle, 0, 1, 0);  // Rotate by rotAngle about y-axis
    glRotated(rotAngle1, 1, 0, 0); // Rotate by rotAngle1 about x-axis

    glEnable(GL_COLOR_MATERIAL); // Enable color material
    glColor3f(1.0, 0.1, 0.1);    // Set color to reddish
    glutSolidTeapot(1);          // Draw a teapot

    glPopMatrix();      // Restore the model-view matrix
    glFlush();          // Force OpenGL to render now
    glutSwapBuffers();  // Swap buffers for double buffering
}

//------------------------------------------------------------------
// keyboard callback function
// This is called whenever a keyboard key is pressed.
//------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        rotAngle += 5; // Increase rotation around Y-axis
        break;
    case 'l':
        rotAngle -= 5; // Decrease rotation around Y-axis
        break;
    case 'y':
        rotAngle1 += 5; // Increase rotation around X-axis
        break;
    case 'b':
        rotAngle1 -= 5; // Decrease rotation around X-axis
        break;
    case 'q':
        exit(0); // Exit the program
    }
    glutPostRedisplay(); // Redraw the image now
}

//------------------------------------------------------------------
// main program
// Entry point where everything begins.
//------------------------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB); // Set display mode
    glutCreateWindow("GLUT Example"); // Create window

    glutDisplayFunc(display);   // Register display callback
    glutKeyboardFunc(keyboard); // Register keyboard callback
    init();                     // Perform OpenGL initializations

    glutMainLoop(); // Start the main loop
    return 0;
}

