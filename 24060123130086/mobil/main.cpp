#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Posisi mobil
float carPositionX = 0.0f;


// Function prototypes
void display(void);
void reshape(int w, int h);
void drawCar(void);
void drawWheel(float x, float y);
void drawRoad(void);
void drawBackground(void);

void drawBackground(void) {
    // Background berwarna malam biru gradasi
    glBegin(GL_QUADS);
        glColor3f(0.05f, 0.05f, 0.2f);
        glVertex2f(-400.0f, 300.0f);
        glVertex2f(400.0f, 300.0f);
        glColor3f(0.1f, 0.1f, 0.3f);
        glVertex2f(400.0f, -50.0f);
        glVertex2f(-400.0f, -50.0f);
    glEnd();
    
    // bintang bintang
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(1.5f);
    glBegin(GL_POINTS);
        // Add some scattered stars
        for(int i = 0; i < 100; i++) {
            float x = -380.0f + (i * 7.8f);
            float y = 50.0f + (i % 15) * 16.0f;
            glVertex2f(x, y);
        }
    glEnd();
    
    // Bulan (Lingkaran)
    glColor3f(0.95f, 0.95f, 0.8f);
    glPushMatrix();
    glTranslatef(300.0f, 200.0f, 0.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float radian = i * (3.14159f/180.0f);
        glVertex2f(cos(radian) * 40.0f, sin(radian) * 40.0f);
    }
    glEnd();
    
    // Detail bulan
    glColor3f(0.85f, 0.85f, 0.7f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float radian = i * (3.14159f/180.0f);
        glVertex2f(cos(radian) * 8.0f + 15.0f, sin(radian) * 8.0f + 10.0f);
    }
    glEnd();
    
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float radian = i * (3.14159f/180.0f);
        glVertex2f(cos(radian) * 5.0f - 10.0f, sin(radian) * 5.0f - 5.0f);
    }
    glEnd();
    
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float radian = i * (3.14159f/180.0f);
        glVertex2f(cos(radian) * 6.0f - 20.0f, sin(radian) * 6.0f + 20.0f);
    }
    glEnd();
    glPopMatrix();
    
    // Gunung
    glColor3f(0.15f, 0.15f, 0.25f);
    glBegin(GL_TRIANGLES);
        // Gunung Tengah
        glVertex2f(-100.0f, -50.0f);
        glVertex2f(50.0f, 180.0f);
        glVertex2f(200.0f, -50.0f);
        
        // Gunung kecil
        glVertex2f(-350.0f, -50.0f);
        glVertex2f(-200.0f, 100.0f);
        glVertex2f(-50.0f, -50.0f);
        
        glVertex2f(150.0f, -50.0f);
        glVertex2f(300.0f, 80.0f);
        glVertex2f(450.0f, -50.0f);
    glEnd();
}

void drawRoad(void) {
    // Jalan warna abu
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-400.0f, -100.0f);
        glVertex2f(400.0f, -100.0f);
        glVertex2f(400.0f, -200.0f);
        glVertex2f(-400.0f, -200.0f);
    glEnd();
    
    // Pinggiran jalan warna cokelat
    glColor3f(0.6f, 0.5f, 0.4f);
    glBegin(GL_QUADS);
        // Bagian Atas
        glVertex2f(-400.0f, -90.0f);
        glVertex2f(400.0f, -90.0f);
        glVertex2f(400.0f, -100.0f);
        glVertex2f(-400.0f, -100.0f);
        
        // Bagian Bawah
        glVertex2f(-400.0f, -200.0f);
        glVertex2f(400.0f, -200.0f);
        glVertex2f(400.0f, -210.0f);
        glVertex2f(-400.0f, -210.0f);
    glEnd();
    
    // Pinggiran rumput warna hijau
    glColor3f(0.3f, 0.7f, 0.2f);
    glBegin(GL_QUADS);
        // Bagian Atas
        glVertex2f(-400.0f, -50.0f);
        glVertex2f(400.0f, -50.0f);
        glVertex2f(400.0f, -90.0f);
        glVertex2f(-400.0f, -90.0f);
        
        // Bagian Bawah
        glVertex2f(-400.0f, -210.0f);
        glVertex2f(400.0f, -210.0f);
        glVertex2f(400.0f, -300.0f);
        glVertex2f(-400.0f, -300.0f);
    glEnd();
    
    // Marka jalan warna putih
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        for(int x = -380; x < 400; x += 40) {
            glVertex2f((float)x, -150.0f);
            glVertex2f((float)x + 20.0f, -150.0f);
        }
    glEnd();
}

