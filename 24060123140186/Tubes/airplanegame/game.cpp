// game.cpp (Updated) - Dengan deteksi tabrakan awan dan burung dan kontrol kamera

#include "game.h"
#include <cstdio>

Game::Game() : score(0), gameTime(60), gameOver(false), gameWin(false), 
               remainingTime(60), elapsedTime(0), gameOverReason(NONE),
               cameraDistance(5.0f), cameraHeight(2.0f), cameraOffset(0.0f),
               cameraMode(FOLLOW_CAMERA) {
    // Reset input keys
    for (int i = 0; i < 256; i++) {
        keys[i] = false;
    }
}

void Game::init() {
    glClearColor(0.4f, 0.6f, 0.9f, 1.0f); // Warna langit biru yang lebih realistis
    glEnable(GL_DEPTH_TEST);
    
    // Inisialisasi pencahayaan
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // Posisi cahaya
    GLfloat lightPos[] = {10.0f, 20.0f, 10.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    // Mengaktifkan shading halus
    glShadeModel(GL_SMOOTH);
    
    // Mengatur material objek
    GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    // Inisialisasi objek permainan
    player.pos = Position(0, 5, 0);
    generateBuildings();
    generateRings();
    generateClouds();
    generateBirds();
    
    // Siapkan timer
    timerStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
    
    // Reset status permainan
    gameOver = false;
    gameWin = false;
    remainingTime = gameTime;
    elapsedTime = 0;
    gameOverReason = NONE;
    
    // Reset pengaturan kamera
    cameraDistance = 5.0f;
    cameraHeight = 2.0f;
    cameraOffset = 0.0f;
    cameraMode = FOLLOW_CAMERA;
    
    // Reset input keys
    for (int i = 0; i < 256; i++) {
        keys[i] = false;
    }
}

void Game::generateBuildings() {
    // Bersihkan bangunan yang ada
    buildings.clear();
    
    // Jumlah dan area bangunan
    int numBuildings = 70; // Tambahkan lebih banyak gedung
    float citySize = 120.0f; // Area kota yang lebih luas
    
    // Seed RNG
    srand(static_cast<unsigned int>(time(NULL)));
    
    // Membuat raster/grid untuk menempatkan bangunan secara lebih rapi
    int gridSize = 10;
    float cellSize = citySize / gridSize;
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            // Skip beberapa sel secara acak untuk membuat variasi
            if (rand() % 3 == 0) continue;
            
            // Posisi dasar di tengah sel dengan sedikit variasi
            float x = (i * cellSize) - citySize/2 + cellSize/2 + (rand() % (int)(cellSize/2)) - cellSize/4;
            float z = (j * cellSize) - citySize/2 + cellSize/2 + (rand() % (int)(cellSize/2)) - cellSize/4;
            
            // Hindari menempatkan bangunan di jalur awal pesawat
            if (fabs(x) < 7.0f && z > -15.0f && z < 15.0f) continue;
            
            // Variasi ukuran dengan beberapa gedung tinggi
            float width = 2.0f + (rand() % 3);
            float height = 5.0f + (rand() % 20); // Beberapa gedung tinggi
            float depth = 2.0f + (rand() % 3);
            
            // Warna variasi untuk gedung (warna lebih realistis)
            Color color;
            
            // Pilih dari beberapa warna gedung realistis
            int colorType = rand() % 5;
            switch (colorType) {
                case 0: // Abu-abu
                    color = Color(0.7f, 0.7f, 0.7f);
                    break;
                case 1: // Coklat muda
                    color = Color(0.8f, 0.7f, 0.6f);
                    break;
                case 2: // Biru muda (kaca)
                    color = Color(0.6f, 0.8f, 0.9f);
                    break;
                case 3: // Krem
                    color = Color(0.9f, 0.85f, 0.7f);
                    break;
                case 4: // Abu-abu gelap
                    color = Color(0.4f, 0.4f, 0.45f);
                    break;
            }
            
            buildings.push_back(Building(Position(x, height/2, z), width, height, depth, color));
        }
    }
}

