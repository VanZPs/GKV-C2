#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include <cmath>

// Ukuran jendela
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Warna RGB
struct Color {
    float r, g, b;
};

// Warna mobil sport
Color carColor = {0.8f, 0.1f, 0.1f};  // Merah

// Fungsi untuk menggambar roda
void drawWheel(float x, float y, float radius) {
    const int NUM_SEGMENTS = 30;
    float theta = 0;
    float step = 2.0f * M_PI / NUM_SEGMENTS;
    
    // Roda (lingkaran hitam)
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        float px = x + radius * cos(theta);
        float py = y + radius * sin(theta);
        glVertex2f(px, py);
        theta += step;
    }
    glEnd();
    
    // Velg (lingkaran abu-abu)
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        float px = x + (radius * 0.6f) * cos(theta);
        float py = y + (radius * 0.6f) * sin(theta);
        glVertex2f(px, py);
        theta += step;
    }
    glEnd();
    
    // Pusat roda
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        float px = x + (radius * 0.2f) * cos(theta);
        float py = y + (radius * 0.2f) * sin(theta);
        glVertex2f(px, py);
        theta += step;
    }
    glEnd();
}

// Fungsi untuk menggambar background Tokyo
void drawTokyoBackground() {
    // Langit malam
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.2f);  // Biru gelap
    glVertex2f(0, WINDOW_HEIGHT);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT);
    glColor3f(0.2f, 0.0f, 0.4f);  // Ungu tua (Tokyo night gradient)
    glVertex2f(WINDOW_WIDTH, 0);
    glVertex2f(0, 0);
    glEnd();
    
    // Bintang-bintang
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 100; i++) {
        float x = (float)(rand() % WINDOW_WIDTH);
        float y = (float)(rand() % WINDOW_HEIGHT) * 0.7f + WINDOW_HEIGHT * 0.3f;
        glVertex2f(x, y);
    }
    glEnd();
    
    // Bulan
    glColor3f(0.9f, 0.9f, 0.8f);
    const int NUM_SEGMENTS = 30;
    float moonRadius = 40.0f;
    float moonX = WINDOW_WIDTH * 0.8f;
    float moonY = WINDOW_HEIGHT * 0.8f;
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        float theta = 2.0f * M_PI * i / NUM_SEGMENTS;
        float x = moonX + moonRadius * cos(theta);
        float y = moonY + moonRadius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
    
    // Gedung-gedung Tokyo
    // Gedung kecil di latar belakang
    for (int i = 0; i < 20; i++) {
        float x = i * 40.0f;
        float height = 100.0f + rand() % 100;
        float width = 35.0f;
        
        // Badan gedung
        glColor3f(0.1f, 0.1f, 0.2f);
        glBegin(GL_POLYGON);
        glVertex2f(x, WINDOW_HEIGHT/2 - 50);
        glVertex2f(x + width, WINDOW_HEIGHT/2 - 50);
        glVertex2f(x + width, WINDOW_HEIGHT/2 - 50 + height);
        glVertex2f(x, WINDOW_HEIGHT/2 - 50 + height);
        glEnd();
        
        // Jendela-jendela
        glColor3f(1.0f, 1.0f, 0.4f);
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < height/20; k++) {
                if (rand() % 4 > 0) {  // 75% chance for a window to be lit
                    glBegin(GL_QUADS);
                    glVertex2f(x + 5 + j * 6, WINDOW_HEIGHT/2 - 40 + k * 20);
                    glVertex2f(x + 9 + j * 6, WINDOW_HEIGHT/2 - 40 + k * 20);
                    glVertex2f(x + 9 + j * 6, WINDOW_HEIGHT/2 - 30 + k * 20);
                    glVertex2f(x + 5 + j * 6, WINDOW_HEIGHT/2 - 30 + k * 20);
                    glEnd();
                }
            }
        }
    }
    
    // Tokyo Tower
    glColor3f(0.8f, 0.2f, 0.2f);  // Merah khas Tokyo Tower
    glBegin(GL_POLYGON);
    glVertex2f(200, WINDOW_HEIGHT/2 - 50);
    glVertex2f(250, WINDOW_HEIGHT/2 - 50);
    glVertex2f(235, WINDOW_HEIGHT/2 + 200);
    glVertex2f(215, WINDOW_HEIGHT/2 + 200);
    glEnd();
    
    // Puncak Tokyo Tower
    glBegin(GL_POLYGON);
    glVertex2f(215, WINDOW_HEIGHT/2 + 200);
    glVertex2f(235, WINDOW_HEIGHT/2 + 200);
    glVertex2f(225, WINDOW_HEIGHT/2 + 250);
    glEnd();
    
    // Lampu Tokyo Tower
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(225, WINDOW_HEIGHT/2 + 250);
    glEnd();

}

