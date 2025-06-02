#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Window dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Game constants
#define PADDLE_WIDTH 2.0f
#define PADDLE_HEIGHT 0.3f
#define PADDLE_DEPTH 0.3f
#define BALL_RADIUS 0.15f
#define BLOCK_WIDTH 1.0f
#define BLOCK_HEIGHT 0.4f
#define BLOCK_DEPTH 0.6f
#define BLOCKS_PER_ROW 8
#define BLOCKS_PER_COL 5
#define MAX_LAYERS 3
#define GROUND_LEVEL 0.0f
#define BLOCK_FALL_SPEED 0.05f

// Game variables
float paddleX = 0.0f;
float ballX = 0.0f, ballY = 0.0f, ballZ = 0.0f;
float ballVelX = 0.05f, ballVelY = 0.08f, ballVelZ = 0.03f;
bool gameRunning = true;
int score = 0;
int blocksRemaining;

// Block structure with falling capability
typedef struct {
    float x, y, z;
    bool active;
    bool falling;
    float fallSpeed;
    int targetLayer; // Which layer this block should settle at
    float r, g, b; // Color
} Block;

// Grid to track block positions [row][col] = height of blocks at that position
int blockGrid[BLOCKS_PER_COL][BLOCKS_PER_ROW];
Block blocks[BLOCKS_PER_COL][BLOCKS_PER_ROW][MAX_LAYERS];

// Initialize blocks
void initBlocks() {
    blocksRemaining = 0;
    
    // Clear grid
    for (int row = 0; row < BLOCKS_PER_COL; row++) {
        for (int col = 0; col < BLOCKS_PER_ROW; col++) {
            blockGrid[row][col] = 0;
        }
    }
    
    // Create initial block layout - some stacked, some not
    for (int row = 0; row < BLOCKS_PER_COL; row++) {
        for (int col = 0; col < BLOCKS_PER_ROW; col++) {
            // Vary the number of blocks per column (1-3 blocks high)
            int numBlocks = 1 + (row + col) % MAX_LAYERS;
            blockGrid[row][col] = numBlocks;
            
            for (int layer = 0; layer < numBlocks; layer++) {
                blocks[row][col][layer].x = (col - BLOCKS_PER_ROW/2.0f + 0.5f) * (BLOCK_WIDTH + 0.1f);
                blocks[row][col][layer].y = GROUND_LEVEL + BLOCK_HEIGHT/2 + layer * BLOCK_HEIGHT;
                blocks[row][col][layer].z = 2.0f + row * (BLOCK_DEPTH + 0.1f);
                blocks[row][col][layer].active = true;
                blocks[row][col][layer].falling = false;
                blocks[row][col][layer].fallSpeed = 0.0f;
                blocks[row][col][layer].targetLayer = layer;
                
                // Different colors for different layers
                if (layer == 0) {
                    blocks[row][col][layer].r = 1.0f;
                    blocks[row][col][layer].g = 0.2f;
                    blocks[row][col][layer].b = 0.2f;
                } else if (layer == 1) {
                    blocks[row][col][layer].r = 0.2f;
                    blocks[row][col][layer].g = 1.0f;
                    blocks[row][col][layer].b = 0.2f;
                } else {
                    blocks[row][col][layer].r = 0.2f;
                    blocks[row][col][layer].g = 0.2f;
                    blocks[row][col][layer].b = 1.0f;
                }
                
                blocksRemaining++;
            }
        }
    }
}

