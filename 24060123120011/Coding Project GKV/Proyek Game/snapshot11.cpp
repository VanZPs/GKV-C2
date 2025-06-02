#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <random>
#include "Environment/live.cpp"

using namespace std;

// Window dimensions
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

// Game constants
#define PADDLE_WIDTH_DEFAULT 2.0f
#define PADDLE_HEIGHT 0.3f
#define PADDLE_DEPTH 0.3f
#define PADDLE_SPEED_DEFAULT 0.1f
#define BALL_RADIUS_DEFAULT 0.15f
#define BLOCK_WIDTH 1.0f
#define BLOCK_HEIGHT 0.4f
#define BLOCK_DEPTH 0.6f
#define BLOCKS_PER_ROW_LAYER0 8
#define BLOCKS_PER_COL_LAYER0 8
#define BLOCKS_PER_ROW_LAYER1 6
#define BLOCKS_PER_COL_LAYER1 6
#define LAYERS 2
#define FALL_SPEED 0.02f
#define INITIAL_LIVES 3

// Game variables
float paddleX = 0.0f;
float ballX = 0.0f, ballY = -5.0f, ballZ = 0.0f;
float ballVelX = 0.05f, ballVelY = 0.08f;
bool gameRunning = true;
int score = 0;
int lives = INITIAL_LIVES;
int blocksRemaining;
bool leftPressed = false;
bool rightPressed = false;
float paddleSpeed = PADDLE_SPEED_DEFAULT;
bool ballActive = true;

// Block structure - enhanced with falling mechanics
typedef struct {
    float x, y, z;
    float targetY;
    bool active;
    bool falling;
    float fallVel;
    float r, g, b;
} Block;

Block blocks[LAYERS][8][8];  // Use maximum dimensions for array

// Get the number of rows and columns for each layer
int getRowsForLayer(int layer) {
    return (layer == 0) ? BLOCKS_PER_COL_LAYER0 : BLOCKS_PER_COL_LAYER1;
}

int getColsForLayer(int layer) {
    return (layer == 0) ? BLOCKS_PER_ROW_LAYER0 : BLOCKS_PER_ROW_LAYER1;
}

// Reset ball position and velocity
void resetBall() {
    ballX = 0.0f;
    ballY = -5.0f;
    ballZ = 0.0f;
    ballVelX = 0.05f;
    ballVelY = 0.08f;
    ballActive = true;
}

// Initialize blocks
void initBlocks() {
    blocksRemaining = BLOCKS_PER_ROW_LAYER0 * BLOCKS_PER_COL_LAYER0 + BLOCKS_PER_ROW_LAYER1 * BLOCKS_PER_COL_LAYER1;
    
    for (int layer = 0; layer < LAYERS; layer++) {
        int rows = getRowsForLayer(layer);
        int cols = getColsForLayer(layer);
        
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                // Center the blocks for each layer on both X and Y axes
                blocks[layer][row][col].x = (col - cols/2.0f + 0.5f) * (BLOCK_WIDTH + 0.1f);
                
                // Center Y-axis: calculate offset to center this layer relative to the base layer
                float baseY = 2.0f;
                float yOffset = (BLOCKS_PER_COL_LAYER0 - rows) * (BLOCK_HEIGHT + 0.1f) / 2.0f;
                blocks[layer][row][col].y = baseY + yOffset + row * (BLOCK_HEIGHT + 0.1f);
                
                blocks[layer][row][col].z = layer * (BLOCK_DEPTH + 0.2f);
                blocks[layer][row][col].targetY = blocks[layer][row][col].y;
                blocks[layer][row][col].active = true;
                blocks[layer][row][col].falling = false;
                blocks[layer][row][col].fallVel = 0.0f;
                
                // Different colors for different layers
                if (layer == 0) {
                    float color_r[3] = {1.0f, 0.2f, 0.2f};
                    float color_g[3] = {0.2f, 1.0f, 0.2f};
                    float color_b[3] = {0.2f, 0.2f, 1.0f};
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(0, 2);
                    int colorRoll = distrib(gen);
                    blocks[layer][row][col].r = color_r[colorRoll];
                    blocks[layer][row][col].g = color_g[colorRoll];
                    blocks[layer][row][col].b = color_b[colorRoll];
                } else {
                    float color_r[3] = {0.0f, 1.0f, 1.0f};
                    float color_g[3] = {1.0f, 0.0f, 1.0f};
                    float color_b[3] = {1.0f, 1.0f, 0.0f};
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(0, 2);
                    int colorRoll = distrib(gen);
                    blocks[layer][row][col].r = color_r[colorRoll];
                    blocks[layer][row][col].g = color_g[colorRoll];
                    blocks[layer][row][col].b = color_b[colorRoll];
                }
            }
        }
        
        // Mark unused slots as inactive
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (row >= rows || col >= cols) {
                    blocks[layer][row][col].active = false;
                }
            }
        }
    }
}

