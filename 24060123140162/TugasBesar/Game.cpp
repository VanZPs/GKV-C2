/*
Nama Kelompok : 
Muhammad Azka Subhan - 24060123130086
Mohammad Izza Hakiki - 24060123140139
Lalu Gilang Wirapati - 24060123140162
*/

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <random>
#include <string>
#include <sstream>

// Window dimensions
int windowWidth = 1200;
int windowHeight = 800;

// Camera variables
float cameraX = 0.0f, cameraY = 8.0f, cameraZ = 20.0f;
float lookAtX = 0.0f, lookAtY = 0.0f, lookAtZ = 0.0f;
float cameraAngleX = 0.0f, cameraAngleY = 0.0f;
bool followCamera = false;
bool keys[256];

// Animation variables
float time_var = 0.0f;
float deltaTime = 0.016f;
int spawnDifficulty = 50; // Initial spawn difficulty, decreases over time

// Game variables
int score = 0;
int playerLives = 3;
bool gameRunning = true;
bool gameOver = false;
bool shadowsEnabled = false;

// Player spaceship structure
struct Spaceship {
    int gridX, gridY;
    float x, y, z;
    float targetX, targetY;
    float speed;
    float size;
    bool isMoving;
    bool hitAnimation;
    float hitTimer;
    float hitRotation;

    Spaceship(int gx, int gy);
    void updateWorldPosition();
    void move(int dx, int dy);
    void update(float dt);
};

// Enemy structure
struct Enemy {
    int gridX, gridY;
    float x, y, z;
    float speed;
    float size;
    float rotation;
    bool isRock;

    Enemy(int gx, int gy, bool rock);
    void updateWorldPosition();
    void update(float dt);
};

// Laser structure
struct Laser {
    float x, y, z;
    float speed;
    Laser(float px, float py, float pz);
};

// Particle structure
struct Particle {
    float x, y, z;
    float vx, vy, vz;
    float life;
    Particle(float px, float py, float pz);
};

// Star structure
struct Star {
    float x, y, z;
    float speed;
    Star();
};

// Global data
Spaceship player(2, 2);
std::vector<Enemy> enemies;
std::vector<Laser> lasers;
std::vector<Particle> particles;
std::vector<Star> stars;
GLuint starTexture, planetTexture, rockTexture, spaceshipTexture, sithTexture;

// Function prototypes
void setupLighting();
void createTexture(GLuint &textureId, float r, float g, float b, int pattern);
void initTextures();
void drawStars();
void drawPlanet();
void drawSpaceship(const Spaceship& ship);
void drawEnemy(const Enemy& enemy);
void drawLaser(const Laser& laser);
void drawParticles();
void drawShadowPlane();
void updateStars();
void updateEnemies();
void updateLasers();
void updateParticles();
void drawUI();
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void handleKeys();
void specialKeys(int key, int x, int y);
void timer(int value);
void display();
void reshape(int w, int h);
void init();

// Function definitions
Spaceship::Spaceship(int gx, int gy) {
    gridX = gx;
    gridY = gy;
    speed = 10.0f;
    size = 0.9f;
    z = 0.0f;
    isMoving = false;
    hitAnimation = false;
    hitTimer = 0.0f;
    hitRotation = 0.0f;
    updateWorldPosition();
}

void Spaceship::updateWorldPosition() {
    targetX = (gridX - 2) * 6.0f;
    targetY = (gridY - 2) * 6.0f;
}

void Spaceship::move(int dx, int dy) {
    int newGridX = gridX + dx;
    int newGridY = gridY + dy;
    if (newGridX >= 1 && newGridX <= 3) gridX = newGridX;
    if (newGridY >= 1 && newGridY <= 3) gridY = newGridY;
    updateWorldPosition();
    isMoving = true;
}

