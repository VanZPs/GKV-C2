#include <GL/freeglut.h>
#include <cmath>

// lingkaran buat roda sama velg
void drawCircle(float x, float y, float radius, int segments = 50) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
}

// Roda sama velg
void drawWheel(float x, float y, float outerRadius, float innerRadius) {
    glColor3f(0.0, 0.0, 0.0); // Ban luar
    drawCircle(x, y, outerRadius);
    glColor3f(0.6, 0.6, 0.6); // Velg
    drawCircle(x, y, innerRadius);

    // Detail velg
    glColor3f(0.3, 0.3, 0.3);
    for (int i = 0; i < 6; i++) {
        float angle = 2.0f * 3.14159f * i / 6;
        glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x + innerRadius * cos(angle), y + innerRadius * sin(angle));
        glEnd();
    }
}

// Gedung dengan jendela kuning
void drawCityscape() {
    float x = -1.0;
    float heights[] = {0.3, 0.5, 0.4, 0.6, 0.35, 0.55, 0.45, 0.5, 0.4, 0.6};
    
    for (int i = 0; i < 10; i++, x += 0.22) {
        float height = heights[i];
        
        // Gedung
        glColor3f(0.3, 0.3, 0.4);
        glBegin(GL_QUADS);
        glVertex2f(x, -0.4);
        glVertex2f(x + 0.2, -0.4);
        glVertex2f(x + 0.2, height);
        glVertex2f(x, height);
        glEnd();

        // Jendela
        glColor3f(1.0, 1.0, 0.4);
        for (float wy = -0.35; wy < height - 0.05; wy += 0.08) {
            for (float wx = x + 0.02; wx < x + 0.18; wx += 0.06) {
                glBegin(GL_QUADS);
                glVertex2f(wx, wy);
                glVertex2f(wx + 0.04, wy);
                glVertex2f(wx + 0.04, wy + 0.06);
                glVertex2f(wx, wy + 0.06);
                glEnd();
            }
        }
    }
}

// Jalan dan marka
void drawRoad() {
    // Jalan
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(-1.0, -0.4);
    glVertex2f(1.0, -0.4);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();

    // Marka jalan
    glColor3f(1.0, 1.0, 1.0);
    for (float i = -1.0; i < 1.0; i += 0.25) {
        glBegin(GL_QUADS);
        glVertex2f(i, -0.7);
        glVertex2f(i + 0.1, -0.7);
        glVertex2f(i + 0.1, -0.68);
        glVertex2f(i, -0.68);
        glEnd();
    }
}

// Pom bensin sederhana
void drawGasStation() {
    // Atap pom bensin
    glColor3f(0.8, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(0.7, -0.1);
    glVertex2f(1.0, -0.1);
    glVertex2f(1.0, 0.0);
    glVertex2f(0.7, 0.0);
    glEnd();

    // Tiang pom bensin
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUADS);
    glVertex2f(0.75, -0.4);
    glVertex2f(0.78, -0.4);
    glVertex2f(0.78, -0.1);
    glVertex2f(0.75, -0.1);
    glEnd();
}

// Mobil sport
void drawCar() {
    // Body mobil
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6, -0.4);
    glVertex2f(0.6, -0.4);
    glVertex2f(0.55, -0.2);
    glVertex2f(-0.55, -0.2);
    glEnd();

    // Atap mobil
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3, -0.2);
    glVertex2f(0.3, -0.2);
    glVertex2f(0.2, -0.05);
    glVertex2f(-0.2, -0.05);
    glEnd();

    // Kaca film
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(-0.25, -0.18);
    glVertex2f(0.25, -0.18);
    glVertex2f(0.18, -0.06);
    glVertex2f(-0.18, -0.06);
    glEnd();

    // Spoiler
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(-0.55, -0.2);
    glVertex2f(-0.45, -0.2);
    glVertex2f(-0.45, -0.1);
    glVertex2f(-0.55, -0.1);
    glEnd();

    // Lampu depan
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(0.58, -0.34);
    glVertex2f(0.6, -0.34);
    glVertex2f(0.6, -0.3);
    glVertex2f(0.58, -0.3);
    glEnd();

    // Lampu sen depan
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(0.58, -0.38);
    glVertex2f(0.6, -0.38);
    glVertex2f(0.6, -0.36);
    glVertex2f(0.58, -0.36);
    glEnd();

    // Lampu sen belakang
    glBegin(GL_QUADS);
    glVertex2f(-0.6, -0.38);
    glVertex2f(-0.58, -0.38);
    glVertex2f(-0.58, -0.36);
    glVertex2f(-0.6, -0.36);
    glEnd();

    // Roda 
    drawWheel(-0.4, -0.42, 0.12, 0.05);
    drawWheel(0.4, -0.42, 0.12, 0.05);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCityscape();
    drawGasStation();
    drawRoad();
    drawCar();
    glFlush();
}

void init() {
    glClearColor(0.1, 0.1, 0.3, 1.0);
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Mobil Sport di Jalan Kota");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