// Make blocks fall when support is removed
void updateBlockPhysics() {
    for (int row = 0; row < BLOCKS_PER_COL; row++) {
        for (int col = 0; col < BLOCKS_PER_ROW; col++) {
            // Check each layer from bottom to top
            for (int layer = 0; layer < MAX_LAYERS; layer++) {
                if (blocks[row][col][layer].active) {
                    // Calculate where this block should be based on blocks below it
                    int supportingBlocks = 0;
                    for (int checkLayer = 0; checkLayer < layer; checkLayer++) {
                        if (blocks[row][col][checkLayer].active && !blocks[row][col][checkLayer].falling) {
                            supportingBlocks++;
                        }
                    }
                    
                    float targetY = GROUND_LEVEL + BLOCK_HEIGHT/2 + supportingBlocks * BLOCK_HEIGHT;
                    
                    // If block is above its target position, make it fall
                    if (blocks[row][col][layer].y > targetY + 0.01f) {
                        blocks[row][col][layer].falling = true;
                        blocks[row][col][layer].fallSpeed = BLOCK_FALL_SPEED;
                        blocks[row][col][layer].targetLayer = supportingBlocks;
                    }
                    
                    // Update falling blocks
                    if (blocks[row][col][layer].falling) {
                        blocks[row][col][layer].y -= blocks[row][col][layer].fallSpeed;
                        
                        // Stop falling when reaching target
                        if (blocks[row][col][layer].y <= targetY) {
                            blocks[row][col][layer].y = targetY;
                            blocks[row][col][layer].falling = false;
                            blocks[row][col][layer].fallSpeed = 0.0f;
                        }
                    }
                }
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
    for (int row = 0; row < BLOCKS_PER_COL; row++) {
        for (int col = 0; col < BLOCKS_PER_ROW; col++) {
            for (int layer = 0; layer < MAX_LAYERS; layer++) {
                if (blocks[row][col][layer].active) {
                    if (checkCollision(ballX, ballY, ballZ, BALL_RADIUS,
                                     blocks[row][col][layer].x, blocks[row][col][layer].y, blocks[row][col][layer].z,
                                     BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_DEPTH)) {
                        
                        blocks[row][col][layer].active = false;
                        score += 10;
                        blocksRemaining--;
                        
                        // Update block grid count for this position
                        blockGrid[row][col]--;
                        
                        // Simple collision response - reverse appropriate velocity component
                        float blockCenterX = blocks[row][col][layer].x;
                        float blockCenterY = blocks[row][col][layer].y;
                        float blockCenterZ = blocks[row][col][layer].z;
                        
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
    
    // Update block physics (falling)
    updateBlockPhysics();
    
    // Move ball
    ballX += ballVelX;
    ballY += ballVelY;
    ballZ += ballVelZ;
    
    // Wall collisions (all at ground level)
    if (ballX <= -6.0f || ballX >= 6.0f) {
        ballVelX = -ballVelX;
    }
    if (ballY >= 3.0f) { // Top wall
        ballVelY = -ballVelY;
    }
    if (ballZ <= 0.5f || ballZ >= 6.0f) { // Front and back walls
        ballVelZ = -ballVelZ;
    }
    
    // Paddle collision (at ground level)
    if (ballY <= GROUND_LEVEL + PADDLE_HEIGHT/2 + BALL_RADIUS && ballY >= GROUND_LEVEL - 0.5f &&
        ballX >= paddleX - PADDLE_WIDTH/2 && ballX <= paddleX + PADDLE_WIDTH/2 &&
        ballZ >= -PADDLE_DEPTH/2 && ballZ <= PADDLE_DEPTH/2) {
        
        ballVelY = fabs(ballVelY); // Always bounce up
        
        // Add some spin based on where it hits the paddle
        float hitOffset = (ballX - paddleX) / (PADDLE_WIDTH/2);
        ballVelX += hitOffset * 0.02f;
        
        // Clamp velocity
        if (ballVelX > 0.1f) ballVelX = 0.1f;
        if (ballVelX < -0.1f) ballVelX = -0.1f;
    }
    
    // Check for game over (ball falls below ground)
    if (ballY < GROUND_LEVEL - 1.0f) {
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
    
    // Set camera position (angled above and behind, adjusted for ground level)
    gluLookAt(0.0, -12.0, 8.0,    // Eye position
              0.0, 1.0, 3.0,     // Look at center
              0.0, 1.0, 0.0);    // Up vector
    
    // Draw ground plane
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-8.0f, GROUND_LEVEL - 0.1f, -1.0f);
    glVertex3f(8.0f, GROUND_LEVEL - 0.1f, -1.0f);
    glVertex3f(8.0f, GROUND_LEVEL - 0.1f, 8.0f);
    glVertex3f(-8.0f, GROUND_LEVEL - 0.1f, 8.0f);
    glEnd();
    
    // Draw paddle (at ground level)
    drawCube(paddleX, GROUND_LEVEL + PADDLE_HEIGHT/2, 0.0f, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_DEPTH, 0.8f, 0.8f, 0.8f);
    
    // Draw ball
    drawSphere(ballX, ballY, ballZ, BALL_RADIUS, 1.0f, 1.0f, 0.0f);
    
    // Draw blocks
    for (int row = 0; row < BLOCKS_PER_COL; row++) {
        for (int col = 0; col < BLOCKS_PER_ROW; col++) {
            for (int layer = 0; layer < MAX_LAYERS; layer++) {
                if (blocks[row][col][layer].active) {
                    drawCube(blocks[row][col][layer].x, blocks[row][col][layer].y, blocks[row][col][layer].z,
                           BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_DEPTH,
                           blocks[row][col][layer].r, blocks[row][col][layer].g, blocks[row][col][layer].b);
                }
            }
        }
    }
    
    // Draw walls (at ground level)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    // Left wall
    glVertex3f(-6.0f, GROUND_LEVEL, 0.5f); glVertex3f(-6.0f, 3.0f, 0.5f);
    glVertex3f(-6.0f, GROUND_LEVEL, 6.0f); glVertex3f(-6.0f, 3.0f, 6.0f);
    // Right wall
    glVertex3f(6.0f, GROUND_LEVEL, 0.5f); glVertex3f(6.0f, 3.0f, 0.5f);
    glVertex3f(6.0f, GROUND_LEVEL, 6.0f); glVertex3f(6.0f, 3.0f, 6.0f);
    // Back wall
    glVertex3f(-6.0f, GROUND_LEVEL, 6.0f); glVertex3f(6.0f, GROUND_LEVEL, 6.0f);
    glVertex3f(-6.0f, 3.0f, 6.0f); glVertex3f(6.0f, 3.0f, 6.0f);
    // Top edges
    glVertex3f(-6.0f, 3.0f, 0.5f); glVertex3f(6.0f, 3.0f, 0.5f);
    glVertex3f(-6.0f, 3.0f, 6.0f); glVertex3f(6.0f, 3.0f, 6.0f);
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
            ballY = 0.5f;
            ballZ = 1.0f;
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
    GLfloat lightPos[] = {0.0f, 5.0f, 2.0f, 1.0f};
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
    glutCreateWindow("3D Breakout Game - Block Drop Edition");
    
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
    printf("3D Breakout Game - Block Drop Edition Controls:\n");
    printf("A/D or Arrow Keys: Move paddle left/right\n");
    printf("R: Reset game\n");
    printf("ESC: Exit\n");
    printf("Watch blocks fall when support is removed!\n\n");
    
    // Start game loop
    glutMainLoop();
    
    return 0;
}