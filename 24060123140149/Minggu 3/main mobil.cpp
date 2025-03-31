#include <GL/glut.h>
#include <cmath>

float carX = 0.0f; // Posisi mobil
float wheelAngle = 0.0f; // Sudut rotasi roda
float roadOffset = 0.0f; // Offset jalan untuk efek bergerak

void drawCircle(float x, float y, float radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

void drawCar() {
    glPushMatrix();
    glTranslatef(carX, -0.3f, 0.0f); // Posisi mobil
    
    // Bodi Mobil
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3f, -0.1f);
    glVertex2f(0.3f, -0.1f);
    glVertex2f(0.35f, 0.1f);
    glVertex2f(-0.35f, 0.1f);
    glEnd();
    
    // Atap Mobil
    glColor3f(0.8f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, 0.1f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(0.15f, 0.2f);
    glVertex2f(-0.15f, 0.2f);
    glEnd();
    
    // Roda
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(-0.2f, -0.1f, 0.0f);
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
    drawCircle(0.0f, 0.0f, 0.05f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.2f, -0.1f, 0.0f);
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
    drawCircle(0.0f, 0.0f, 0.05f);
    glPopMatrix();
    
    glPopMatrix();
}

void drawRoad() {
    glPushMatrix();
    glTranslatef(roadOffset, -0.5f, 0.0f);
    
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.2f);
    glVertex2f(1.0f, -0.2f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawRoad();
    drawCar();
    
    glutSwapBuffers();
}

void update(int value) {
    wheelAngle -= 5.0f; // Roda berputar
    roadOffset -= 0.02f; // Jalan bergerak
    
    if (roadOffset < -1.0f)
        roadOffset = 1.0f;
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a') carX -= 0.05f;
    if (key == 'd') carX += 0.05f;
}

void init() {
    glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Mobil OpenGL GLUT");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);
    
    glutMainLoop();
    return 0;
}

