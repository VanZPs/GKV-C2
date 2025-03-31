#include <GL/glut.h>
#include <math.h>

// Mendefinisikan konstanta PI
#define PI 3.14159265358979323846

// Variabel global untuk animasi
float carPosition = -1.0f;
float wheelRotation = 0.0f;

// Fungsi untuk menggambar lingkaran (untuk roda)
void drawCircle(float cx, float cy, float radius, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * float(i) / float(num_segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Fungsi untuk menggambar jari-jari roda
void drawWheelSpokes(float cx, float cy, float radius) {
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float theta = 2.0f * PI * float(i) / 8.0f;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(cx, cy);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Fungsi untuk menggambar badan mobil
void drawCarBody() {
    // Badan utama mobil (persegi panjang)
    glColor3f(0.8f, 0.2f, 0.2f); // Merah
    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.5f, 0.25f);
        glVertex2f(-0.5f, 0.25f);
    glEnd();
    
    // Kabin mobil (trapesium)
    glColor3f(0.2f, 0.2f, 0.8f); // Biru
    glBegin(GL_POLYGON);
        glVertex2f(-0.3f, 0.25f);
        glVertex2f(0.3f, 0.25f);
        glVertex2f(0.2f, 0.4f);
        glVertex2f(-0.2f, 0.4f);
    glEnd();
    
    // Kaca depan
    glColor3f(0.8f, 0.8f, 1.0f); // Biru muda
    glBegin(GL_POLYGON);
        glVertex2f(0.2f, 0.25f);
        glVertex2f(0.3f, 0.25f);
        glVertex2f(0.2f, 0.4f);
    glEnd();
    
    // Kaca belakang
    glBegin(GL_POLYGON);
        glVertex2f(-0.3f, 0.25f);
        glVertex2f(-0.2f, 0.25f);
        glVertex2f(-0.2f, 0.4f);
    glEnd();
    
    // Lampu depan
    glColor3f(1.0f, 1.0f, 0.0f); // Kuning
    glBegin(GL_POLYGON);
        glVertex2f(0.45f, 0.05f);
        glVertex2f(0.5f, 0.05f);
        glVertex2f(0.5f, 0.15f);
        glVertex2f(0.45f, 0.15f);
    glEnd();
    
    // Lampu belakang
    glColor3f(1.0f, 0.0f, 0.0f); // Merah terang
    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, 0.05f);
        glVertex2f(-0.45f, 0.05f);
        glVertex2f(-0.45f, 0.15f);
        glVertex2f(-0.5f, 0.15f);
    glEnd();
    
    // Plat nomor
    glColor3f(1.0f, 1.0f, 1.0f); // Putih
    glBegin(GL_POLYGON);
        glVertex2f(-0.15f, 0.05f);
        glVertex2f(0.15f, 0.05f);
        glVertex2f(0.15f, 0.15f);
        glVertex2f(-0.15f, 0.15f);
    glEnd();
    
    // Garis plat nomor
    glColor3f(0.0f, 0.0f, 0.0f); // Hitam
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);
    glEnd();
}

// Fungsi untuk menggambar roda
void drawWheel(float x, float y, float radius) {
    // Ban luar (hitam)
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle(x, y, radius, 30);
    
    // Velg (abu-abu)
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(x, y, radius * 0.7f, 30);
    
    // Jari-jari roda (hitam)
    glColor3f(0.1f, 0.1f, 0.1f);
    drawWheelSpokes(x, y, radius * 0.7f);
    
    // Hub roda (hitam)
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle(x, y, radius * 0.2f, 20);
}

// Fungsi display
void display() {
    // Membersihkan buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Reset transformasi
    glLoadIdentity();
    
    // Translasi seluruh mobil
    glTranslatef(carPosition, 0.0f, 0.0f);
    
    // Menggambar badan mobil
    glPushMatrix();
        drawCarBody();
    glPopMatrix();
    
    // Menggambar roda depan dengan rotasi
    glPushMatrix();
        glTranslatef(0.3f, -0.05f, 0.0f);
        glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
        drawWheel(0.0f, 0.0f, 0.12f);
    glPopMatrix();
    
    // Menggambar roda belakang dengan rotasi
    glPushMatrix();
        glTranslatef(-0.3f, -0.05f, 0.0f);
        glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
        drawWheel(0.0f, 0.0f, 0.12f);
    glPopMatrix();
    
    // Menggambar jalan
    glLoadIdentity();
    glColor3f(0.2f, 0.2f, 0.2f); // Abu-abu gelap
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.2f);
        glVertex2f(1.0f, -0.2f);
        glVertex2f(1.0f, -0.4f);
        glVertex2f(-1.0f, -0.4f);
    glEnd();
    
    // Garis jalan
    glColor3f(1.0f, 1.0f, 1.0f); // Putih
    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.8f, -0.3f);
        glVertex2f(-0.6f, -0.3f);
        
        glVertex2f(-0.4f, -0.3f);
        glVertex2f(-0.2f, -0.3f);
        
        glVertex2f(0.0f, -0.3f);
        glVertex2f(0.2f, -0.3f);
        
        glVertex2f(0.4f, -0.3f);
        glVertex2f(0.6f, -0.3f);
        
        glVertex2f(0.8f, -0.3f);
        glVertex2f(1.0f, -0.3f);
    glEnd();
    
    // Menampilkan hasil (double buffer)
    glutSwapBuffers();
}

// Fungsi reshape
void reshape(int width, int height) {
    // Mengatur viewport
    glViewport(0, 0, width, height);
    
    // Mengatur proyeksi
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Mengatur aspek rasio yang sesuai
    if (width <= height)
        glOrtho(-1.0, 1.0, -1.0 * height / width, 1.0 * height / width, -1.0, 1.0);
    else
        glOrtho(-1.0 * width / height, 1.0 * width / height, -1.0, 1.0, -1.0, 1.0);
    
    // Kembali ke mode modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Fungsi timer untuk animasi
void timer(int value) {
    // Update posisi mobil
    carPosition += 0.01f;
    if (carPosition > 1.5f) {
        carPosition = -1.5f;
    }
    
    // Update rotasi roda
    wheelRotation -= 5.0f;
    if (wheelRotation < -360.0f) {
        wheelRotation += 360.0f;
    }
    
    // Meminta GLUT untuk menggambar ulang
    glutPostRedisplay();
    
    // Memanggil timer lagi setelah 16ms (sekitar 60 FPS)
    glutTimerFunc(16, timer, 0);
}

// Program utama
int main(int argc, char** argv) {
    // Inisialisasi GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil 2D dengan OpenGL");
    
    // Mengatur warna background (biru muda untuk langit)
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    
    // Mendaftarkan fungsi callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    // Memulai timer untuk animasi
    glutTimerFunc(0, timer, 0);
    
    // Memulai loop utama GLUT
    glutMainLoop();
    
    return 0;
}
