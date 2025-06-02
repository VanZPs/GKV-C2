#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <random>

using namespace std;

// Texture ID for wood floor
GLuint woodTextureID;

// Particle system for visual effects
struct Particle {
    float x, y, z;
    float vx, vy, vz;
    float r, g, b;
    float life;
    float maxLife;
    bool active;
};

const int MAX_PARTICLES = 100;
Particle particles[MAX_PARTICLES];
random_device rd;
mt19937 gen(rd());

// Function to load BMP texture
GLuint loadBMPTexture(const char* filename) {
    FILE* file;
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    unsigned char* data;
    
    // Open the file
    file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Could not open texture file %s\n", filename);
        return 0;
    }
    
    // Read the header
    if (fread(header, 1, 54, file) != 54) {
        printf("Error: Not a correct BMP file\n");
        fclose(file);
        return 0;
    }
    
    // Check BMP signature
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Error: Not a correct BMP file\n");
        fclose(file);
        return 0;
    }
    
    // Read image information
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    
    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;
    
    // Create a buffer
    data = new unsigned char[imageSize];
    
    // Read the actual data from the file into the buffer
    fseek(file, dataPos, SEEK_SET);
    fread(data, 1, imageSize, file);
    fclose(file);
    
    // Convert BGR to RGB (BMP stores colors in BGR format)
    for (unsigned int i = 0; i < imageSize; i += 3) {
        unsigned char temp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = temp;
    }
    
    // Create OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Upload the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    delete[] data;
    return textureID;
}

// Initialize environment system
void initEnvironment() {
    // Load wood texture
    woodTextureID = loadBMPTexture("Environment/wood.bmp");
    if (woodTextureID == 0) {
        printf("Warning: Failed to load wood texture, using default color\n");
    }
    
    // Initialize particle system
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].active = false;
        particles[i].life = 0.0f;
        particles[i].maxLife = 1.0f;
    }
    
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
}

// Create a new particle at specified position
void createParticle(float x, float y, float z, float r, float g, float b) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!particles[i].active) {
            particles[i].x = x;
            particles[i].y = y;
            particles[i].z = z;
            
            // Random velocity
            uniform_real_distribution<float> vel(-0.1f, 0.1f);
            particles[i].vx = vel(gen);
            particles[i].vy = vel(gen) + 0.05f; // Slight upward bias
            particles[i].vz = vel(gen);
            
            particles[i].r = r;
            particles[i].g = g;
            particles[i].b = b;
            
            uniform_real_distribution<float> lifeDist(0.5f, 2.0f);
            particles[i].maxLife = lifeDist(gen);
            particles[i].life = particles[i].maxLife;
            particles[i].active = true;
            break;
        }
    }
}

// Update particle system
void updateParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            // Update position
            particles[i].x += particles[i].vx;
            particles[i].y += particles[i].vy;
            particles[i].z += particles[i].vz;
            
            // Apply gravity
            particles[i].vy -= 0.002f;
            
            // Update life
            particles[i].life -= 0.016f; // Assuming 60 FPS
            
            if (particles[i].life <= 0.0f) {
                particles[i].active = false;
            }
        }
    }
    
    // Occasionally spawn ambient particles
    uniform_int_distribution<int> spawnChance(1, 300);
    if (spawnChance(gen) == 1) {
        uniform_real_distribution<float> xPos(-5.0f, 5.0f);
        uniform_real_distribution<float> yPos(1.0f, 6.0f);
        uniform_real_distribution<float> zPos(-1.0f, 3.0f);
        uniform_real_distribution<float> color(0.3f, 0.8f);
        
        createParticle(xPos(gen), yPos(gen), zPos(gen), 
                      color(gen), color(gen), color(gen));
    }
}

