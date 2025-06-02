#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <random>

using namespace std;

// Window dimensions
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

// Game constants
#define PADDLE_WIDTH_DEFAULT 2.0f
#define PADDLE_HEIGHT 0.3f
#define PADDLE_DEPTH 0.3f
#define BALL_RADIUS 0.15f
#define BLOCK_WIDTH 1.0f
#define BLOCK_HEIGHT 0.4f
#define BLOCK_DEPTH 0.6f
#define BLOCKS_PER_ROW 8
#define BLOCKS_PER_COL 5
#define LAYERS 2

// Game variables
float paddleX = 0.0f;
float ballX = 0.0f, ballY = -5.0f, ballZ = 0.0f;
float ballVelX = 0.05f, ballVelY = 0.08f, ballVelZ = 0.03f;
bool gameRunning = true;
int score = 0;
int blocksRemaining;

// Block structure
typedef struct {
    float x, y, z;
    bool active;
    float r, g, b; // Color
} Block;

Block blocks[LAYERS][BLOCKS_PER_COL][BLOCKS_PER_ROW];

// Initialize blocks
void initBlocks() {
    blocksRemaining = LAYERS * BLOCKS_PER_COL * BLOCKS_PER_ROW;
    
    for (int layer = 0; layer < LAYERS; layer++) {
        for (int row = 0; row < BLOCKS_PER_COL; row++) {
            for (int col = 0; col < BLOCKS_PER_ROW; col++) {
                blocks[layer][row][col].x = (col - BLOCKS_PER_ROW/2.0f + 0.5f) * (BLOCK_WIDTH + 0.1f);
                blocks[layer][row][col].y = 2.0f + row * (BLOCK_HEIGHT + 0.1f);
                blocks[layer][row][col].z = layer * (BLOCK_DEPTH + 0.2f);
                blocks[layer][row][col].active = true;
                
                // Random colors for all blocks
                float color_r[3] = {1.0f, 0.2f, 0.2f};
                float color_g[3] = {0.2f, 1.0f, 0.2f};
                float color_b[3] = {0.2f, 0.2f, 1.0f};
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> distrib(0, 3);
                int colorRoll = distrib(gen);
                blocks[layer][row][col].r = color_r[colorRoll];
                blocks[layer][row][col].g = color_g[colorRoll];
                blocks[layer][row][col].b = color_b[colorRoll];

                // Different colors for different layers
                // if (layer == 0) {
                //     blocks[layer][row][col].r = 1.0f;
                //     blocks[layer][row][col].g = 0.2f;
                //     blocks[layer][row][col].b = 0.2f;
                // } else if (layer == 1) {
                //     blocks[layer][row][col].r = 0.2f;
                //     blocks[layer][row][col].g = 1.0f;
                //     blocks[layer][row][col].b = 0.2f;
                // } else {
                //     blocks[layer][row][col].r = 0.2f;
                //     blocks[layer][row][col].g = 0.2f;
                //     blocks[layer][row][col].b = 1.0f;
                // }
            }
        }
    }
}

// Draw a cube
void drawCube(float x, float y, float z, float width, float height, float depth, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(width, height, depth);
    glColor3f(r, g, b);
    glutSolidCube(1.0);
    
    // Draw wireframe for better visibility
    glColor3f(0.0f, 0.0f, 0.0f);
    glutWireCube(1.02);
    glPopMatrix();
}

// Draw a sphere
void drawSphere(float x, float y, float z, float radius, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(r, g, b);
    glutSolidSphere(radius, 16, 16);
    glPopMatrix();
}