void Spaceship::update(float dt) {
    if (isMoving) {
        float lerpSpeed = 5.0f * dt;
        x += (targetX - x) * lerpSpeed;
        y += (targetY - y) * lerpSpeed;
        if (fabs(targetX - x) < 0.1f && fabs(targetY - y) < 0.1f) {
            x = targetX;
            y = targetY;
            isMoving = false;
        }
    }
    if (hitAnimation) {
        hitTimer += dt;
        hitRotation += 15.0f * dt; // Small rotation for shake effect
        if (hitTimer >= 1.0f) {
            hitAnimation = false;
            hitTimer = 0.0f;
            hitRotation = 0.0f;
        }
    }
}

Enemy::Enemy(int gx, int gy, bool rock) {
    gridX = gx;
    gridY = gy;
    updateWorldPosition();
    z = -50.0f;
    speed = rock ? 5.0f : 7.0f;
    size = rock ? 1.0f : 0.8f;
    rotation = 0.0f;
    isRock = rock;
}

void Enemy::updateWorldPosition() {
    x = (gridX - 2) * 6.0f;
    y = (gridY - 2) * 6.0f;
}

void Enemy::update(float dt) {
    z += speed * dt;
    if (isRock) rotation += 30.0f * dt;
}

Laser::Laser(float px, float py, float pz) {
    x = px; y = py; z = pz;
    speed = 10.0f;
}

Particle::Particle(float px, float py, float pz) {
    x = px; y = py; z = pz;
    vx = ((rand() % 200) - 100) / 50.0f;
    vy = ((rand() % 200) - 100) / 50.0f;
    vz = ((rand() % 200) - 100) / 50.0f;
    life = 1.0f;
}

Star::Star() {
    x = -20.0f + (rand() % 4000) / 100.0f;
    y = -15.0f + (rand() % 3000) / 100.0f;
    z = -50.0f + (rand() % 5000) / 100.0f;
    speed = 2.0f + (rand() % 200) / 100.0f;
}

void setupLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    GLfloat light0_pos[] = {0.0f, 10.0f, 20.0f, 1.0f};
    GLfloat light0_ambient[] = {0.1f, 0.1f, 0.2f, 1.0f};
    GLfloat light0_diffuse[] = {0.6f, 0.6f, 0.8f, 1.0f};
    GLfloat light0_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    GLfloat light1_pos[] = {player.x, player.y, player.z, 1.0f};
    GLfloat light1_dir[] = {0.0f, 0.0f, -1.0f};
    GLfloat light1_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light1_diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat light1_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_dir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

    GLfloat global_ambient[] = {0.05f, 0.05f, 0.1f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
}

