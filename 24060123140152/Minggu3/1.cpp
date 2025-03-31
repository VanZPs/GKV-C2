#include <GL/glut.h>
#include <cmath>

float wheelAngle = 0.0f;

void drawCircle(float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.1415926f * i / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawSky() {
    glColor3f(0.5f, 0.8f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-100, 50);
    glVertex2f(100, 50);
    glVertex2f(100, -10);
    glVertex2f(-100, -10);
    glEnd();
}

void drawRoad() {
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-100, -20);
    glVertex2f(100, -20);
    glVertex2f(100, -40);
    glVertex2f(-100, -40);
    glEnd();
    
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = -90; i < 100; i += 20) {
        glBegin(GL_POLYGON);
        glVertex2f(i, -29);
        glVertex2f(i + 10, -29);
        glVertex2f(i + 10, -31);
        glVertex2f(i, -31);
        glEnd();
    }
}

void drawBuilding(float x, float width, float height) {
    glColor3f(0.6f, 0.6f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(x, -10);
    glVertex2f(x + width, -10);
    glVertex2f(x + width, height);
    glVertex2f(x, height);
    glEnd();
    
    glColor3f(0.8f, 0.9f, 1.0f);
    for (float wx = x + 2; wx < x + width - 2; wx += 5) {
        for (float wy = -5; wy < height - 5; wy += 10) {
            glBegin(GL_POLYGON);
            glVertex2f(wx, wy);
            glVertex2f(wx + 3, wy);
            glVertex2f(wx + 3, wy + 6);
            glVertex2f(wx, wy + 6);
            glEnd();
        }
    }
}

void drawBackground() {
    drawSky();
    drawBuilding(-80, 30, 50);
    drawBuilding(-40, 25, 40);
    drawBuilding(0, 35, 60);
    drawBuilding(50, 30, 45);
    drawRoad();
}

void drawWheel(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(wheelAngle, 0, 0, 1);
    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircle(7, 30);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 8; i++) {
        glPushMatrix();
        glRotatef(i * 45, 0, 0, 1);
        glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(7, 0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}

void drawCar() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-35, -10);
    glVertex2f(35, -10);
    glVertex2f(33, 8);
    glVertex2f(-33, 8);
    glEnd();
    
    glColor3f(0.9f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-25, 8);
    glVertex2f(25, 8);
    glVertex2f(18, 20);
    glVertex2f(-18, 20);
    glEnd();
    
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(33, 3);
    glVertex2f(36, 4);
    glVertex2f(36, 1);
    glVertex2f(33, 0);
    glEnd();
    
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(-10, -10);
    glVertex2f(10, -10);
    glVertex2f(10, 8);
    glVertex2f(-10, 8);
    glEnd();
    
    glColor3f(0.2f, 0.2f, 0.2f);
    drawWheel(-20, -15);
    drawWheel(20, -15);
    
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-25, 6);
    glVertex2f(-23, 6);
    glVertex2f(-23, 8);
    glVertex2f(-25, 8);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();
    drawCar();
    glutSwapBuffers();
}

void update(int value) {
    wheelAngle += 5.0f;
    if (wheelAngle > 360) wheelAngle -= 360;
    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void init() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -50, 50);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Mobil 2D di Jalan Kota");
    glutDisplayFunc(display);
    glutTimerFunc(30, update, 0);
    init();
    glutMainLoop();
    return 0;
}
