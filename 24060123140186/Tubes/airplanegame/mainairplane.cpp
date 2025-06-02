// mainairplane.cpp (Updated) - Dengan deteksi tabrakan awan dan burung, kontrol kamera, tampak depan, dan bayangan gedung

#include "common.h"
#include "airplane.h"
#include "ring.h"
#include "building.h"
#include "cloud.h"
#include "bird.h"
#include "game.h"

// Variabel global
Game game;

// Fungsi untuk menggambar seluruh scene
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Kamera dengan berbagai mode
    float radians = game.player.rotationY * 3.14159f / 180.0f;
    float cameraX, cameraY, cameraZ;
    float targetX, targetY, targetZ;
    
    // Hitung offset lateral untuk free camera
    float lateralOffsetX = cos(radians) * game.cameraOffset;
    float lateralOffsetZ = sin(radians) * game.cameraOffset;
    
    switch (game.cameraMode) {
        case Game::FREE_CAMERA:
            // Kamera bebas dengan posisi yang dapat dikontrol user
            cameraX = game.player.pos.x + sin(radians) * game.cameraDistance + lateralOffsetX;
            cameraY = game.player.pos.y + game.cameraHeight;
            cameraZ = game.player.pos.z + cos(radians) * game.cameraDistance - lateralOffsetZ;
            targetX = game.player.pos.x;
            targetY = game.player.pos.y;
            targetZ = game.player.pos.z;
            break;
            
        case Game::FIRST_PERSON:
            // Kamera first-person dari perspektif pilot
            cameraX = game.player.pos.x;
            cameraY = game.player.pos.y + 0.5f; // Sedikit di atas pusat pesawat
            cameraZ = game.player.pos.z;
            // Lihat ke arah pesawat menghadap
            targetX = game.player.pos.x - sin(radians) * 10.0f;
            targetY = game.player.pos.y + 0.5f;
            targetZ = game.player.pos.z - cos(radians) * 10.0f;
            break;
            
        case Game::FRONT_CAMERA:
            // Kamera tampak depan - melihat ke arah pesawat dari depan
            cameraX = game.player.pos.x - sin(radians) * 7.0f;
            cameraY = game.player.pos.y + 1.0f; // Sedikit di atas pesawat
            cameraZ = game.player.pos.z - cos(radians) * 7.0f;
            // Lihat ke arah pesawat
            targetX = game.player.pos.x;
            targetY = game.player.pos.y;
            targetZ = game.player.pos.z;
            break;
            
        case Game::FOLLOW_CAMERA:
        default:
            // Kamera follow default
            cameraX = game.player.pos.x + sin(radians) * 5.0f;
            cameraY = game.player.pos.y + 2.0f;
            cameraZ = game.player.pos.z + cos(radians) * 5.0f;
            targetX = game.player.pos.x;
            targetY = game.player.pos.y;
            targetZ = game.player.pos.z;
            
            // Reset parameter kamera di mode follow
            game.cameraDistance = 5.0f;
            game.cameraHeight = 2.0f;
            game.cameraOffset = 0.0f;
            break;
    }
    
    gluLookAt(
        cameraX, cameraY, cameraZ,  // Posisi kamera
        targetX, targetY, targetZ,  // Titik target
        0.0f, 1.0f, 0.0f            // Vektor atas
    );
    
    // Gambar lingkungan dengan urutan yang benar untuk mencegah glitch
    drawSky();
    drawGround();
    
    // Aktifkan depth testing untuk mengatasi glitch rendering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    // Aktifkan backface culling untuk mengatasi glitch
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // Gambar bayangan gedung terlebih dahulu (di permukaan tanah)
    for (size_t i = 0; i < game.buildings.size(); i++) {
        game.buildings[i].drawShadow();
    }
    
    // Gambar awan (C++98 compatible)
    for (size_t i = 0; i < game.clouds.size(); i++) {
        game.clouds[i].draw();
    }
    
    // Gambar burung (C++98 compatible)
    for (size_t i = 0; i < game.birds.size(); i++) {
        game.birds[i].draw();
    }
    
    // Gambar bangunan (C++98 compatible)
    for (size_t i = 0; i < game.buildings.size(); i++) {
        game.buildings[i].draw();
    }
    
    // Gambar cincin (C++98 compatible)
    for (size_t i = 0; i < game.rings.size(); i++) {
        game.rings[i].draw();
    }
    
    // Aktifkan blending untuk objek transparant
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Jangan gambar pesawat jika dalam mode first person
    if (game.cameraMode != Game::FIRST_PERSON) {
        game.player.draw();
    }
    
    // Matikan blending
    glDisable(GL_BLEND);
    
    // Matikan culling
    glDisable(GL_CULL_FACE);
    
    // Tampilkan HUD
    displayHUD(game);
    
    glutSwapBuffers();
}