void Game::generateRings() {
    // Bersihkan cincin yang ada
    rings.clear();
    
    // Buat jalur cincin dengan posisi yang lebih hati-hati
    int numRings = 10;
    float pathLength = 100.0f;
    float startZ = -20.0f;
    
    // Validasi posisi ring untuk menghindari tabrakan dengan gedung
    for (int i = 0; i < numRings; i++) {
        float z = startZ - (i * pathLength / numRings);
        float x = 10.0f * sin(i * 0.5f); // Jalur bergelombang
        float y = 10.0f + 3.0f * cos(i * 0.3f); // Ketinggian lebih tinggi untuk menghindari gedung
        
        // Cek apakah cincin terlalu dekat dengan gedung
        bool validPosition = true;
        for (size_t j = 0; j < buildings.size(); j++) {
            Building& building = buildings[j];
            float dx = building.pos.x - x;
            float dy = building.pos.y - y;
            float dz = building.pos.z - z;
            float distance = sqrt(dx*dx + dy*dy + dz*dz);
            
            // Jika terlalu dekat dengan gedung, tandai sebagai posisi tidak valid
            if (distance < (building.width + building.depth)/2 + 4.0f) {
                validPosition = false;
                break;
            }
        }
        
        // Jika posisinya valid, tambahkan cincin
        if (validPosition) {
            rings.push_back(Ring(Position(x, y, z), 2.0f, Color(0.0f, 1.0f, 1.0f)));
        } else {
            // Jika tidak valid, coba posisi alternatif yang lebih tinggi
            y += 5.0f; // Naikkan ketinggian
            rings.push_back(Ring(Position(x, y, z), 2.0f, Color(0.0f, 1.0f, 1.0f)));
        }
    }
}

void Game::generateClouds() {
    // Bersihkan awan yang ada
    clouds.clear();
    
    // Jumlah awan
    int numClouds = 15;
    
    // Seed RNG
    srand(static_cast<unsigned int>(time(NULL)));
    
    for (int i = 0; i < numClouds; i++) {
        float x = (rand() % 200) - 100; // Posisi X acak
        float y = 15.0f + (rand() % 15); // Ketinggian acak
        float z = (rand() % 200) - 100; // Posisi Z acak
        
        float size = 2.0f + (rand() % 30) / 10.0f; // Ukuran acak
        float speed = 0.02f + (rand() % 5) / 100.0f; // Kecepatan acak
        
        clouds.push_back(Cloud(Position(x, y, z), size, speed));
    }
}

void Game::generateBirds() {
    // Bersihkan burung yang ada
    birds.clear();
    
    // Jumlah burung
    int numBirds = 15;
    
    // Seed RNG
    srand(static_cast<unsigned int>(time(NULL)));
    
    for (int i = 0; i < numBirds; i++) {
        float x = (rand() % 200) - 100; // Posisi X acak
        float y = 10.0f + (rand() % 15); // Ketinggian acak
        float z = (rand() % 200) - 100; // Posisi Z acak
        
        float size = 0.5f + (rand() % 10) / 20.0f; // Ukuran acak
        float speed = 0.05f + (rand() % 10) / 100.0f; // Kecepatan acak
        
        birds.push_back(Bird(Position(x, y, z), size, speed));
    }
}

void Game::processInput() {
    if (gameOver || gameWin) return;
    
    // Proses input keyboard
    if (keys['w'] || keys['W']) player.moveForward();
    if (keys['a'] || keys['A']) player.turnLeft();
    if (keys['d'] || keys['D']) player.turnRight();
    if (keys['s'] || keys['S']) player.moveDown();
    if (keys[' ']) player.moveUp();
    
    // Kontrol kamera (hanya aktif dalam mode FREE_CAMERA)
    if (cameraMode == FREE_CAMERA) {
        if (keys['q'] || keys['Q']) cameraOffset -= 0.1f;  // Geser kamera ke kiri
        if (keys['e'] || keys['E']) cameraOffset += 0.1f;  // Geser kamera ke kanan
        if (keys['z'] || keys['Z']) cameraDistance += 0.1f; // Jauhkan kamera
        if (keys['x'] || keys['X']) cameraDistance -= 0.1f; // Dekatkan kamera
        if (keys['c'] || keys['C']) cameraHeight += 0.1f;   // Naikkan kamera
        if (keys['v'] || keys['V']) cameraHeight -= 0.1f;   // Turunkan kamera
        
        // Pastikan kamera tidak terlalu dekat
        if (cameraDistance < 1.0f) cameraDistance = 1.0f;
        if (cameraHeight < 0.1f) cameraHeight = 0.1f;
    }
    
    // Deteksi jika pesawat melewati cincin (C++98 compatible)
    for (size_t i = 0; i < rings.size(); i++) {
        if (!rings[i].collected && rings[i].checkCollision(player)) {
            rings[i].collected = true;
            score += 10;
            
            // Cek apakah semua cincin sudah terlewati
            if (checkAllRingsCollected()) {
                gameWin = true;
                return;
            }
        }
    }
    
    // Deteksi tabrakan dengan gedung
    for (size_t i = 0; i < buildings.size(); i++) {
        Building& building = buildings[i];
        float dx = player.pos.x - building.pos.x;
        float dy = player.pos.y - building.pos.y;
        float dz = player.pos.z - building.pos.z;
        
        // Deteksi kotak sederhana
        if (fabs(dx) < (building.width/2 + 0.5f) &&
            fabs(dy) < (building.height/2 + 0.5f) &&
            fabs(dz) < (building.depth/2 + 0.5f)) {
            // Pesawat menabrak gedung - game over
            gameOver = true;
            gameOverReason = BUILDING_COLLISION;
            return;
        }
    }
    
    // Deteksi tabrakan dengan awan
    for (size_t i = 0; i < clouds.size(); i++) {
        if (clouds[i].checkCollision(player)) {
            // Pesawat menabrak awan - game over
            gameOver = true;
            gameOverReason = CLOUD_COLLISION;
            return;
        }
    }
    
    // Deteksi tabrakan dengan burung
    for (size_t i = 0; i < birds.size(); i++) {
        if (birds[i].checkCollision(player)) {
            // Pesawat menabrak burung - game over
            gameOver = true;
            gameOverReason = BIRD_COLLISION;
            return;
        }
    }
}

