#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265358979323846

// Fungsi untuk menggambar lingkaran
void drawCircle(float radius, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

// Fungsi untuk menggambar roda dengan transformasi
void drawWheel(float x, float y, float radius) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle(radius, 30);
    
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(radius * 0.7f, 30);
    
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle(radius * 0.2f, 20);

    glPopMatrix();
}

// Fungsi untuk menggambar badan mobil dengan transformasi
void drawCarBody() {
    glPushMatrix();
    
    glColor3f(0.8f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, 0.0f);
        glVertex2f(0.7f, 0.0f);
        glVertex2f(0.7f, 0.3f);
        glVertex2f(-0.7f, 0.3f);
    glEnd();
    
    glColor3f(0.2f, 0.2f, 0.8f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3f, 0.3f);
        glVertex2f(0.3f, 0.3f);  
        glVertex2f(0.2f, 0.5f); 
        glVertex2f(-0.3f, 0.5f); 
    glEnd();
    
    glPopMatrix();
}

// Fungsi untuk menggambar lampu kotak dengan transformasi
void drawCarLights() {
    glPushMatrix();
    
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.55f, 0.22f);
        glVertex2f(0.65f, 0.22f);
        glVertex2f(0.65f, 0.28f);
        glVertex2f(0.55f, 0.28f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, 0.22f);
        glVertex2f(-0.55f, 0.22f);
        glVertex2f(-0.55f, 0.28f);
        glVertex2f(-0.65f, 0.28f);
    glEnd();
    
    glPopMatrix();
}

// Fungsi untuk menggambar mobil dengan transformasi
void drawCar() {
    glPushMatrix();
    glTranslatef(0.0f, -0.65f, 0.0f); 
    glScalef(0.8f, 0.8f, 1.0f);      
    
    drawCarBody();
    drawCarLights();
    drawWheel(0.5f, -0.05f, 0.12f);
    drawWheel(-0.5f, -0.05f, 0.12f);
    
    glPopMatrix();
}

// Fungsi untuk menggambar matahari dengan border oranye
void drawSun() {
    glPushMatrix();
    glTranslatef(0.8f, 0.8f, 0.0f); 
    
    glColor3f(1.0f, 0.6f, 0.0f);
    drawCircle(0.18f, 30);
    
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.15f, 30);
    
    glPopMatrix();
}

// Fungsi untuk menggambar gunung
void drawMountain(float x, float height, float width, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, -0.5f, 0.0f); 
    
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
        glVertex2f(-width, 0.0f);    
        glVertex2f(width, 0.0f);    
        glVertex2f(0.0f, height);    
    glEnd();
    
    glPopMatrix();
}

// Fungsi untuk menggambar dua gunung besar
void drawMountains() {
    drawMountain(-0.75f, 0.95f, 0.75f, 0.4f, 0.4f, 0.5f);
    
    drawMountain(0.75f, 0.85f, 0.75f, 0.5f, 0.5f, 0.6f);
}

// Fungsi untuk menggambar jalan yang lebih ke bawah
void drawRoad() {
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.5f, -0.8f);
        glVertex2f(1.5f, -0.8f);
        glVertex2f(1.5f, -0.5f);
        glVertex2f(-1.5f, -0.5f);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
    for (float x = -1.4f; x < 1.5f; x += 0.4f) {
        glBegin(GL_POLYGON);
            glVertex2f(x, -0.66f);
            glVertex2f(x + 0.2f, -0.66f);
            glVertex2f(x + 0.2f, -0.64f);
            glVertex2f(x, -0.64f);
        glEnd();
    }
    
    glPopMatrix();
}

// Fungsi untuk menggambar background/langit
void drawBackground() {
    glBegin(GL_POLYGON);
        glColor3f(0.4f, 0.7f, 1.0f); 
        glVertex2f(-1.5f, -0.5f);
        glVertex2f(1.5f, -0.5f);
        
        glColor3f(0.2f, 0.5f, 0.9f); 
        glVertex2f(1.5f, 1.0f);
        glVertex2f(-1.5f, 1.0f);
    glEnd();
}

// Fungsi display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    drawBackground();
    drawSun();
    drawMountains(); 
    drawRoad();
    drawCar();
    
    glutSwapBuffers();
}

// Fungsi reshape
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if (width <= height)
        glOrtho(-1.0, 1.0, -1.0 * height / width, 1.0 * height / width, -1.0, 1.0);
    else
        glOrtho(-1.0 * width / height, 1.0 * width / height, -1.0, 1.0, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Program utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    
    return 0;
}
