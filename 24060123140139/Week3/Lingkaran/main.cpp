#include <GL/glut.h>
#include <math.h>

// Mendefinisikan konstanta PI
#define PI 3.14159265358979323846

// Fungsi untuk menggambar lingkaran
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

// Fungsi display
void display() {
    // Membersihkan buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Reset transformasi
    glLoadIdentity();
    
    // Set warna hitam untuk semua lingkaran
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // Lingkaran pertama (kiri atas)
    glPushMatrix();
        glTranslatef(-0.5f, 0.5f, 0.0f);
        drawCircle(0.0f, 0.0f, 0.2f, 100);
    glPopMatrix();
    
    // Lingkaran kedua (kanan atas)
    glPushMatrix();
        glTranslatef(0.5f, 0.5f, 0.0f);
        drawCircle(0.0f, 0.0f, 0.2f, 100);
    glPopMatrix();
    
    // Lingkaran ketiga (kiri bawah)
    glPushMatrix();
        glTranslatef(-0.5f, -0.5f, 0.0f);
        drawCircle(0.0f, 0.0f, 0.2f, 100);
    glPopMatrix();
    
    // Lingkaran keempat (kanan bawah)
    glPushMatrix();
        glTranslatef(0.5f, -0.5f, 0.0f);
        drawCircle(0.0f, 0.0f, 0.2f, 100);
    glPopMatrix();
    
    // Menampilkan hasil
    glFlush();
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

// Program utama
int main(int argc, char** argv) {
    // Inisialisasi GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Empat Lingkaran Hitam dengan OpenGL");
    
    // Mengatur warna background (putih)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Mendaftarkan fungsi callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    // Memulai loop utama GLUT
    glutMainLoop();
    
    return 0;
}