// Gambar jalan tol
void drawHighway() {
    // Jalan utama (lebih lebar dan memenuhi sampai ke frame bawah)
    glColor3f(0.2f, 0.2f, 0.2f);  // Abu-abu aspal
    glBegin(GL_POLYGON);
    glVertex2f(0, WINDOW_HEIGHT/2 - 50);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT/2 - 50);
    glVertex2f(WINDOW_WIDTH, 0);  // Sampai ke bawah frame
    glVertex2f(0, 0);  // Sampai ke bawah frame
    glEnd();
    
    // Pembatas jalan (concrete divider)
    glColor3f(0.7f, 0.7f, 0.7f);  // Abu-abu beton
    glBegin(GL_POLYGON);
    glVertex2f(0, WINDOW_HEIGHT/2 - 50);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT/2 - 50);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT/2 - 60);
    glVertex2f(0, WINDOW_HEIGHT/2 - 60);
    glEnd();
    
    // Reflective barriers di pembatas
    glColor3f(1.0f, 0.8f, 0.0f);  // Kuning
    for (int i = 20; i < WINDOW_WIDTH; i += 100) {
        glBegin(GL_POLYGON);
        glVertex2f(i, WINDOW_HEIGHT/2 - 50);
        glVertex2f(i + 10, WINDOW_HEIGHT/2 - 50);
        glVertex2f(i + 10, WINDOW_HEIGHT/2 - 45);
        glVertex2f(i, WINDOW_HEIGHT/2 - 45);
        glEnd();
    }
    
    // Marka jalur jalan (3 jalur)
    glColor3f(1.0f, 1.0f, 1.0f);  // Putih
    glLineWidth(5.0f);
    
    // Jalur 1 (putus-putus)
    glBegin(GL_LINES);
    for (int i = 0; i < WINDOW_WIDTH; i += 50) {
        glVertex2f(i, WINDOW_HEIGHT/2 - 90);
        glVertex2f(i + 30, WINDOW_HEIGHT/2 - 90);
    }
    glEnd();
    
    // Jalur 2 (putus-putus)
    glBegin(GL_LINES);
    for (int i = 0; i < WINDOW_WIDTH; i += 50) {
        glVertex2f(i + 15, WINDOW_HEIGHT/2 - 140);
        glVertex2f(i + 45, WINDOW_HEIGHT/2 - 140);
    }
    glEnd();
    
    // Bahu jalan (solid line)
    glBegin(GL_LINES);
    glVertex2f(0, WINDOW_HEIGHT/2 - 190);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT/2 - 190);
    glEnd();
    
    // Pagar pembatas di bahu jalan
    glColor3f(0.5f, 0.5f, 0.5f);  // Abu-abu metalik
    for (int i = 0; i < WINDOW_WIDTH; i += 40) {
        // Tiang
        glBegin(GL_LINES);
        glVertex2f(i, WINDOW_HEIGHT/2 - 190);
        glVertex2f(i, WINDOW_HEIGHT/2 - 170);
        glEnd();
    }
    
    // Guardrail
    glBegin(GL_LINES);
    glVertex2f(0, WINDOW_HEIGHT/2 - 175);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT/2 - 175);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2f(0, WINDOW_HEIGHT/2 - 180);
    glVertex2f(WINDOW_WIDTH, WINDOW_HEIGHT/2 - 180);
    glEnd();
}

