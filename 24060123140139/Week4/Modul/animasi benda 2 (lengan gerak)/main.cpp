#include <GL/glut.h>

// Variabel untuk rotasi shoulder dan elbow
static int shoulder = 0, elbow = 0;

// Fungsi inisialisasi OpenGL
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Set warna latar belakang (hitam)
    glShadeModel(GL_FLAT);  // Set shading model (flat shading)
}

// Fungsi untuk menggambar objek
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Bersihkan buffer warna
    glPushMatrix();  // Simpan keadaan matriks saat ini

    // Transformasi shoulder
    glTranslatef(-1.0, 0.0, 0.0);  // Geser ke kiri
    glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0);  // Rotasi shoulder
    glTranslatef(1.0, 0.0, 0.0);  // Geser kembali ke kanan

    glPushMatrix();  // Simpan keadaan matriks untuk elbow
    glScalef(2.0, 0.4, 1.0);  // Skala objek untuk shoulder
    glutWireCube(1.0);  // Gambar wireframe kubus
    glPopMatrix();  // Kembalikan keadaan matriks

    // Transformasi elbow
    glTranslatef(1.0, 0.0, 0.0);  // Geser ke kanan
    glRotatef((GLfloat) elbow, 0.0, 0.0, 1.0);  // Rotasi elbow
    glTranslatef(1.0, 0.0, 0.0);  // Geser lagi ke kanan

    glPushMatrix();  // Simpan keadaan matriks untuk elbow
    glScalef(2.0, 0.4, 1.0);  // Skala objek untuk elbow
    glutWireCube(1.0);  // Gambar wireframe kubus
    glPopMatrix();  // Kembalikan keadaan matriks

    glPopMatrix();  // Kembalikan keadaan matriks sebelumnya
    glutSwapBuffers();  // Tukar buffer untuk rendering ganda
}

// Fungsi untuk menangani perubahan ukuran jendela
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);  // Sesuaikan viewport
    glMatrixMode(GL_PROJECTION);  // Pilih mode proyeksi
    glLoadIdentity();  // Reset proyeksi
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);  // Atur perspektif
    glMatrixMode(GL_MODELVIEW);  // Kembali ke mode modelview
    glLoadIdentity();  // Reset modelview matrix
    glTranslatef(0.0, 0.0, -5.0);  // Geser objek ke dalam
}

// Fungsi untuk menangani input keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':  // Rotasi shoulder ke kanan
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();  // Meminta rendering ulang
            break;
        case 'S':  // Rotasi shoulder ke kiri
            shoulder = (shoulder - 5) % 360;
            glutPostRedisplay();  // Meminta rendering ulang
            break;
        case 'e':  // Rotasi elbow ke kanan
            elbow = (elbow + 5) % 360;
            glutPostRedisplay();  // Meminta rendering ulang
            break;
        case 'E':  // Rotasi elbow ke kiri
            elbow = (elbow - 5) % 360;
            glutPostRedisplay();  // Meminta rendering ulang
            break;
        case 27:  // Tombol ESC untuk keluar dari program
            exit(0);
            break;
        default:
            break;
    }
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);  // Inisialisasi GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Mode ganda dan RGB
    glutInitWindowSize(700, 600);  // Ukuran jendela
    glutInitWindowPosition(100, 100);  // Posisi jendela
    glutCreateWindow(argv[0]);  // Nama jendela

    init();  // Panggil fungsi inisialisasi

    glutDisplayFunc(display);  // Daftarkan fungsi display untuk rendering
    glutReshapeFunc(reshape);  // Daftarkan fungsi reshape untuk perubahan ukuran jendela
    glutKeyboardFunc(keyboard);  // Daftarkan fungsi keyboard untuk input pengguna

    glutMainLoop();  // Masuk ke loop utama GLUT
    return 0;
}