void Game::updateObjects() {
    // Update awan
    for (size_t i = 0; i < clouds.size(); i++) {
        clouds[i].update();
    }
    
    // Update burung
    for (size_t i = 0; i < birds.size(); i++) {
        birds[i].update();
    }
}

void Game::restart() {
    gameOver = false;
    gameWin = false;
    score = 0;
    remainingTime = gameTime;
    elapsedTime = 0;
    gameOverReason = NONE;
    player.pos = Position(0, 5, 0);
    player.rotationY = 0;
    generateRings();
    generateClouds();
    generateBirds();
    timerStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
    
    // Reset pengaturan kamera
    cameraDistance = 5.0f;
    cameraHeight = 2.0f;
    cameraOffset = 0.0f;
    cameraMode = FOLLOW_CAMERA;
}

// Implementasi fungsi checkAllRingsCollected
bool Game::checkAllRingsCollected() const {
    for (size_t i = 0; i < rings.size(); i++) {
        if (!rings[i].collected) {
            return false;
        }
    }
    return true;
}

void drawGround() {
    glDisable(GL_LIGHTING); // Matikan pencahayaan untuk tanah
    glDisable(GL_DEPTH_TEST); // Mematikan depth test untuk menggambar ground
    
    // Warna hijau untuk tanah dengan sedikit tekstur
    glBegin(GL_QUADS);
        // Area besar: grid 50x50 dengan kotak berukuran 20 unit
        // Total luas area: 2000x2000 unit
        for (int x = -50; x < 50; x++) {
            for (int z = -50; z < 50; z++) {
                // Variasi warna hijau
                if ((x + z) % 2 == 0) {
                    glColor3f(0.0f, 0.55f, 0.0f); // Hijau tua
                } else {
                    glColor3f(0.15f, 0.65f, 0.1f); // Hijau muda
                }
                
                float size = 20.0f;
                float x1 = x * size;
                float z1 = z * size;
                float x2 = (x + 1) * size;
                float z2 = (z + 1) * size;
                
                glVertex3f(x1, 0.0f, z1);
                glVertex3f(x1, 0.0f, z2);
                glVertex3f(x2, 0.0f, z2);
                glVertex3f(x2, 0.0f, z1);
            }
        }
    glEnd();
    
    glEnable(GL_DEPTH_TEST); // Mengaktifkan kembali depth test
    glEnable(GL_LIGHTING); // Aktifkan kembali pencahayaan
}

