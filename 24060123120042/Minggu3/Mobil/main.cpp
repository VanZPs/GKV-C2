#include <GL/glut.h>
#include <math.h>

#define PI 3.141592653589

// Fungsi untuk menggambar lingkaran terisi
void drawFilledCircle(float radius, int segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * i / segments;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}

// Fungsi untuk menggambar lingkaran outline
void drawCircleOutline(float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * PI * i / segments;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}
// Fungsi untuk menggambar background padang pasir
void drawDesertBackground() {
    // Langit biru
    glBegin(GL_POLYGON);
        glColor3f(0.4f, 0.7f, 1.0f); // Biru di atas
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        
        glColor3f(0.7f, 0.85f, 1.0f); // Biru muda di bawah (horizon)
        glVertex2f(1.0f, -0.2f);
        glVertex2f(-1.0f, -0.2f);
    glEnd();
    
    // Padang pasir (tanah)
    glBegin(GL_POLYGON);
        glColor3f(0.9f, 0.8f, 0.5f); // Pasir di atas
        glVertex2f(-1.0f, -0.2f);
        glVertex2f(1.0f, -0.2f);
        
        glColor3f(0.8f, 0.7f, 0.4f); // Pasir lebih gelap di bawah
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

}

// Fungsi untuk menggambar ban dengan ring pada velg dan gear
void drawWheel(float radius) {
    // Ban (hitam diisi)
    glColor3f(0.2f, 0.2f, 0.2f);
    drawFilledCircle(radius, 100);
    
    // Velg (abu-abu)
    glColor3f(0.7f, 0.7f, 0.7f);
    drawFilledCircle(radius * 0.6f, 100);
    
    // Ring untuk velg (outline hitam)
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.0f);
    drawCircleOutline(radius * 0.7f, 100);
    drawCircleOutline(radius * 0.5f, 100);
    
    // Hub cap (abu-abu gelap)
    glColor3f(0.4f, 0.4f, 0.4f);
    drawFilledCircle(radius * 0.25f, 100);
    
    // Ring untuk hub cap
    glColor3f(0.2f, 0.2f, 0.2f);
    drawCircleOutline(radius * 0.25f, 100);
    
    // Tambahkan gear pada ban
    int numGears = 12;
    float gearLength = radius * 0.15f;
    
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < numGears; i++) {
        float theta = 2.0f * PI * i / numGears;
        float x1 = radius * cos(theta);
        float y1 = radius * sin(theta);
        float x2 = (radius - gearLength) * cos(theta);
        float y2 = (radius - gearLength) * sin(theta);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
}

// Fungsi untuk menggambar body utama mobil 
void drawMainBody() {
    // Body utama merah
    glColor3f(0.9f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
        // Bagian bawah
        glVertex2f(-0.5f, -0.1f);  // Belakang bawah
        
        // Bagian depan dengan kurva
        glVertex2f(0.4f, -0.1f);   // Mendekati depan bawah
        glVertex2f(0.5f, -0.05f);  // Kurva depan bawah
        glVertex2f(0.5f, 0.15f);   // Kurva depan atas
        glVertex2f(0.4f, 0.2f);    // Mendekati depan atas
        
        // Bagian atas
        glVertex2f(-0.5f, 0.2f);   // Belakang atas
    glEnd();
    
    // Tambahan body bagian belakang 
    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, -0.1f);  // Belakang bawah
        glVertex2f(-0.5f, 0.2f);   // Belakang atas
        glVertex2f(-0.55f, 0.15f); // Kurva belakang atas
        glVertex2f(-0.55f, -0.05f);// Kurva belakang bawah
    glEnd();
    
    // Motif garis tebal pada body
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(4.0f);
    // Garis horizontal tengah
    glBegin(GL_LINES);
        glVertex2f(-0.5f, 0.05f);
        glVertex2f(0.4f, 0.05f);
    glEnd();
    
    // Garis horizontal bawah
    glBegin(GL_LINES);
        glVertex2f(-0.45f, -0.05f);
        glVertex2f(0.35f, -0.05f);
    glEnd();
    
    // Garis pemisah pintu
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        // Garis pemisah pintu depan dan belakang
        glVertex2f(-0.2f, -0.1f);
        glVertex2f(-0.2f, 0.2f);
    glEnd();
    
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        // Garis pemisah pintu depan dan belakang
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, 0.2f);
    glEnd();

    // Gagang pintu 
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(8.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.18f, 0.1f);
        glVertex2f(-0.09f, 0.1f);
    glEnd();
    
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(20.0f);
    glBegin(GL_LINES);
        glVertex2f(0.17f, 0.13f);
        glVertex2f(0.13f, 0.13f);
    glEnd();
    
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(20.0f);
    glBegin(GL_LINES);
        glVertex2f(0.17f, -0.03f);
        glVertex2f(0.13f, -0.03f);
    glEnd();
    
    // Grille depan
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(0.45f, -0.1f);
        glVertex2f(0.5f, -0.1f);
        glVertex2f(0.5f, 0.15f);
        glVertex2f(0.45f, 0.15f);
    glEnd();
    
    // Garis-garis pada grille
    glColor3f(0.6f, 0.6f, 0.6f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 9; i++) {
        float y = 0.15f - i * 0.03f;
        glVertex2f(0.45f, y);
        glVertex2f(0.5f, y);
    }
    glEnd();
    
    // Lampu belakang
    glColor3f(0.7f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.55f, 0.0f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(-0.5f, 0.1f);
        glVertex2f(-0.55f, 0.1f);
    glEnd();
    
    // Outline lampu belakang
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.55f, 0.0f);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(-0.5f, 0.1f);
        glVertex2f(-0.55f, 0.1f);
    glEnd();
}