// Check collision between ball and box
bool checkCollision(float ballX, float ballY, float ballZ, float ballRadius,
                   float boxX, float boxY, float boxZ, float boxWidth, float boxHeight, float boxDepth) {
    // Calculate closest point on box to ball center
    float closestX = fmax(boxX - boxWidth/2, fmin(ballX, boxX + boxWidth/2));
    float closestY = fmax(boxY - boxHeight/2, fmin(ballY, boxY + boxHeight/2));
    float closestZ = fmax(boxZ - boxDepth/2, fmin(ballZ, boxZ + boxDepth/2));
    
    // Calculate distance between ball center and closest point
    float distanceX = ballX - closestX;
    float distanceY = ballY - closestY;
    float distanceZ = ballZ - closestZ;
    
    float distanceSquared = distanceX * distanceX + distanceY * distanceY + distanceZ * distanceZ;
    
    return distanceSquared < (ballRadius * ballRadius);
}

// Handle ball-block collisions
void handleBlockCollisions() {
    for (int layer = 0; layer < LAYERS; layer++) {
        for (int row = 0; row < BLOCKS_PER_COL; row++) {
            for (int col = 0; col < BLOCKS_PER_ROW; col++) {
                if (blocks[layer][row][col].active) {
                    if (checkCollision(ballX, ballY, ballZ, BALL_RADIUS,
                                     blocks[layer][row][col].x, blocks[layer][row][col].y, blocks[layer][row][col].z,
                                     BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_DEPTH)) {
                        
                        blocks[layer][row][col].active = false;
                        score += 10;
                        blocksRemaining--;
                        
                        // Simple collision response - reverse appropriate velocity component
                        float blockCenterX = blocks[layer][row][col].x;
                        float blockCenterY = blocks[layer][row][col].y;
                        float blockCenterZ = blocks[layer][row][col].z;
                        
                        float deltaX = ballX - blockCenterX;
                        float deltaY = ballY - blockCenterY;
                        float deltaZ = ballZ - blockCenterZ;
                        
                        // Determine which face was hit and reverse appropriate component
                        if (fabs(deltaX) > fabs(deltaY) && fabs(deltaX) > fabs(deltaZ)) {
                            ballVelX = -ballVelX;
                        } else if (fabs(deltaY) > fabs(deltaZ)) {
                            ballVelY = -ballVelY;
                        } else {
                            ballVelZ = -ballVelZ;
                        }
                        
                        return; // Only handle one collision per frame
                    }
                }
            }
        }
    }
}