void drawCustomWheel(float x, float y, float radius) {
    // Constants for wheel design
    float tireWidth = radius * 0.3f;  // Width of the tire
    float rimRadius = radius * 0.7f;  // Radius of the rim
    float innerRadius = radius * 0.4f;  // Radius of the inner part of the rim
    float centerRadius = radius * 0.15f;  // Radius of the wheel center
    int numSpokes = 7;  // Number of spokes for the JDM wheel
    
    // Draw the tire (black)
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
    }
    glEnd();
    
    // Draw the outer rim (silver/chrome)
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + rimRadius * cos(angle), y + rimRadius * sin(angle));
    }
    glEnd();
    
    // Draw the deep dish inner rim (darker silver)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + innerRadius * cos(angle), y + innerRadius * sin(angle));
    }
    glEnd();
    
    // Draw the center cap
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + centerRadius * cos(angle), y + centerRadius * sin(angle));
    }
    glEnd();
    
    // Draw the spokes
    glColor3f(0.7f, 0.7f, 0.7f);
    for (int i = 0; i < numSpokes; i++) {
        float angle1 = (i * 360.0f / numSpokes) * 3.14159f / 180.0f;
        float angle2 = ((i + 0.5f) * 360.0f / numSpokes) * 3.14159f / 180.0f;
        
        // Draw the main spoke
        glBegin(GL_POLYGON);
        // Left edge of spoke
        glVertex2f(x + centerRadius * cos(angle1 - 0.2f),
                  y + centerRadius * sin(angle1 - 0.2f));
        glVertex2f(x + rimRadius * cos(angle1 - 0.1f),
                  y + rimRadius * sin(angle1 - 0.1f));
        
        // Right edge of spoke
        glVertex2f(x + rimRadius * cos(angle1 + 0.1f),
                  y + rimRadius * sin(angle1 + 0.1f));
        glVertex2f(x + centerRadius * cos(angle1 + 0.2f),
                  y + centerRadius * sin(angle1 + 0.2f));
        glEnd();
    }
    
    // Draw the rim lip (chrome/polished)
    glColor3f(0.9f, 0.9f, 0.9f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + rimRadius * cos(angle), y + rimRadius * sin(angle));
    }
    glEnd();
    
    // Draw valve stem
    glColor3f(0.0f, 0.0f, 0.0f);
    float valveAngle = 45.0f * 3.14159f / 180.0f;
    glBegin(GL_POLYGON);
    glVertex2f(x + (rimRadius - 5) * cos(valveAngle),
              y + (rimRadius - 5) * sin(valveAngle));
    glVertex2f(x + (rimRadius + 2) * cos(valveAngle),
              y + (rimRadius + 2) * sin(valveAngle));
    glVertex2f(x + (rimRadius + 2) * cos(valveAngle + 0.05f),
              y + (rimRadius + 2) * sin(valveAngle + 0.05f));
    glVertex2f(x + (rimRadius - 5) * cos(valveAngle + 0.05f),
              y + (rimRadius - 5) * sin(valveAngle + 0.05f));
    glEnd();
    
    // Draw tire tread pattern
    glColor3f(0.1f, 0.1f, 0.1f);
    glLineWidth(1.0f);
    for (int i = 0; i < 12; i++) {
        float angle = (i * 30.0f) * 3.14159f / 180.0f;
        glBegin(GL_LINES);
        glVertex2f(x + (radius - 2) * cos(angle),
                  y + (radius - 2) * sin(angle));
        glVertex2f(x + (radius + 2) * cos(angle),
                  y + (radius + 2) * sin(angle));
        glEnd();
    }
    
    // Optional: Add a slight camber effect for the JDM look
    // (This is just for visual effect - in a real application you'd transform the entire wheel)
    float camberOffset = radius * 0.05f;
    glColor3f(0.15f, 0.15f, 0.15f);
    glBegin(GL_LINES);
    glVertex2f(x - radius, y);
    glVertex2f(x - radius, y - camberOffset);
    glVertex2f(x + radius, y);
    glVertex2f(x + radius, y + camberOffset);
    glEnd();
}