// Fungsi callback untuk keyboard
void keyboard(unsigned char key, int x, int y) {
    game.keys[key] = true;
    
    // Toggle mode kamera dengan tombol F
    if (key == 'f' || key == 'F') {
        // Siklus melalui mode kamera
        switch (game.cameraMode) {
            case Game::FOLLOW_CAMERA:
                game.cameraMode = Game::FREE_CAMERA;
                break;
            case Game::FREE_CAMERA:
                game.cameraMode = Game::FIRST_PERSON;
                break;
            case Game::FIRST_PERSON:
                game.cameraMode = Game::FRONT_CAMERA;
                break;
            case Game::FRONT_CAMERA:
                game.cameraMode = Game::FOLLOW_CAMERA;
                break;
        }
        // Reset status tombol untuk mencegah toggle berulang
        game.keys['f'] = game.keys['F'] = false;
    }
    
    // Restart game
    if (key == 'r' || key == 'R') {
        if (game.gameOver || game.gameWin) {
            game.restart();
        }
    }
    
    // Menu utama (belum diimplementasikan)
    if (key == 'm' || key == 'M') {
        // TODO: Implementasi menu utama
    }
}

// Fungsi callback untuk keyboard (key up)
void keyboardUp(unsigned char key, int x, int y) {
    game.keys[key] = false;
}

// Fungsi callback untuk perubahan ukuran window
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width/(float)height, 0.1, 200.0);
    
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi update (timer callback)
void update(int value) {
    // Update status game over
    int currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
    int timeElapsed = currentTime - game.timerStartTime;
    int timeLeft = game.gameTime - timeElapsed;
    
    // Jika belum menang atau game over, periksa waktu dan update remainingTime dan elapsedTime
    if (!game.gameWin && !game.gameOver) {
        // Update remaining time dan elapsed time
        game.remainingTime = (timeLeft > 0) ? timeLeft : 0;
        game.elapsedTime = timeElapsed;
        
        // Cek apakah semua ring sudah terkumpulkan
        if (game.checkAllRingsCollected()) {
            game.gameWin = true;
            // elapsedTime sudah diset, akan digunakan untuk display
        }
        // Pastikan waktu tidak menjadi minus dan update gameOver jika waktu habis
        else if (timeLeft <= 0) {
            game.remainingTime = 0;
            game.elapsedTime = game.gameTime; // Waktu habis, jadi elapsed time = total waktu
            game.gameOver = true;
            game.gameOverReason = TIME_UP;
        }
    }
    
    // Proses input dan update objek hanya jika permainan masih berjalan
    if (!game.gameOver && !game.gameWin) {
        game.processInput();
        game.updateObjects(); // Update awan dan burung
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

// Fungsi main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Game Pesawat 3D OpenGL");
    
    // Eliminasi flickering/glitch dengan pengaturan buffer
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    
    // Perbaikan glitch gambar
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    // Mengaktifkan alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(16, update, 0);
    
    game.init();
    
    glutMainLoop();
    
    return 0;
}