void createTexture(GLuint &textureId, float r, float g, float b, int pattern) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    const int texSize = 64;
    unsigned char texture[texSize][texSize][3];
    for (int i = 0; i < texSize; i++) {
        for (int j = 0; j < texSize; j++) {
            float noise = sin(i * 0.1f) * cos(j * 0.1f) * 0.5f + 0.5f;
            if (pattern == 0) {
                texture[i][j][0] = (unsigned char)(r * 255 * (0.8f + noise * 0.4f));
                texture[i][j][1] = (unsigned char)(g * 255 * (0.8f + noise * 0.4f));
                texture[i][j][2] = (unsigned char)(b * 255 * (0.8f + noise * 0.4f));
            } else if (pattern == 1) {
                float pattern_val = sin(i * 0.3f) * sin(j * 0.3f) * 0.5f + 0.5f;
                texture[i][j][0] = (unsigned char)(r * 255 * (0.6f + pattern_val * 0.4f));
                texture[i][j][1] = (unsigned char)(g * 255 * (0.6f + pattern_val * 0.4f));
                texture[i][j][2] = (unsigned char)(b * 255 * (0.6f + pattern_val * 0.4f));
            } else if (pattern == 2) {
                float rock_noise = (sin(i * 0.2f) * cos(j * 0.2f) * 0.5f + 0.5f) * 0.4f;
                texture[i][j][0] = (unsigned char)(0.8f * 255 * (0.9f + rock_noise));
                texture[i][j][1] = (unsigned char)(0.8f * 255 * (0.9f + rock_noise));
                texture[i][j][2] = (unsigned char)(0.8f * 255 * (0.9f + rock_noise));
            } else if (pattern == 3) {
                float metal_noise = (sin(i * 0.15f) * cos(j * 0.15f) * 0.5f + 0.5f) * 0.3f;
                texture[i][j][0] = (unsigned char)(0.8f * 255 * (0.7f + metal_noise));
                texture[i][j][1] = (unsigned char)(0.8f * 255 * (0.7f + metal_noise));
                texture[i][j][2] = (unsigned char)(0.9f * 255 * (0.7f + metal_noise));
            } else {
                float panel_noise = (sin(i * 0.25f) * cos(j * 0.25f) * 0.5f + 0.5f) * 0.2f;
                texture[i][j][0] = (unsigned char)(0.3f * 255 * (0.6f + panel_noise));
                texture[i][j][1] = (unsigned char)(0.3f * 255 * (0.6f + panel_noise));
                texture[i][j][2] = (unsigned char)(0.3f * 255 * (0.6f + panel_noise));
            }
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texSize, texSize, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void initTextures() {
    createTexture(starTexture, 0.9f, 0.9f, 1.0f, 0);
    createTexture(planetTexture, 0.4f, 0.6f, 0.8f, 1);
    createTexture(rockTexture, 0.8f, 0.8f, 0.8f, 2);
    createTexture(spaceshipTexture, 0.8f, 0.8f, 0.9f, 3);
    createTexture(sithTexture, 0.3f, 0.3f, 0.3f, 4);
}

void drawStars() {
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, starTexture);
    glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
    for (const auto& star : stars) {
        glPushMatrix();
        glTranslatef(star.x, star.y, star.z);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f, -0.1f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.1f, -0.1f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.1f, 0.1f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, 0.1f, 0.0f);
        glEnd();
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

void drawPlanet() {
    glPushMatrix();
    glTranslatef(-15.0f, 10.0f, -50.0f);
    glRotatef(time_var * 10.0f, 0.0f, 1.0f, 0.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, planetTexture);
    GLfloat planet_material[] = {0.4f, 0.6f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, planet_material);
    GLfloat planet_specular[] = {0.2f, 0.2f, 0.3f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, planet_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
    glutSolidSphere(5.0f, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15.0f, -5.0f, -60.0f);
    glRotatef(time_var * -8.0f, 0.0f, 1.0f, 0.0f);
    glutSolidSphere(3.0f, 18, 18);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawSpaceship(const Spaceship& ship) {
    glPushMatrix();
    glTranslatef(ship.x, ship.y, ship.z);
    if (ship.hitAnimation && fmod(ship.hitTimer * 10, 2) < 1) {
        glColor3f(1.0f, 0.0f, 0.0f); // Blink red
    }
    glRotatef(ship.hitRotation, 0.0f, 0.0f, 1.0f); // Shake effect
    glScalef(ship.size, ship.size, ship.size);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spaceshipTexture);
    GLfloat body_material[] = {0.8f, 0.8f, 0.9f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, body_material);
    GLfloat body_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, body_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
    glutSolidSphere(0.5f, 10, 10);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spaceshipTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.7f);
    glScalef(0.3f, 0.3f, 0.5f);
    glutSolidCone(0.5f, 1.0f, 8, 8);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spaceshipTexture);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -0.5f);
    glutSolidSphere(0.2f, 8, 8);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spaceshipTexture);
    GLfloat wing_material[] = {1.0f, 0.2f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wing_material);
    glMaterialfv(GL_FRONT, GL_SPECULAR, body_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
    glPushMatrix();
    glTranslatef(0.5f, 0.5f, 0.0f);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.1f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.5f, 0.5f, 0.0f);
    glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.1f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.5f, -0.5f, 0.0f);
    glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.1f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.5f, -0.5f, 0.0f);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.1f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();
    if (ship.hitAnimation && fmod(ship.hitTimer * 10, 2) < 1) {
        glColor3f(1.0f, 1.0f, 1.0f); // Reset color
    }
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawEnemy(const Enemy& enemy) {
    glPushMatrix();
    glTranslatef(enemy.x, enemy.y, enemy.z);
    glRotatef(enemy.rotation, 0.0f, 1.0f, 0.0f);
    glScalef(enemy.size, enemy.size, enemy.size);
    if (enemy.isRock) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, rockTexture);
        GLfloat rock_material[] = {0.8f, 0.8f, 0.8f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, rock_material);
        GLfloat rock_specular[] = {0.3f, 0.3f, 0.3f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, rock_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 20.0f);
        glutSolidDodecahedron();
        glDisable(GL_TEXTURE_2D);
    } else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, sithTexture);
        GLfloat enemy_material[] = {0.3f, 0.3f, 0.3f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, enemy_material);
        GLfloat enemy_specular[] = {0.8f, 0.8f, 0.8f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, enemy_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 80.0f);
        glPushMatrix();
        glScalef(0.8f, 0.8f, 0.8f);
        glutSolidSphere(0.5f, 10, 10);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(1.0f, 0.0f, 0.0f);
        glScalef(0.1f, 1.5f, 1.0f);
        glutSolidSphere(0.5f, 6, 6);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-1.0f, 0.0f, 0.0f);
        glScalef(0.1f, 1.5f, 1.0f);
        glutSolidSphere(0.5f, 6, 6);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void drawLaser(const Laser& laser) {
    glPushMatrix();
    glTranslatef(laser.x, laser.y, laser.z);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 1.0f, 0.0f, 0.8f);
    glPushMatrix();
    glScalef(0.1f, 0.1f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-0.2f, -0.2f, 0.0f);
    glVertex3f(0.2f, -0.2f, 0.0f);
    glVertex3f(0.2f, 0.2f, 0.0f);
    glVertex3f(-0.2f, 0.2f, 0.0f);
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPopMatrix();
}

