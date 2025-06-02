// game.h (Updated) - dengan penyebab game over, kontrol kamera, dan kamera tampak depan

#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "airplane.h"
#include "ring.h"
#include "building.h"
#include "cloud.h"
#include "bird.h"

// Enum untuk melacak penyebab game over
enum GameOverReason {
    NONE,
    BUILDING_COLLISION,
    CLOUD_COLLISION,
    BIRD_COLLISION,
    TIME_UP
};

class Game {
public:
    // Mode kamera
    enum CameraMode {
        FOLLOW_CAMERA,
        FREE_CAMERA,
        FIRST_PERSON,
        FRONT_CAMERA  // Mode kamera tampak depan baru
    };

    Airplane player;
    std::vector<Ring> rings;
    std::vector<Building> buildings;
    std::vector<Cloud> clouds;
    std::vector<Bird> birds;
    bool keys[256];
    int score;
    int gameTime; // Waktu game dalam detik
    int timerStartTime;
    bool gameOver;
    bool gameWin;  // Flag untuk menandakan kemenangan
    int remainingTime; // Untuk menyimpan waktu tersisa saat game berakhir
    int elapsedTime; // Untuk menyimpan waktu yang sudah dihabiskan
    GameOverReason gameOverReason; // Penyebab game over
    
    // Variabel kontrol kamera
    float cameraDistance;   // Jarak dari pesawat
    float cameraHeight;     // Ketinggian di atas pesawat
    float cameraOffset;     // Offset lateral (kiri/kanan)
    CameraMode cameraMode;  // Mode kamera saat ini
    
    Game();
    
    // Inisialisasi game
    void init();
    
    // Generasi objek game
    void generateBuildings();
    void generateRings();
    void generateClouds();
    void generateBirds();
    
    // Proses input dari pemain
    void processInput();
    
    // Update objek game
    void updateObjects();
    
    // Reset game
    void restart();
    
    // Cek jika semua ring sudah terlewati
    bool checkAllRingsCollected() const;
};

// Fungsi untuk menggambar lingkungan
void drawGround();
void drawSky();

// Fungsi untuk menampilkan teks di layar
void renderText(const char* text, float x, float y);

// Fungsi untuk menampilkan HUD (Heads-Up Display)
void displayHUD(const Game& game);

#endif // GAME_H
