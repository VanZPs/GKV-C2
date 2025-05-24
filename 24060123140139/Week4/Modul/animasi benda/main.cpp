#include <GL/glut.h>

// Variabel global untuk rotasi
GLfloat xRotated, yRotated, zRotated;

// Fungsi display untuk menggambar objek
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  // Bersihkan buffer warna
    glLoadIdentity();  // Reset transformasi modelview

    glTranslatef(0.0, 0.0, -4.0);  // Translasikan objek ke dalam layar
    glRotatef(xRotated, 1.0, 0.0, 0.0);  // Rotasi objek pada sumbu X
    glRotatef(yRotated, 0.0, 1.0, 0.0);  // Rotasi objek pada sumbu Y
    glRotatef(zRotated, 0.0, 0.0, 1.0);  // Rotasi objek pada sumbu Z

    glScalef(2.0, 1.0, 1.0);  // Skala objek (lebih lebar pada sumbu X)

    glutWireCube(1.0);  // Gambarkan wireframe kubus
    glFlush();  // Selesaikan rendering
    glutSwapBuffers();  // Tukar buffer (untuk rendering ganda)
}

// Fungsi reshape untuk menangani perubahan ukuran jendela
void Reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  // Cegah pembagian dengan nol

    glMatrixMode(GL_PROJECTION);  // Pilih mode proyeksi
    glLoadIdentity();  // Reset proyeksi
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);  // Tentukan proyeksi perspektif
    glMatrixMode(GL_MODELVIEW);  // Kembali ke mode modelview
    glViewport(0, 0, x, y);  // Sesuaikan ukuran viewport dengan jendela baru
}

// Fungsi idle untuk pembaruan rotasi
void Idle(void)
{
    // Perbarui nilai rotasi setiap kali idle
    xRotated += 0.05;
    yRotated += 0.05;
    zRotated += -0.05;
    Display();  // Panggil fungsi display untuk menggambar objek yang sudah diperbarui
}

// Fungsi utama
int main(int argc, char **argv)
{
    glutInit(&argc, argv);  // Inisialisasi GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Mode buffer ganda dan RGB
    glutInitWindowSize(300, 300);  // Ukuran jendela
    glutCreateWindow("Cube example");  // Nama jendela

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Gambar kubus dengan wireframe (garis)

    xRotated = yRotated = zRotated = 0.0;  // Inisialisasi rotasi
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Set warna latar belakang (hitam)

    glutDisplayFunc(Display);  // Daftarkan fungsi display
    glutReshapeFunc(Reshape);  // Daftarkan fungsi reshape
    glutIdleFunc(Idle);  // Daftarkan fungsi idle untuk pembaruan terus-menerus

    glutMainLoop();  // Mulai loop utama GLUT
    return 0;
}