void drawParticles() {
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 0.5f, 0.0f, 0.8f);
    for (const auto& particle : particles) {
        glPushMatrix();
        glTranslatef(particle.x, particle.y, particle.z);
        glutSolidSphere(0.1f, 4, 4);
        glPopMatrix();
    }
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void drawShadowPlane() {
    glPushMatrix();
    glTranslatef(0.0f, -10.0f, 0.0f);
    if (shadowsEnabled) {
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        GLfloat lightPos[] = {0.0f, 10.0f, 20.0f, 1.0f};
        GLfloat plane[] = {0.0f, 1.0f, 0.0f, 10.0f};
        GLfloat shadowMatrix[16] = {
            lightPos[1], 0, 0, 0,
            -lightPos[0], 0, -lightPos[2], -1,
            0, 0, lightPos[1], 0,
            0, 0, -lightPos[3], lightPos[1]
        };
        glPushMatrix();
        glMultMatrixf(shadowMatrix);
        glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
        drawSpaceship(player);
        for (const auto& enemy : enemies) {
            drawEnemy(enemy);
        }
        glPopMatrix();
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();
}

void updateStars() {
    for (auto& star : stars) {
        star.z += star.speed * deltaTime;
        if (star.z > 10.0f) {
            star.z = -50.0f;
            star.x = -20.0f + (rand() % 4000) / 100.0f;
            star.y = -15.0f + (rand() % 3000) / 100.0f;
        }
    }
}

void updateEnemies() {
    for (size_t i = 0; i < enemies.size();) {
        Enemy& enemy = enemies[i];
        enemy.update(deltaTime);
        if (enemy.z > 10.0f) {
            enemies.erase(enemies.begin() + i);
            continue;
        }
        float dx = player.x - enemy.x;
        float dy = player.y - enemy.y;
        float dz = player.z - enemy.z;
        float dist = sqrt(dx*dx + dy*dy + dz*dz);
        if (dist < (player.size + enemy.size)) {
            playerLives--;
            if (playerLives <= 0) {
                gameOver = true;
                gameRunning = false;
            }
            enemies.erase(enemies.begin() + i);
            if (!enemy.isRock) {
                for (int j = 0; j < 20; j++) {
                    particles.push_back(Particle(enemy.x, enemy.y, enemy.z));
                }
            } else {
                player.hitAnimation = true; // Trigger hit animation for asteroid collision
            }
            continue;
        }
        i++;
    }
    if (enemies.empty() && rand() % spawnDifficulty < 2) {
        int randGridX = 1 + (rand() % 3);
        int randGridY = 1 + (rand() % 3);
        bool isRock = (rand() % 100) < 25;
        enemies.push_back(Enemy(randGridX, randGridY, isRock));
    }
}

void updateLasers() {
    for (size_t i = 0; i < lasers.size();) {
        Laser& laser = lasers[i];
        laser.z -= laser.speed * deltaTime;
        if (laser.z < -50.0f) {
            lasers.erase(lasers.begin() + i);
            continue;
        }
        bool hit = false;
        for (size_t j = 0; j < enemies.size(); j++) {
            Enemy& enemy = enemies[j];
            float dx = laser.x - enemy.x;
            float dy = laser.y - enemy.y;
            float dz = laser.z - enemy.z;
            float dist = sqrt(dx*dx + dy*dy + dz*dz);
            if (dist < (enemy.size + 0.5f) && !enemy.isRock) {
                score += 50;
                for (int k = 0; k < 20; k++) {
                    particles.push_back(Particle(enemy.x, enemy.y, enemy.z));
                }
                enemies.erase(enemies.begin() + j);
                lasers.erase(lasers.begin() + i);
                hit = true;
                break;
            }
        }
        if (!hit) i++;
    }
}

void updateParticles() {
    for (size_t i = 0; i < particles.size();) {
        Particle& particle = particles[i];
        particle.x += particle.vx * deltaTime;
        particle.y += particle.vy * deltaTime;
        particle.z += particle.vz * deltaTime;
        particle.life -= deltaTime;
        if (particle.life <= 0.0f) {
            particles.erase(particles.begin() + i);
        } else {
            i++;
        }
    }
}

void drawUI() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10, windowHeight - 30);
    std::string scoreText = "Score: " + std::to_string(score);
    for (char c : scoreText) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    glRasterPos2f(10, windowHeight - 60);
    std::string livesText = "Lives: " + std::to_string(playerLives);
    for (char c : livesText) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    int gridPos = (player.gridY - 1) * 3 + player.gridX;
    glRasterPos2f(10, windowHeight - 90);
    std::string posText = "Grid Position: " + std::to_string(gridPos);
    for (char c : posText) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    if (gameOver) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0); glVertex2f(windowWidth, 0);
        glVertex2f(windowWidth, windowHeight); glVertex2f(0, windowHeight);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(windowWidth/2 - 100, windowHeight/2 + 50);
        std::string gameOverText = "GAME OVER!";
        for (char c : gameOverText) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        glRasterPos2f(windowWidth/2 - 80, windowHeight/2);
        std::string finalScoreText = "Final Score: " + std::to_string(score);
        for (char c : finalScoreText) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        glRasterPos2f(windowWidth/2 - 100, windowHeight/2 - 80);
        std::string restartText = "Press R to Restart";
        for (char c : restartText) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
    glColor3f(0.8f, 0.8f, 0.8f);
    glRasterPos2f(windowWidth - 300, windowHeight - 30);
    std::string controlText = "WASD: Move Ship | Space: Shoot";
    for (char c : controlText) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    glRasterPos2f(windowWidth - 300, windowHeight - 50);
    std::string controlText2 = "Arrow Keys: Look | Z: Shadow | C: Camera";
    for (char c : controlText2) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    keys[key] = true;
    switch (key) {
        case 27: exit(0); break;
        case 'r': case 'R':
            if (gameOver) {
                gameOver = false;
                gameRunning = true;
                score = 0;
                playerLives = 3;
                player = Spaceship(2, 2);
                enemies.clear();
                lasers.clear();
                particles.clear();
                spawnDifficulty = 50; // Reset spawn difficulty
            }
            break;
        case 'z': case 'Z': shadowsEnabled = !shadowsEnabled; break;
        case 'c': case 'C': followCamera = !followCamera; break;
        case ' ': if (gameRunning) lasers.push_back(Laser(player.x, player.y, player.z)); break;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    keys[key] = false;
}