// Check if a block has support beneath it (enhanced for different layer sizes)
bool hasSupport(int layer, int row, int col) {
    if (layer == 0) return true; // Front layer always has support
    
    // For layer 1 (6x6), check if there's support in the corresponding area of layer 0 (8x8)
    // We need to map the 6x6 position to the 8x8 layer beneath
    
    // Calculate the offset to center the 6x6 grid over the 8x8 grid
    int offsetRow = (BLOCKS_PER_COL_LAYER0 - BLOCKS_PER_COL_LAYER1) / 2;
    int offsetCol = (BLOCKS_PER_ROW_LAYER0 - BLOCKS_PER_ROW_LAYER1) / 2;
    
    int supportRow = row + offsetRow;
    int supportCol = col + offsetCol;
    
    // Check if the corresponding block in layer 0 exists and is active
    if (supportRow >= 0 && supportRow < BLOCKS_PER_COL_LAYER0 && 
        supportCol >= 0 && supportCol < BLOCKS_PER_ROW_LAYER0) {
        return blocks[0][supportRow][supportCol].active;
    }
    
    return false;
}

// Make blocks fall if they lose support
void updateFallingBlocks() {
    for (int layer = 1; layer < LAYERS; layer++) {
        int rows = getRowsForLayer(layer);
        int cols = getColsForLayer(layer);
        
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (blocks[layer][row][col].active && !blocks[layer][row][col].falling) {
                    if (!hasSupport(layer, row, col)) {
                        blocks[layer][row][col].falling = true;
                        blocks[layer][row][col].fallVel = 0.0f;
                    }
                }
                
                // Update falling blocks
                if (blocks[layer][row][col].falling) {
                    blocks[layer][row][col].fallVel += 0.01f;
                    blocks[layer][row][col].z -= blocks[layer][row][col].fallVel;
                    
                    float targetZ = blocks[0][0][0].z;
                    if (blocks[layer][row][col].z <= targetZ) {
                        blocks[layer][row][col].z = targetZ;
                        blocks[layer][row][col].falling = false;
                        blocks[layer][row][col].fallVel = 0.0f;
                        
                        // Calculate where to place the fallen block in layer 0
                        int offsetRow = (BLOCKS_PER_COL_LAYER0 - BLOCKS_PER_COL_LAYER1) / 2;
                        int offsetCol = (BLOCKS_PER_ROW_LAYER0 - BLOCKS_PER_ROW_LAYER1) / 2;
                        
                        int targetRow = row + offsetRow;
                        int targetCol = col + offsetCol;
                        
                        if (targetRow >= 0 && targetRow < BLOCKS_PER_COL_LAYER0 && 
                            targetCol >= 0 && targetCol < BLOCKS_PER_ROW_LAYER0) {
                            blocks[0][targetRow][targetCol] = blocks[layer][row][col];
                            blocks[0][targetRow][targetCol].z = targetZ;
                        }
                        
                        blocks[layer][row][col].active = false;
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
    glRotated(0.0f, 0.0f, 0.0f, 0.0f);
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

// Draw text on screen
void drawText(float x, float y, const char* text, float r, float g, float b) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// Check collision between ball and box
bool checkCollision(float ballX, float ballY, float ballZ, float ballRadius,
                   float boxX, float boxY, float boxZ, float boxWidth, float boxHeight, float boxDepth) {
    float closestX = fmax(boxX - boxWidth/2, fmin(ballX, boxX + boxWidth/2));
    float closestY = fmax(boxY - boxHeight/2, fmin(ballY, boxY + boxHeight/2));
    
    float distanceX = ballX - closestX;
    float distanceY = ballY - closestY;
    
    float distanceSquared = distanceX * distanceX + distanceY * distanceY;
    
    return distanceSquared < (ballRadius * ballRadius);
}

// Improved collision detection with proper surface detection
struct CollisionInfo {
    bool occurred;
    float penetrationX, penetrationY;
    int hitLayer, hitRow, hitCol;
};

// Better collision detection that determines the collision surface
CollisionInfo checkBlockCollision(float ballX, float ballY, float ballRadius,
                                 float blockX, float blockY, float blockWidth, float blockHeight) {
    CollisionInfo info = {false, 0, 0, -1, -1, -1};
    
    float leftEdge = blockX - blockWidth/2;
    float rightEdge = blockX + blockWidth/2;
    float topEdge = blockY + blockHeight/2;
    float bottomEdge = blockY - blockHeight/2;
    
    if (ballX + ballRadius >= leftEdge && ballX - ballRadius <= rightEdge &&
        ballY + ballRadius >= bottomEdge && ballY - ballRadius <= topEdge) {
        
        info.occurred = true;
        
        float penetrationLeft = (ballX + ballRadius) - leftEdge;
        float penetrationRight = rightEdge - (ballX - ballRadius);
        float penetrationTop = topEdge - (ballY - ballRadius);
        float penetrationBottom = (ballY + ballRadius) - bottomEdge;
        
        float minPenetration = fmin(fmin(penetrationLeft, penetrationRight), 
                                   fmin(penetrationTop, penetrationBottom));
        
        if (minPenetration == penetrationLeft) {
            info.penetrationX = -penetrationLeft;
        } else if (minPenetration == penetrationRight) {
            info.penetrationX = penetrationRight;
        } else if (minPenetration == penetrationTop) {
            info.penetrationY = penetrationTop;
        } else {
            info.penetrationY = -penetrationBottom;
        }
    }
    
    return info;
}

// Improved block collision handling with proper response
void handleBlockCollisions() {
    if (!ballActive) return;
    
    float prevBallX = ballX - ballVelX;
    float prevBallY = ballY - ballVelY;
    
    CollisionInfo collision = {false, 0, 0, -1, -1, -1};
    float closestDistance = 1000.0f;
    
    // Find the closest collision
    for (int layer = 0; layer < LAYERS; layer++) {
        int rows = getRowsForLayer(layer);
        int cols = getColsForLayer(layer);
        
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (blocks[layer][row][col].active) {
                    CollisionInfo info = checkBlockCollision(ballX, ballY, BALL_RADIUS_DEFAULT,
                                                           blocks[layer][row][col].x, 
                                                           blocks[layer][row][col].y,
                                                           BLOCK_WIDTH, BLOCK_HEIGHT);
                    
                    if (info.occurred) {
                        float distance = sqrt(pow(ballX - blocks[layer][row][col].x, 2) + 
                                            pow(ballY - blocks[layer][row][col].y, 2));
                        
                        if (distance < closestDistance) {
                            closestDistance = distance;
                            collision = info;
                            collision.hitLayer = layer;
                            collision.hitRow = row;
                            collision.hitCol = col;
                        }
                    }
                }
            }
        }
    }
    
    // Handle the closest collision only
    if (collision.occurred) {
        blocks[collision.hitLayer][collision.hitRow][collision.hitCol].active = false;
        score += 10;
        blocksRemaining--;
        
        ballX += collision.penetrationX;
        ballY += collision.penetrationY;
        
        if (collision.penetrationX != 0) {
            ballVelX = -ballVelX;
        }
        if (collision.penetrationY != 0) {
            ballVelY = -ballVelY;
        }
        
        // Clamp velocities
        if (ballVelX > 0.12f) ballVelX = 0.12f;
        if (ballVelX < -0.12f) ballVelX = -0.12f;
        if (ballVelY > 0.12f) ballVelY = 0.12f;
        if (ballVelY < -0.12f) ballVelY = -0.12f;
        
        // Ensure minimum speed
        if (fabs(ballVelX) < 0.02f) ballVelX = (ballVelX >= 0) ? 0.02f : -0.02f;
        if (fabs(ballVelY) < 0.02f) ballVelY = (ballVelY >= 0) ? 0.02f : -0.02f;
    }
}

// Update game physics
void updateGame() {
    if (!gameRunning) return;

    // Smooth paddle movement
    if (leftPressed && paddleX > -5.0f) {
        paddleX -= paddleSpeed;
        if (paddleX < -5.0f) paddleX = -5.0f;
    }
    if (rightPressed && paddleX < 5.0f) {
        paddleX += paddleSpeed;
        if (paddleX > 5.0f) paddleX = 5.0f;
    }

    // Update falling blocks
    updateFallingBlocks();

    // Only update ball if it's active
    if (ballActive) {
        float prevBallX = ballX;
        float prevBallY = ballY;
        
        handleBlockCollisions();
        
        // Move ball
        ballX += ballVelX;
        ballY += ballVelY;
        
        // Wall collisions
        if (ballX <= -6.0f || ballX >= 6.0f) {
            ballVelX = -ballVelX;
            ballX = (ballX <= -6.0f) ? -6.0f + BALL_RADIUS_DEFAULT : 6.0f - BALL_RADIUS_DEFAULT;
        }
        if (ballY >= 8.0f) {
            ballVelY = -ballVelY;
            ballY = 8.0f - BALL_RADIUS_DEFAULT;
        }
        
        // Paddle collision
        if (ballY <= -5.5f && ballY >= -6.0f &&
            ballX >= paddleX - PADDLE_WIDTH_DEFAULT/2 && ballX <= paddleX + PADDLE_WIDTH_DEFAULT/2) {
            
            ballVelY = fabs(ballVelY);
            
            float hitOffset = (ballX - paddleX) / (PADDLE_WIDTH_DEFAULT/2);
            ballVelX += hitOffset * 0.1f;
            
            if (ballVelX > 0.1f) ballVelX = 0.1f;
            if (ballVelX < -0.1f) ballVelX = -0.1f;
        }
        
        // Check if ball fell below paddle
        if (ballY < -7.0f) {
            lives--;
            printf("Ball lost! Lives remaining: %d\n", lives);
            
            if (lives >= 0) {
                // Respawn ball
                resetBall();
            } else {
                // Game over
                gameRunning = false;
                ballActive = false;
                printf("Game Over! Final Score: %d\n", score);
            }
        }
    }
    
    // Check for win
    if (blocksRemaining == 0) {
        gameRunning = false;
        printf("You Win! Final Score: %d\n", score);
    }
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Set camera position
    gluLookAt(0.0, -8.0, 12.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    drawEnvironmentBoundaries();
    drawEnvironmentFloor();
    drawEnvironmentParticles();
    
    // Draw paddle
    drawCube(paddleX, -5.8f, 0.0f, PADDLE_WIDTH_DEFAULT, PADDLE_HEIGHT, PADDLE_DEPTH, 0.8f, 0.8f, 0.8f);
    
    // Draw ball only if active
    if (ballActive) {
        drawSphere(ballX, ballY, ballZ, BALL_RADIUS_DEFAULT, 1.0f, 1.0f, 0.0f);
    }
    
    // Draw blocks
    for (int layer = 0; layer < LAYERS; layer++) {
        int rows = getRowsForLayer(layer);
        int cols = getColsForLayer(layer);
        
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (blocks[layer][row][col].active) {
                    drawCube(blocks[layer][row][col].x, blocks[layer][row][col].y, blocks[layer][row][col].z,
                           BLOCK_WIDTH, BLOCK_HEIGHT, BLOCK_DEPTH,
                           blocks[layer][row][col].r, blocks[layer][row][col].g, blocks[layer][row][col].b);
                }
            }
        }
    }
    
    // Draw boundaries
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
    
    // Draw UI text
    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);
    drawText(20, WINDOW_HEIGHT - 30, scoreText, 0.0f, 1.0f, 1.0f);
    
    char livesText[50];
    sprintf(livesText, "Lives: %d", lives);
    drawText(20, WINDOW_HEIGHT - 60, livesText, 1.0f, 1.0f, 0.0f);
    
    if (!gameRunning) {
        if (blocksRemaining == 0) {
            drawText(20, WINDOW_HEIGHT - 90, "YOU WIN!", 0.0f, 1.0f, 0.0f);
        } else {
            drawText(20, WINDOW_HEIGHT - 90, "GAME OVER", 1.0f, 0.0f, 0.0f);
        }
        drawText(20, WINDOW_HEIGHT - 120, "Press 'R' to restart...", 1.0f, 1.0f, 1.0f);
    }
    
    glutSwapBuffers();
}

// Keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            leftPressed = true;
            break;
        case 'd':
        case 'D':
            rightPressed = true;
            break;
        case 'r':
        case 'R':
            // Reset game
            paddleX = 0.0f;
            gameRunning = true;
            score = 0;
            lives = INITIAL_LIVES;
            leftPressed = false;
            rightPressed = false;
            resetBall();
            initBlocks();
            break;        
        case 27: // ESC key
            exit(0);
            break;
        // Keys for debugging
        case '+':
            lives++;
            break;
        case '-':
            lives--;
            break;
        case '[':
            blocksRemaining = 100;
            gameRunning = false;
            break;
        case ']':
            blocksRemaining = 0;
            gameRunning = false;
            break;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
        case 'A':
            leftPressed = false;
            break;
        case 'd':
        case 'D':
            rightPressed = false;
            break;
    }
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            leftPressed = true;
            break;
        case GLUT_KEY_RIGHT:
            rightPressed = true;
            break;
    }
}

void specialKeysUp(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            leftPressed = false;
            break;
        case GLUT_KEY_RIGHT:
            rightPressed = false;
            break;
    }
}

void timer(int value) {
    updateGame();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void initGL() {
    glEnable(GL_DEPTH_TEST);
    initEnvironment();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    GLfloat lightPos[] = {0.0f, 5.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    GLfloat lightAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("3D Breakout Game - Pyramid Structure with Lives");
    
    initGL();
    initBlocks();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(specialKeysUp);
    glutTimerFunc(16, timer, 0);
    
    printf("3D Breakout Game with Pyramid Block Structure and Lives System:\n");
    printf("A/D or Arrow Keys: Move paddle left/right\n");
    printf("R: Reset game\n");
    printf("ESC: Exit\n");
    printf("You start with %d lives. Don't let the ball fall!\n", INITIAL_LIVES);
    printf("Bottom layer: 8x8 blocks, Top layer: 6x6 blocks (centered)\n");
    printf("Destroy bottom blocks to make top blocks fall!\n\n");
    
    glutMainLoop();
    
    return 0;
}
