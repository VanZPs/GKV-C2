#include <GL/glut.h>

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    glLoadIdentity();  // Reset the transformations

    // Begin drawing a polygon (triangle)
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);  // Set color to black
    glVertex3f(-0.5, -0.5, -3.0);  // Vertex 1 (x, y, z)

    glColor3f(1.0, 0.0, 0.0);  // Set color to red
    glVertex3f(0.5, -0.5, -3.0);  // Vertex 2 (x, y, z)

    glColor3f(0.0, 0.0, 1.0);  // Set color to blue
    glVertex3f(0.5, 0.5, -3.0);  // Vertex 3 (x, y, z)
    glEnd();  // End drawing the polygon

    glFlush();  // Finish rendering
}

void Reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  // Prevent division by zero

    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  // Reset the projection matrix

    // Set perspective projection
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);  // Field of view, aspect ratio, near and far planes

    glMatrixMode(GL_MODELVIEW);  // Switch back to modelview matrix
    glViewport(0, 0, x, y);  // Set the viewport to cover the entire window
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Single buffer and RGB color mode
    glutInitWindowSize(300, 300);  // Set the window size to 300x300
    glutCreateWindow("Intro");  // Create the window with the title "Intro"

    glClearColor(0.0, 0.0, 0.0, 0.0);  // Set the background color to black

    glutDisplayFunc(Display);  // Set the display function to render the scene
    glutReshapeFunc(Reshape);  // Set the reshape function to handle window resizing

    glutMainLoop();  // Enter the GLUT main loop, which listens for events

    return 0;
}