// Update game physics
void updateGame() {
    if (!gameRunning) return;
    
    // Move ball
    ballX += ballVelX;
    ballY += ballVelY;
    ballZ += ballVelZ;
    
    // Wall collisions
    if (ballX <= -6.0f || ballX >= 6.0f) {
        ballVelX = -ballVelX;
    }
    if (ballY >= 8.0f) {
        ballVelY = -ballVelY;
    }
    if (ballZ <= -2.0f || ballZ >= 4.0f) {
        ballVelZ = -ballVelZ;
    }
    
    // Paddle collision
    if (ballY <= -5.5f && ballY >= -6.0f &&
        ballX >= paddleX - PADDLE_WIDTH_DEFAULT/2 && ballX <= paddleX + PADDLE_WIDTH_DEFAULT/2 &&
        ballZ >= -PADDLE_DEPTH/2 && ballZ <= PADDLE_DEPTH/2) {
        
        ballVelY = fabs(ballVelY); // Always bounce up
        
        // Add some spin based on where it hits the paddle
        float hitOffset = (ballX - paddleX) / (PADDLE_WIDTH_DEFAULT/2);
        ballVelX += hitOffset * 0.02f;
        
        // Clamp velocity
        if (ballVelX > 0.1f) ballVelX = 0.1f;
        if (ballVelX < -0.1f) ballVelX = -0.1f;
    }
    
    // Check for game over
    if (ballY < -7.0f) {
        gameRunning = false;
        printf("Game Over! Final Score: %d\n", score);
    }
    
    // Check for win
    if (blocksRemaining == 0) {
        gameRunning = false;
        printf("You Win! Final Score: %d\n", score);
    }
    
    // Handle block collisions
    handleBlockCollisions();
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Set camera position (angled above and behind)
    gluLookAt(0.0, -8.0, 12.0,    // Eye position
              0.0, 0.0, 0.0,     // Look at center
              0.0, 1.0, 0.0);    // Up vector
    
    // Draw paddle
    drawCube(paddleX, -5.8f, 0.0f, PADDLE_WIDTH_DEFAULT, PADDLE_HEIGHT, PADDLE_DEPTH, 0.8f, 0.8f, 0.8f);
    
    // Draw ball
    drawSphere(ballX, ballY, ballZ, BALL_RADIUS, 1.0f, 1.0f, 0.0f);
    
    // Draw blocks
    for (int layer = 0; layer < LAYERS; layer++) {
        for (int row = 0; row < BLOCKS_PER_COL; row++) {
            for (int col = 0; col < BLOCKS_PER_ROW; col++) {
                if (blocks[layer][row][col].active) {
                    drawCube(blocks[layer][row][col].x, blocks[layer][row][col].y, blocks[layer][row][col].z,
                           BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_DEPTH,
                           blocks[layer][row][col].r, blocks[layer][row][col].g, blocks[layer][row][col].b);
                }
            }
        }
    }
    
    // Draw boundaries (optional visual guides)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    // Left wall
    glVertex3f(-6.0f, -6.0f, -2.0f); glVertex3f(-6.0f, 8.0f, -2.0f);
    glVertex3f(-6.0f, -6.0f, 4.0f); glVertex3f(-6.0f, 8.0f, 4.0f);
    // Right wall
    glVertex3f(6.0f, -6.0f, -2.0f); glVertex3f(6.0f, 8.0f, -2.0f);
    glVertex3f(6.0f, -6.0f, 4.0f); glVertex3f(6.0f, 8.0f, 4.0f);
    // Back wall
    glVertex3f(-6.0f, -6.0f, 4.0f); glVertex3f(6.0f, -6.0f, 4.0f);
    glVertex3f(-6.0f, 8.0f, 4.0f); glVertex3f(6.0f, 8.0f, 4.0f);
    // Front wall
    glVertex3f(-6.0f, -6.0f, -2.0f); glVertex3f(6.0f, -6.0f, -2.0f);
    glVertex3f(-6.0f, 8.0f, -2.0f); glVertex3f(6.0f, 8.0f, -2.0f);
    glEnd();
    
    glutSwapBuffers();
}

// Keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            if (paddleX > -5.0f) paddleX -= 0.3f;
            break;
        case 'd':
        case 'D':
            if (paddleX < 5.0f) paddleX += 0.3f;
            break;
        case 'r':
        case 'R':
            // Reset game
            paddleX = 0.0f;
            ballX = 0.0f;
            ballY = -5.0f;
            ballZ = 0.0f;
            ballVelX = 0.05f;
            ballVelY = 0.08f;
            ballVelZ = 0.03f;
            gameRunning = true;
            score = 0;
            initBlocks();
            break;
        case 27: // ESC key
            exit(0);
            break;
    }
}

// Special keys (arrow keys)
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if (paddleX > -5.0f) paddleX -= 0.3f;
            break;
        case GLUT_KEY_RIGHT:
            if (paddleX < 5.0f) paddleX += 0.3f;
            break;
    }
}

// Timer callback for animation
void timer(int value) {
    updateGame();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

// Reshape callback
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Initialize OpenGL
void initGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    // Set light position
    GLfloat lightPos[] = {0.0f, 5.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    // Set light colors
    GLfloat lightAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("3D Breakout Game");
    
    // Initialize game
    initGL();
    initBlocks();
    
    // Set callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(16, timer, 0);
    
    // Print instructions
    printf("3D Breakout Game Controls:\n");
    printf("A/D or Arrow Keys: Move paddle left/right\n");
    printf("R: Reset game\n");
    printf("ESC: Exit\n\n");
    
    // Start game loop
    glutMainLoop();
    
    return 0;
}