// Fungsi untuk menggambar bagian atas (trapesium) - transparan
void drawTopCabin() {
    // Frame cabin utama
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(7.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5f, 0.2f);   // Belakang bawah
        glVertex2f(0.25f, 0.2f);   // Depan bawah
        glVertex2f(0.18f, 0.5f);   // Depan atas
        glVertex2f(-0.4f, 0.5f);   // Belakang atas
    glEnd();
    
    // Trapesium dalam (sisi lain)
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(10.0f);  // Lebih tebal untuk trapesium dalam
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.35f, 0.20f);  // Belakang bawah
        glVertex2f(0.15f, 0.20f);  // Depan bawah
        glVertex2f(0.12f, 0.44f);  // Depan atas
        glVertex2f(-0.30f, 0.44f); // Belakang atas
    glEnd();
    
    glLineWidth(10.0f);
    glBegin(GL_LINES);
        // Tiang depan
        glVertex2f(0.25f, 0.2f);   // Trapesium luar bawah
        glVertex2f(0.15f, 0.23f);  // Trapesium dalam bawah
        
        glVertex2f(0.18f, 0.5f);   // Trapesium luar atas
        glVertex2f(0.12f, 0.47f);  // Trapesium dalam atas
    glEnd();
    
}

// Fungsi untuk menggambar kaca depan
void drawWindshield() {
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.15f, 0.2f);    // Bawah kiri
        glVertex2f(0.25f, 0.2f);   // Bawah kanan
        glVertex2f(0.18f, 0.5f);   // Atas kanan
        glVertex2f(0.1f, 0.5f);    // Atas kiri
    glEnd();
    
    // Frame kaca
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.15f, 0.2f);
        glVertex2f(0.25f, 0.2f);
        glVertex2f(0.18f, 0.5f);
        glVertex2f(0.1f, 0.5f);
    glEnd();
}

// Fungsi untuk menggambar roll bar
void drawRollBar() {
    glLineWidth(3.5f);
    glColor3f(0.1f, 0.1f, 0.1f);
    
    // Rangka utama
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.4f, 0.5f);   // Belakang kiri
        glVertex2f(-0.4f, 0.55f);  // Belakang atas
        glVertex2f(0.18f, 0.55f);  // Depan atas
        glVertex2f(0.18f, 0.5f);   // Depan kanan
    glEnd();
    
    // Garis miring pertama
    glLineWidth(15.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.4f, 0.5f);    // Titik awal di pojok kiri atas trapesium luar
        glVertex2f(-0.2f, 0.2f);    // Titik akhir di bawah
    glEnd();

    // Garis miring kedua 
    glLineWidth(15.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.4f, 0.5f);    // Titik awal di pojok kiri atas trapesium luar
        glVertex2f(-0.30f, 0.43f);  // Titik akhir 
    glEnd();
}

// Fungsi untuk menggambar lampu
void drawLights() {
    // Lingkaran utama (lampu depan)
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
        glTranslatef(0.2f, 0.52f, 0.0f);
        drawFilledCircle(0.05f, 100);
    glPopMatrix();
    
    // Lingkaran putih di ujung kanan 
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
        glTranslatef(0.23f, 0.52f, 0.0f);
        drawFilledCircle(0.04f, 100);
    glPopMatrix();
    
    // Persegi panjang di kiri lingkaran 
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(0.05f, 0.50f);
        glVertex2f(0.15f, 0.50f);
        glVertex2f(0.15f, 0.54f);
        glVertex2f(0.05f, 0.54f);
    glEnd();
    
    // Outline untuk persegi panjang
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.05f, 0.50f);
        glVertex2f(0.15f, 0.50f);
        glVertex2f(0.15f, 0.54f);
        glVertex2f(0.05f, 0.54f);
    glEnd();
}