void drawSky() {
    glDisable(GL_LIGHTING); // Matikan pencahayaan untuk langit
    glDisable(GL_DEPTH_TEST); // Mematikan depth test untuk menggambar langit
    
    // Warna langit gradien
    glPushMatrix();
    glBegin(GL_QUADS);
        // Atas (biru tua)
        glColor3f(0.0f, 0.4f, 0.8f);
        glVertex3f(-1000.0f, 100.0f, -1000.0f); // Perluas ukuran langit
        glVertex3f(-1000.0f, 100.0f, 1000.0f);
        glVertex3f(1000.0f, 100.0f, 1000.0f);
        glVertex3f(1000.0f, 100.0f, -1000.0f);
        
        // Tengah (biru)
        glColor3f(0.4f, 0.6f, 0.9f);
        glVertex3f(-1000.0f, 40.0f, -1000.0f);
        glVertex3f(-1000.0f, 40.0f, 1000.0f);
        glVertex3f(1000.0f, 40.0f, 1000.0f);
        glVertex3f(1000.0f, 40.0f, -1000.0f);
        
        // Bawah (biru muda)
        glColor3f(0.7f, 0.85f, 1.0f);
        glVertex3f(-1000.0f, 0.0f, -1000.0f);
        glVertex3f(-1000.0f, 0.0f, 1000.0f);
        glVertex3f(1000.0f, 0.0f, 1000.0f);
        glVertex3f(1000.0f, 0.0f, -1000.0f);
    glEnd();
    glPopMatrix();
    
    glEnable(GL_DEPTH_TEST); // Mengaktifkan kembali depth test
    glEnable(GL_LIGHTING); // Aktifkan kembali pencahayaan
}