// Fungsi untuk menggambar mobil sport
void drawSportsCar() {
    // Definisi koordinat
    float baseX = WINDOW_WIDTH / 2.0f;
    float baseY = WINDOW_HEIGHT / 2.0f - 50.0f; // Turunkan posisi mobil untuk menyesuaikan dengan jalan
    float carLength = 300.0f;
    float carHeight = 60.0f;
    float roofHeight = 35.0f;
    float wheelRadius = 30.0f;
    
    // Bayangan mobil
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/2 + 20, baseY - carHeight - 5);
    glVertex2f(baseX + carLength/2 - 20, baseY - carHeight - 5);
    glVertex2f(baseX + carLength/2 - 40, baseY - carHeight - 15);
    glVertex2f(baseX - carLength/2 + 40, baseY - carHeight - 15);
    glEnd();
    
    // Badan mobil bagian bawah - Dengan lebih banyak sudut tajam khas JDM
    glColor3f(carColor.r, carColor.g, carColor.b);
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/2, baseY - 10);
    glVertex2f(baseX - carLength/2 + 70, baseY); // Kap depan yang lebih landai
    glVertex2f(baseX + carLength/2 - 70, baseY); // Kap belakang yang lebih landai
    glVertex2f(baseX + carLength/2, baseY - 10);
    glVertex2f(baseX + carLength/2 - 20, baseY - carHeight);
    glVertex2f(baseX - carLength/2 + 20, baseY - carHeight);
    glEnd();
    
    // Badan mobil bagian atas (atap) - Lebih rendah dan aerodinamis
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/4, baseY);
    glVertex2f(baseX + carLength/5, baseY);
    glVertex2f(baseX + carLength/7, baseY + roofHeight);
    glVertex2f(baseX - carLength/7, baseY + roofHeight);
    glEnd();
    
    // Tambahan detail badan - Garis bawah khas JDM
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/2 + 30, baseY - carHeight + 5);
    glVertex2f(baseX + carLength/2 - 30, baseY - carHeight + 5);
    glVertex2f(baseX + carLength/2 - 40, baseY - carHeight);
    glVertex2f(baseX - carLength/2 + 40, baseY - carHeight);
    glEnd();
    
    // Kaca depan
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX + carLength/5, baseY);
    glVertex2f(baseX + carLength/7, baseY + roofHeight);
    glVertex2f(baseX - carLength/7, baseY + roofHeight);
    glVertex2f(baseX - carLength/4, baseY);
    glEnd();
    
    // Kaca samping
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/4, baseY);
    glVertex2f(baseX - carLength/7, baseY + roofHeight);
    glVertex2f(baseX - carLength/3, baseY + roofHeight/2);
    glVertex2f(baseX - carLength/2 + 70, baseY);
    glEnd();
    
    // Kaca belakang
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/3, baseY + roofHeight/2);
    glVertex2f(baseX - carLength/7, baseY + roofHeight);
    glVertex2f(baseX - carLength/2 + 70, baseY + 5);
    glVertex2f(baseX - carLength/2 + 60, baseY);
    glEnd();
    
    // Ujung kap depan (hood)
    glColor3f(carColor.r * 0.9f, carColor.g * 0.9f, carColor.b * 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX + carLength/2 - 80, baseY);
    glVertex2f(baseX + carLength/2, baseY - 10);
    glVertex2f(baseX + carLength/2 - 20, baseY - 30);
    glVertex2f(baseX + carLength/2 - 100, baseY - 20);
    glEnd();
    
    // Spion samping
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX + carLength/7, baseY + roofHeight/2);
    glVertex2f(baseX + carLength/7 + 15, baseY + roofHeight/2);
    glVertex2f(baseX + carLength/7 + 20, baseY + roofHeight/2 - 5);
    glVertex2f(baseX + carLength/7, baseY + roofHeight/2 - 10);
    glEnd();
    
    // Logo JDM (simple)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX + carLength/2 - 50, baseY - 15);
    glVertex2f(baseX + carLength/2 - 40, baseY - 15);
    glVertex2f(baseX + carLength/2 - 40, baseY - 25);
    glVertex2f(baseX + carLength/2 - 50, baseY - 25);
    glEnd();
    
    // Lampu depan JDM style (lebih tajam)
    glColor3f(1.0f, 1.0f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX + carLength/2 - 10, baseY - 15);
    glVertex2f(baseX + carLength/2, baseY - 10);
    glVertex2f(baseX + carLength/2, baseY - 30);
    glVertex2f(baseX + carLength/2 - 15, baseY - 35);
    glEnd();
    
    // Lampu belakang JDM style (lebih lebar)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/2 + 5, baseY - 15);
    glVertex2f(baseX - carLength/2, baseY - 10);
    glVertex2f(baseX - carLength/2, baseY - 40);
    glVertex2f(baseX - carLength/2 + 10, baseY - 45);
    glEnd();
    
    // Spoiler JDM style - lebih tinggi dan agresif
    glColor3f(0.0f, 0.0f, 0.0f); // Spoiler hitam
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/2 + 20, baseY);
    glVertex2f(baseX - carLength/2 + 70, baseY);
    glVertex2f(baseX - carLength/2 + 60, baseY + 40);
    glVertex2f(baseX - carLength/2 + 30, baseY + 40);
    glEnd();
    
    // Pegangan spoiler
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/2 + 30, baseY);
    glVertex2f(baseX - carLength/2 + 40, baseY);
    glVertex2f(baseX - carLength/2 + 40, baseY + 30);
    glVertex2f(baseX - carLength/2 + 30, baseY + 30);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/2 + 50, baseY);
    glVertex2f(baseX - carLength/2 + 60, baseY);
    glVertex2f(baseX - carLength/2 + 60, baseY + 30);
    glVertex2f(baseX - carLength/2 + 50, baseY + 30);
    glEnd();
    
    // Roda depan - Lebih besar dan black deep dish style
    drawCustomWheel(baseX + carLength/4, baseY - carHeight, wheelRadius + 5);
    
    // Roda belakang - Lebih besar dan black deep dish style
    drawCustomWheel(baseX - carLength/4, baseY - carHeight, wheelRadius + 5);
    
    // Garis pemisah pintu
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(baseX, baseY - 5);
    glVertex2f(baseX, baseY - carHeight + 15);
    glEnd();
    
    // Handle pintu JDM style
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX + 10, baseY - 20);
    glVertex2f(baseX + 25, baseY - 20);
    glVertex2f(baseX + 25, baseY - 25);
    glVertex2f(baseX + 10, baseY - 25);
    glEnd();
    
    // Exhaust JDM
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX - carLength/2 + 5, baseY - carHeight + 10);
    glVertex2f(baseX - carLength/2 + 15, baseY - carHeight + 10);
    glVertex2f(baseX - carLength/2 + 15, baseY - carHeight);
    glVertex2f(baseX - carLength/2 + 5, baseY - carHeight);
    glEnd();
    
    // Intercooler visible
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
    glVertex2f(baseX + carLength/2 - 30, baseY - carHeight + 15);
    glVertex2f(baseX + carLength/2 - 10, baseY - carHeight + 15);
    glVertex2f(baseX + carLength/2 - 10, baseY - carHeight + 5);
    glVertex2f(baseX + carLength/2 - 30, baseY - carHeight + 5);
    glEnd();
    
    // Garis-garis pada intercooler
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(1.0f);
    for (int i = 0; i < 5; i++) {
        glBegin(GL_LINES);
        glVertex2f(baseX + carLength/2 - 28 + i*4, baseY - carHeight + 15);
        glVertex2f(baseX + carLength/2 - 28 + i*4, baseY - carHeight + 5);
        glEnd();
    }
}



// Fungsi display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Atur warna background
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    
    // Gambar Tokyo
    drawTokyoBackground();
    
    // // Gambar jalan Tol
    drawHighway();
    
    // Gambar mobil sport
    drawSportsCar();
    

    
    glutSwapBuffers();
}

// Fungsi reshape
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil Sport 2D");
    
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}
