#include <GL/glut.h>
#include <cmath>

// Fungsi untuk menggambar lingkaran (roda)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Fungsi untuk menggambar roda dengan garis-garis (jari-jari roda)
void drawWheel(float cx, float cy, float r) {
    glColor3f(0.0f, 0.0f, 0.0f); 
    drawCircle(cx, cy, r, 20);
    
    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) { 
        float theta = i * 3.1415926f / 4.0f; 
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx, cy);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Fungsi untuk menggambar mobil 2D
void drawCar() {
    glPushMatrix(); 

    // ** Badan Mobil **
    glColor3f(1.0f, 0.0f, 1.0f); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, -0.1f);
    glVertex2f(0.4f, -0.1f);
    glVertex2f(0.35f, 0.1f);
    glVertex2f(-0.35f, 0.1f);
    glEnd();

    // ** Atap Mobil **
    glColor3f(1.0f, 0.0f, 1.0f); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, 0.1f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(0.15f, 0.25f);
    glVertex2f(-0.15f, 0.25f);
    glEnd();

    // ** Jendela Depan **
    glColor3f(0.0f, 0.0f, 0.0f); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.15f, 0.12f);
    glVertex2f(0.0f, 0.12f);
    glVertex2f(0.0f, 0.23f);
    glVertex2f(-0.13f, 0.23f);
    glEnd();

    // ** Jendela Belakang **
    glBegin(GL_POLYGON);
    glVertex2f(0.05f, 0.12f);
    glVertex2f(0.17f, 0.12f);
    glVertex2f(0.15f, 0.23f);
    glVertex2f(0.05f, 0.23f);
    glEnd();


    // ** Roda Depan **
	glColor3f(0.0f, 0.0f, 0.0f); 
	drawWheel(-0.25f, -0.15f, 0.07f);

	// ** Roda Belakang **
	drawWheel(0.25f, -0.15f, 0.07f);


    // ** Lampu Depan **
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.38f, 0.02f, 0.02f, 10);

    // ** Lampu Belakang **
    glColor3f(1.0f, 0.0f, 0.0f); 
    drawCircle(-0.38f, 0.02f, 0.02f, 10);

    glPopMatrix(); 
}

// Fungsi display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0f, -0.2f, 0.0f); 
    glRotatef(0.0f, 0.0f, 0.0f, 1.0f); 
    drawCar();
    glPopMatrix();

    glFlush();
}

// Inisialisasi OpenGL
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(1, 1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mobil 2D OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