void renderText(const char* text, float x, float y) {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void displayHUD(const Game& game) {
    // Dapatkan ukuran window sekali di awal
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    
    char scoreText[100];
    sprintf(scoreText, "Score: %d", game.score);
    
    // Menampilkan skor dengan warna kuning emas
    glColor3f(1.0f, 0.84f, 0.0f);
    renderText(scoreText, 10, windowHeight - 30);
    
    // Tampilkan waktu tersisa
    int currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
    int timeElapsed = currentTime - game.timerStartTime;
    int timeLeft;
    
    // Gunakan remainingTime jika game over atau win, jika tidak hitung seperti biasa
    if (game.gameOver || game.gameWin) {
        timeLeft = game.remainingTime;
    } else {
        timeLeft = game.gameTime - timeElapsed;
        if (timeLeft <= 0) {
            timeLeft = 0;
        }
    }
    
    // Tampilkan waktu dengan warna yang berubah saat mendekati habis
    char timeText[100];
    sprintf(timeText, "Time: %d", timeLeft);
    
    // Ubah warna teks berdasarkan waktu tersisa
    if (timeLeft <= 10) {
        // Merah berkedip untuk 10 detik terakhir
        if (timeLeft % 2 == 0) {
            glColor3f(1.0f, 0.0f, 0.0f); // Merah
        } else {
            glColor3f(1.0f, 0.5f, 0.0f); // Oranye
        }
    } else if (timeLeft <= 20) {
        glColor3f(1.0f, 0.5f, 0.0f); // Oranye
    } else {
        glColor3f(1.0f, 1.0f, 1.0f); // Putih
    }
    
    renderText(timeText, windowWidth - 120, windowHeight - 30);
    
    // Tampilkan informasi mode kamera
    char cameraText[100];
    
    switch (game.cameraMode) {
        case Game::FREE_CAMERA:
            sprintf(cameraText, "Free Camera: Q/E - Kiri/Kanan, Z/X - Jarak, C/V - Tinggi (F: ganti)");
            glColor3f(0.0f, 1.0f, 0.0f); // Hijau
            break;
        case Game::FIRST_PERSON:
            sprintf(cameraText, "First Person View (F: ganti mode)");
            glColor3f(1.0f, 0.5f, 0.0f); // Oranye
            break;
        case Game::FOLLOW_CAMERA:
        default:
            sprintf(cameraText, "Follow Camera (F: ganti mode)");
            glColor3f(0.5f, 0.5f, 1.0f); // Biru muda
            break;
    }
    renderText(cameraText, windowWidth/2 - 250, 70);
    
    // Gambar background untuk panduan kontrol
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // Background semi-transparan berwarna biru tua
    glColor4f(0.0f, 0.1f, 0.3f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(0, 45);
        glVertex2f(windowWidth, 45);
        glVertex2f(windowWidth, 0);
    glEnd();
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    
    glDisable(GL_BLEND);
    
    // Tampilkan teks kontrol dengan warna-warna menarik
       glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    renderText("W", 20, 20);
    glColor3f(1.0f, 1.0f, 1.0f); // Putih
    renderText(": FORWARD", 40, 20);
    
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    renderText("S", windowWidth / 8, 20);
    glColor3f(1.0f, 1.0f, 1.0f); // Putih
    renderText(": DOWN", windowWidth / 8 + 20, 20);
    
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    renderText("A", 2 * windowWidth / 8, 20);
    glColor3f(1.0f, 1.0f, 1.0f); // Putih
    renderText(": LEFT", 2 * windowWidth / 8 + 20, 20);
    
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    renderText("D", 3 * windowWidth / 8, 20);
    glColor3f(1.0f, 1.0f, 1.0f); // Putih
    renderText(": RIGHT", 3 * windowWidth / 8 + 20, 20);
    
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    renderText("SPACE", 4 * windowWidth / 8, 20);
    glColor3f(1.0f, 1.0f, 1.0f); // Putih
    renderText(": UP", 4 * windowWidth / 8 + 50, 20);
    
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    renderText("F", 5 * windowWidth / 8, 20);
    glColor3f(1.0f, 1.0f, 1.0f); // Putih
    renderText(": CAMERA", 5 * windowWidth / 8 + 20, 20);
    
    glColor3f(0.0f, 1.0f, 1.0f); // Cyan
    renderText("R", 6 * windowWidth / 8, 20);
    glColor3f(1.0f, 1.0f, 1.0f); // Putih
    renderText(": RESTART", 6 * windowWidth / 8 + 20, 20);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    // Tampilkan pesan WIN ketika pemain mengumpulkan semua cincin
    if (game.gameWin) {
        // Background semi-transparan untuk pesan win
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
        
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        
        // Background hijau semi-transparan
        glColor4f(0.0f, 0.5f, 0.0f, 0.7f);
        glBegin(GL_QUADS);
            glVertex2f(windowWidth/2 - 200, windowHeight/2 - 60);
            glVertex2f(windowWidth/2 - 200, windowHeight/2 + 60);
            glVertex2f(windowWidth/2 + 200, windowHeight/2 + 60);
            glVertex2f(windowWidth/2 + 200, windowHeight/2 - 60);
        glEnd();
        
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        
        glDisable(GL_BLEND);
        
        // Teks WIN dengan warna hijau terang
        glColor3f(0.0f, 1.0f, 0.0f);
        char winText[100];
        sprintf(winText, "WIN! Final Score: %d", game.score);
        renderText(winText, windowWidth/2 - 120, windowHeight/2 + 20);
        
        // Tampilkan waktu yang dihabiskan untuk menang
        char winTimeText[100];
        sprintf(winTimeText, "Time Used: %d seconds", game.elapsedTime);
        renderText(winTimeText, windowWidth/2 - 100, windowHeight/2 - 10);
        
        // Teks instruksi restart dengan warna putih
        glColor3f(1.0f, 1.0f, 1.0f);
        renderText("Press R to restart", windowWidth/2 - 100, windowHeight/2 - 40);
        
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
    }
    // Tampilkan pesan game over dengan lebih jelas
    else if (game.gameOver) {
        // Background semi-transparan untuk pesan game over
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
        
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        
        // Background hitam semi-transparan
        glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
        glBegin(GL_QUADS);
            glVertex2f(windowWidth/2 - 200, windowHeight/2 - 80);
            glVertex2f(windowWidth/2 - 200, windowHeight/2 + 60);
            glVertex2f(windowWidth/2 + 200, windowHeight/2 + 60);
            glVertex2f(windowWidth/2 + 200, windowHeight/2 - 80);
        glEnd();
        
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        
        glDisable(GL_BLEND);
        
        // Teks game over dengan warna merah
        glColor3f(1.0f, 0.0f, 0.0f);
        char gameOverText[100];
        sprintf(gameOverText, "GAME OVER! Final Score: %d", game.score);
        renderText(gameOverText, windowWidth/2 - 150, windowHeight/2 + 30);
        
        // Teks alasan game over
        char reasonText[100];
        switch (game.gameOverReason) {
            case BUILDING_COLLISION:
                sprintf(reasonText, "You crashed into a building!");
                break;
            case CLOUD_COLLISION:
                sprintf(reasonText, "You flew into a cloud!");
                break;
            case BIRD_COLLISION:
                sprintf(reasonText, "You hit a bird!");
                break;
            case TIME_UP:
                sprintf(reasonText, "Time's up!");
                break;
            default:
                reasonText[0] = '\0'; // Empty string
        }
        if (reasonText[0] != '\0') {
            renderText(reasonText, windowWidth/2 - 120, windowHeight/2);
        }
        
        // Teks instruksi restart dengan warna putih
        glColor3f(1.0f, 1.0f, 1.0f);
        renderText("Press R to restart", windowWidth/2 - 100, windowHeight/2 - 30);
        
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
    }
}