// Menggambar roda
void drawWheel(float x, float y) {
    glColor3f(0.1f, 0.1f, 0.1f);
    
    glPushMatrix();
    
    glTranslatef(x, y, 0.0f);

    
    // Lingkaran hitam untuk roda mobil
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 5) {
        float radian = i * (3.14159f/180.0f);
        glVertex2f(cos(radian) * 20.0f, sin(radian) * 20.0f);
    }
    glEnd();
    
    // Menggambar velg mobil
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 15) {
        float radian = i * (3.14159f/180.0f);
        glVertex2f(cos(radian) * 10.0f, sin(radian) * 10.0f);
    }
    glEnd();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    for(int i = 0; i < 360; i += 45) {
        float radian = i * (3.14159f/180.0f);
        glBegin(GL_LINES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(cos(radian) * 18.0f, sin(radian) * 18.0f);
        glEnd();
    }
    
    glPopMatrix();
}

// Menggambar Mobil
void drawCar(void) {
    glLoadIdentity();
    glTranslatef(carPositionX, -150.0f, 0.0f);
    
    //Badan mobil warna oranye
    glColor3f(0.99f, 0.47f, 0.0f);
    glBegin(GL_POLYGON);
    
    glVertex2f(0.0f, 0.0f);
    glVertex2f(200.0f, 0.0f);
    glVertex2f(200.0f, 40.0f);
    glVertex2f(175.0f, 40.0f);
    glVertex2f(150.0f, 70.0f);
    glVertex2f(30.0f, 70.0f);
    glVertex2f(15.0f, 40.0f);
    glVertex2f(0.0f, 40.0f);
    glEnd();
    
    // Jendela depan mobil
    glColor3f(0.0f, 0.32f, 0.75f);
    glBegin(GL_POLYGON);
    glVertex2f(45.0f, 40.0f);
    glVertex2f(95.0f, 40.0f);
    glVertex2f(85.0f, 65.0f);
    glVertex2f(60.0f, 65.0f);
    glEnd();
    
    // Jendela belakang mobil berwarna biru
    glColor3f(0.0f, 0.32f, 0.75f);
    glBegin(GL_POLYGON);
    glVertex2f(105.0f, 40.0f);
    glVertex2f(150.0f, 40.0f);
    glVertex2f(130.0f, 65.0f);
    glVertex2f(110.0f, 65.0f);
    glEnd();
    
    // Pembagi jendela warna hitam
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(100.0f, 40.0f);
    glVertex2f(97.0f, 65.0f);
    glEnd();
    
    // Detail berwarna pink
    glColor3f(0.99f, 0.09f, 0.49f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(25.0f, 25.0f);
    glVertex2f(50.0f, 25.0f);
    glVertex2f(70.0f, 15.0f);
    glVertex2f(100.0f, 35.0f);
    glVertex2f(130.0f, 15.0f);
    glVertex2f(175.0f, 25.0f);
    glEnd();
    
    // Detail mobil dan outline
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(200.0f, 0.0f);
    glVertex2f(200.0f, 40.0f);
    glVertex2f(175.0f, 40.0f);
    glVertex2f(150.0f, 70.0f);
    glVertex2f(30.0f, 70.0f);
    glVertex2f(15.0f, 40.0f);
    glVertex2f(0.0f, 40.0f);
    glEnd();
    
    // Outline jendela depan
    glBegin(GL_LINE_LOOP);
    glVertex2f(45.0f, 40.0f);
    glVertex2f(95.0f, 40.0f);
    glVertex2f(85.0f, 65.0f);
    glVertex2f(60.0f, 65.0f);
    glEnd();
    
    // Outliine jendela belakang
    glBegin(GL_LINE_LOOP);
    glVertex2f(105.0f, 40.0f);
    glVertex2f(150.0f, 40.0f);
    glVertex2f(130.0f, 65.0f);
    glVertex2f(110.0f, 65.0f);
    glEnd();
    
    // Lampu mobil
        // Lampu depan
        glColor3f(1.0f, 1.0f, 0.8f);
        glBegin(GL_POLYGON);
            glVertex2f(5.0f, 25.0f);
            glVertex2f(15.0f, 25.0f);
            glVertex2f(15.0f, 35.0f);
            glVertex2f(5.0f, 35.0f);
        glEnd();

    // Lampu belakang
            glColor3f(1.0f, 1.0f, 0.8f);
            glBegin(GL_POLYGON);
                glVertex2f(185.0f, 25.0f);
                glVertex2f(195.0f, 25.0f);
                glVertex2f(195.0f, 35.0f);
                glVertex2f(185.0f, 35.0f);
            glEnd();

        // menggambar roda
        drawWheel(40.0f, 0.0f);    // roda depan
        drawWheel(160.0f, 0.0f);   // roda belakang
    }

    void display(void) {

        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        drawBackground();
        drawRoad();
        drawCar();
        glutSwapBuffers();
    }

    void reshape(int w, int h) {
        if (h == 0) h = 1;
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-400.0, 400.0, -300.0, 300.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Mobil ganteng jalan jalan di jepang");
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glutMainLoop();
        return 0;
    }