void handleKeys() {
    if (keys['w'] || keys['W']) { player.move(0, 1); keys['w'] = keys['W'] = false; }
    if (keys['s'] || keys['S']) { player.move(0, -1); keys['s'] = keys['S'] = false; }
    if (keys['a'] || keys['A']) { player.move(-1, 0); keys['a'] = keys['A'] = false; }
    if (keys['d'] || keys['D']) { player.move(1, 0); keys['d'] = keys['D'] = false; }
}

void specialKeys(int key, int x, int y) {
    float rotSpeed = 2.0f;
    switch (key) {
        case GLUT_KEY_UP: cameraAngleX -= rotSpeed; break;
        case GLUT_KEY_DOWN: cameraAngleX += rotSpeed; break;
        case GLUT_KEY_LEFT: cameraAngleY -= rotSpeed; break;
        case GLUT_KEY_RIGHT: cameraAngleY += rotSpeed; break;
    }
}

void timer(int value) {
    if (gameRunning) {
        time_var += 0.05f;
        handleKeys();
        player.update(deltaTime);
        updateStars();
        updateEnemies();
        updateLasers();
        updateParticles();
        setupLighting();
        // Increase difficulty every 30 seconds
        if (fmod(time_var, 30.0f) < deltaTime && spawnDifficulty > 20) {
            spawnDifficulty -= 10; // Reduce spawn threshold, increasing frequency
            if (spawnDifficulty < 20) spawnDifficulty = 20; // Minimum threshold
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (followCamera) {
        gluLookAt(player.x, player.y + 3.0f, player.z + 10.0f,
                  player.x, player.y, player.z,
                  0.0f, 1.0f, 0.0f);
    } else {
        gluLookAt(cameraX, cameraY, cameraZ,
                  lookAtX, lookAtY, lookAtZ,
                  0.0f, 1.0f, 0.0f);
        glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);
    }
    drawStars();
    drawPlanet();
    drawShadowPlane();
    for (const auto& enemy : enemies) drawEnemy(enemy);
    for (const auto& laser : lasers) drawLaser(laser);
    drawSpaceship(player);
    drawParticles();
    drawUI();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    setupLighting();
    initTextures();
    srand(time(NULL));
    for (int i = 0; i < 100; i++) stars.push_back(Star());
    for (int i = 0; i < 256; i++) keys[i] = false;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Space Blaster - OpenGL GLUT");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(0, timer, 0);
    std::cout << "=== SPACE BLASTER ===" << std::endl;
    std::cout << "CONTROLS:" << std::endl;
    std::cout << "- WASD: Move X-Wing on 3x3 grid (1-9)" << std::endl;
    std::cout << "- Space: Shoot laser" << std::endl;
    std::cout << "- Arrow Keys: Look around" << std::endl;
    std::cout << "- Z: Toggle Shadow" << std::endl;
    std::cout << "- C: Toggle Camera Follow" << std::endl;
    std::cout << "- R: Restart game (when game over)" << std::endl;
    std::cout << "- ESC: Exit" << std::endl;
    std::cout << "\nGRID POSITIONS:" << std::endl;
    std::cout << " 7 | 8 | 9 " << std::endl;
    std::cout << " 4 | 5 | 6 " << std::endl;
    std::cout << " 1 | 2 | 3 " << std::endl;
    std::cout << "\nOBJECTIVE: Destroy Sith Fighters to gain score! Avoid rocks." << std::endl;
    std::cout << "Avoid collisions to keep your lives. Game over when lives reach 0." << std::endl;
    glutMainLoop();
    return 0;
}
