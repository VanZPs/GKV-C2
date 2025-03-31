#include <GL/glut.h>
#include <math.h>

// Fungsi untuk menggambar lingkaran
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Fungsi display
void display() {
    // Membersihkan layar
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Menggambar lampu merah di posisi paling atas
    glColor3f(1.0, 0.0, 0.0); // Merah
    drawCircle(0.0, 0.5, 0.15, 100);
    
    // Menggambar lampu kuning di tengah
    glColor3f(1.0, 1.0, 0.0); // Kuning
    drawCircle(0.0, 0.0, 0.15, 100);
    
    // Menggambar lampu hijau di bawah
    glColor3f(0.0, 1.0, 0.0); // Hijau
    drawCircle(0.0, -0.5, 0.15, 100);
    
    // Memastikan semua perintah grafis telah dieksekusi
    glFlush();
}

// Fungsi untuk inisialisasi
void init() {
    // Mengatur warna background menjadi putih
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    // Mengatur proyeksi orthographic
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

// Fungsi utama
int main(int argc, char** argv) {
    // Inisialisasi GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Mengatur ukuran jendela
    glutInitWindowSize(500, 800);
    glutInitWindowPosition(100, 100);
    
    // Membuat jendela dengan judul
    glutCreateWindow("Lingkaran");
    
    // Memanggil fungsi inisialisasi
    init();
    
    // Mendaftarkan fungsi display
    glutDisplayFunc(display);
    
    // Memulai loop utama GLUT
    glutMainLoop();
    
    return 0;
}