// Fungsi untuk menggambar lengkungan antara body dan ban
void drawWheelArches() {
    // Lengkungan atas ban belakang
    glColor3f(0.85f, 0.18f, 0.1f);
    glBegin(GL_POLYGON);
        // Setengah lingkaran untuk lengkungan
        for (int i = 0; i <= 180; i += 10) {
            float theta = PI * i / 180.0f;
            glVertex2f(-0.35f + 0.15f * cos(theta), -0.15f + 0.15f * sin(theta));
        }
        glVertex2f(-0.5f, -0.15f);
        glVertex2f(-0.5f, -0.3f);
        glVertex2f(-0.2f, -0.3f);
        glVertex2f(-0.2f, -0.15f);
    glEnd();
    
    // Lengkungan atas ban depan
    glBegin(GL_POLYGON);
        // Setengah lingkaran untuk lengkungan
        for (int i = 0; i <= 180; i += 10) {
            float theta = PI * i / 180.0f;
            glVertex2f(0.35f + 0.15f * cos(theta), -0.15f + 0.15f * sin(theta));
        }
        glVertex2f(0.5f, -0.15f);
        glVertex2f(0.5f, -0.3f);
        glVertex2f(0.2f, -0.3f);
        glVertex2f(0.2f, -0.15f);
    glEnd();
}

// Fungsi untuk menggambar knalpot 
void drawExhaust() {
    // Warna knalpot putih
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        // Ukuran diperbesar
        glVertex2f(0.05f, -0.12f);
        glVertex2f(-0.15f, -0.12f);
        glVertex2f(-0.15f, -0.22f);
        glVertex2f(0.05f, -0.22f);
    glEnd();
    
    // Outline knalpot
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.05f, -0.12f);
        glVertex2f(-0.15f, -0.12f);
        glVertex2f(-0.15f, -0.22f);
        glVertex2f(0.05f, -0.22f);
    glEnd();
    
    // Kotak kecil di ujung knalpot
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.15f, -0.14f);
        glVertex2f(-0.20f, -0.14f);
        glVertex2f(-0.20f, -0.2f);
        glVertex2f(-0.15f, -0.2f);
    glEnd();
    
    // Outline kotak ujung knalpot
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.15f, -0.14f);
        glVertex2f(-0.20f, -0.14f);
        glVertex2f(-0.20f, -0.2f);
        glVertex2f(-0.15f, -0.2f);
    glEnd();
    
    // Bintik-bintik lingkaran kecil pada knalpot
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
        glTranslatef(-0.02f, -0.17f, 0.0f);
        drawFilledCircle(0.015f, 20);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-0.07f, -0.17f, 0.0f);
        drawFilledCircle(0.015f, 20);
    glPopMatrix();
    
    glPushMatrix();
        glTranslatef(-0.12f, -0.17f, 0.0f);
        drawFilledCircle(0.015f, 20);
    glPopMatrix();
}

void drawFootStep() {
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.3f, -0.10f);
        glVertex2f(0.3f, -0.10f);
        glVertex2f(0.3f, -0.15f);
        glVertex2f(-0.3f, -0.15f);
    glEnd();
    
    // Detail perforasi pada foot step
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 10; i++) {
        float x = -0.27f + i * 0.06f;
        glVertex2f(x, -0.10f);
        glVertex2f(x, -0.15f);
    }
    glEnd();
    
    // Outline untuk foot step
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.3f, -0.10f);
        glVertex2f(0.3f, -0.10f);
        glVertex2f(0.3f, -0.15f);
        glVertex2f(-0.3f, -0.15f);
    glEnd();
}

void drawJeep() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Background padang pasir dengan langit biru
    drawDesertBackground();
    
    // Lengkungan antara body dan ban
    drawWheelArches();
    
    // Ban belakang
    glPushMatrix();
        glTranslatef(-0.35f, -0.3f, 0.0f);
        drawWheel(0.15f);
    glPopMatrix();
    
    // Ban depan
    glPushMatrix();
        glTranslatef(0.35f, -0.3f, 0.0f);
        drawWheel(0.15f);
    glPopMatrix();
    
    drawFootStep();
    
    drawMainBody();
    
    // Bagian atas trapesium (transparan)
    drawTopCabin();
    
    // Kaca depan
    drawWindshield();
    
    // Roll bar / Frame atap
    drawRollBar();
    
    // Knalpot yang diperbesar
    glPushMatrix();
        glTranslatef(-0.5f, 0.0f, 0.0f);
        drawExhaust();
    glPopMatrix();
    
    drawLights();
    
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Jeep in Desert");
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    
    glutDisplayFunc(drawJeep);
    glutMainLoop();
    
    return 0;
}