// Draw environment floor with wood texture
void drawEnvironmentFloor() {
    glPushMatrix();
    
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    if (woodTextureID != 0) {
        glBindTexture(GL_TEXTURE_2D, woodTextureID);
        glColor3f(1.0f, 1.0f, 1.0f); // White color to show texture properly
    } else {
        glDisable(GL_TEXTURE_2D);
        glColor3f(0.6f, 0.4f, 0.2f); // Brown color as fallback
    }
    
    // Draw floor plane
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    
    // Bottom floor (y = -6.2)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.5f, -6.2f, -2.5f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f( 6.5f, -6.2f, -2.5f);
    glTexCoord2f(4.0f, 2.0f); glVertex3f( 6.5f, -6.2f,  4.5f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(-6.5f, -6.2f,  4.5f);
    
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// Draw environment boundaries (walls)
void drawEnvironmentBoundaries() {
    glDisable(GL_LIGHTING);
    glColor4f(0.2f, 0.2f, 0.3f, 0.3f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glBegin(GL_QUADS);
    
    // Left wall
    glVertex3f(-6.0f, -6.0f, -2.0f);
    glVertex3f(-6.0f,  8.0f, -2.0f);
    glVertex3f(-6.0f,  8.0f,  4.0f);
    glVertex3f(-6.0f, -6.0f,  4.0f);
    
    // Right wall
    glVertex3f( 6.0f, -6.0f, -2.0f);
    glVertex3f( 6.0f, -6.0f,  4.0f);
    glVertex3f( 6.0f,  8.0f,  4.0f);
    glVertex3f( 6.0f,  8.0f, -2.0f);
    
    // Back wall
    glVertex3f(-6.0f, -6.0f,  4.0f);
    glVertex3f(-6.0f,  8.0f,  4.0f);
    glVertex3f( 6.0f,  8.0f,  4.0f);
    glVertex3f( 6.0f, -6.0f,  4.0f);
    
    // Top wall (ceiling)
    glVertex3f(-6.0f,  8.0f, -2.0f);
    glVertex3f( 6.0f,  8.0f, -2.0f);
    glVertex3f( 6.0f,  8.0f,  4.0f);
    glVertex3f(-6.0f,  8.0f,  4.0f);
    
    glEnd();
    
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    
    // Draw wireframe edges for better visibility
    glDisable(GL_LIGHTING);
    glColor3f(0.4f, 0.4f, 0.5f);
    glLineWidth(2.0f);
    
    glBegin(GL_LINES);
    
    // Vertical edges
    glVertex3f(-6.0f, -6.0f, -2.0f); glVertex3f(-6.0f,  8.0f, -2.0f);
    glVertex3f( 6.0f, -6.0f, -2.0f); glVertex3f( 6.0f,  8.0f, -2.0f);
    glVertex3f(-6.0f, -6.0f,  4.0f); glVertex3f(-6.0f,  8.0f,  4.0f);
    glVertex3f( 6.0f, -6.0f,  4.0f); glVertex3f( 6.0f,  8.0f,  4.0f);
    
    // Horizontal edges - bottom
    glVertex3f(-6.0f, -6.0f, -2.0f); glVertex3f( 6.0f, -6.0f, -2.0f);
    glVertex3f(-6.0f, -6.0f,  4.0f); glVertex3f( 6.0f, -6.0f,  4.0f);
    glVertex3f(-6.0f, -6.0f, -2.0f); glVertex3f(-6.0f, -6.0f,  4.0f);
    glVertex3f( 6.0f, -6.0f, -2.0f); glVertex3f( 6.0f, -6.0f,  4.0f);
    
    // Horizontal edges - top
    glVertex3f(-6.0f,  8.0f, -2.0f); glVertex3f( 6.0f,  8.0f, -2.0f);
    glVertex3f(-6.0f,  8.0f,  4.0f); glVertex3f( 6.0f,  8.0f,  4.0f);
    glVertex3f(-6.0f,  8.0f, -2.0f); glVertex3f(-6.0f,  8.0f,  4.0f);
    glVertex3f( 6.0f,  8.0f, -2.0f); glVertex3f( 6.0f,  8.0f,  4.0f);
    
    glEnd();
    
    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}

// Draw particle effects
void drawEnvironmentParticles() {
    updateParticles();
    
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            float alpha = particles[i].life / particles[i].maxLife;
            glColor4f(particles[i].r, particles[i].g, particles[i].b, alpha * 0.6f);
            glVertex3f(particles[i].x, particles[i].y, particles[i].z);
        }
    }
    
    glEnd();
    glPointSize(1.0f);
    
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}

// Function to create explosion effect when blocks are destroyed
void createBlockExplosion(float x, float y, float z, float r, float g, float b) {
    for (int i = 0; i < 15; i++) { // Create 15 particles per explosion
        createParticle(x, y, z, r, g, b);
    }
}

// Function to create trail effect for the ball
void createBallTrail(float x, float y, float z) {
    static int trailCounter = 0;
    trailCounter++;
    
    if (trailCounter % 3 == 0) { // Create trail particle every 3 frames
        createParticle(x, y, z, 1.0f, 1.0f, 0.0f);
    }
}