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
#define PADDLE_SPEED_DEFAULT 0.1f
#define BALL_RADIUS_DEFAULT 0.15f
#define BLOCK_WIDTH 1.0f
#define BLOCK_HEIGHT 0.4f
#define BLOCK_DEPTH 0.6f
#define BLOCKS_PER_ROW 8
#define BLOCKS_PER_COL 8
#define LAYERS 1

// Game variables
float paddleX = 0.0f;
float ballX = 0.0f, ballY = -5.0f, ballZ = 0.0f;
float ballVelX = 0.05f, ballVelY = 0.08f;
bool gameRunning = true;
int score = 0;
int blocksRemaining;
bool leftPressed = false;
bool rightPressed = false;
float paddleSpeed = PADDLE_SPEED_DEFAULT;

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
    
    // Calculate distance between ball center and closest point
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
    
    // Calculate distances to block edges
    float leftEdge = blockX - blockWidth/2;
    float rightEdge = blockX + blockWidth/2;
    float topEdge = blockY + blockHeight/2;
    float bottomEdge = blockY - blockHeight/2;
    
    // Check if ball is overlapping with block
    if (ballX + ballRadius >= leftEdge && ballX - ballRadius <= rightEdge &&
        ballY + ballRadius >= bottomEdge && ballY - ballRadius <= topEdge) {
        
        info.occurred = true;
        
        // Calculate penetration depths for each side
        float penetrationLeft = (ballX + ballRadius) - leftEdge;
        float penetrationRight = rightEdge - (ballX - ballRadius);
        float penetrationTop = topEdge - (ballY - ballRadius);
        float penetrationBottom = (ballY + ballRadius) - bottomEdge;
        
        // Find the minimum penetration (the side that was hit)
        float minPenetration = fmin(fmin(penetrationLeft, penetrationRight), 
                                   fmin(penetrationTop, penetrationBottom));
        
        if (minPenetration == penetrationLeft) {
            info.penetrationX = -penetrationLeft; // Hit left side, push ball left
        } else if (minPenetration == penetrationRight) {
            info.penetrationX = penetrationRight; // Hit right side, push ball right
        } else if (minPenetration == penetrationTop) {
            info.penetrationY = penetrationTop; // Hit top side, push ball up
        } else {
            info.penetrationY = -penetrationBottom; // Hit bottom side, push ball down
        }
    }
    
    return info;
}

// Improved block collision handling with proper response
void handleBlockCollisions() {
    // Store the ball's previous position for rollback if needed
    float prevBallX = ballX - ballVelX;
    float prevBallY = ballY - ballVelY;
    
    CollisionInfo collision = {false, 0, 0, -1, -1, -1};
    float closestDistance = 1000.0f; // Large number
    
    // Find the closest collision
    for (int layer = 0; layer < LAYERS; layer++) {
        for (int row = 0; row < BLOCKS_PER_COL; row++) {
            for (int col = 0; col < BLOCKS_PER_ROW; col++) {
                if (blocks[layer][row][col].active) {
                    CollisionInfo info = checkBlockCollision(ballX, ballY, BALL_RADIUS_DEFAULT,
                                                           blocks[layer][row][col].x, 
                                                           blocks[layer][row][col].y,
                                                           BLOCK_WIDTH, BLOCK_HEIGHT);
                    
                    if (info.occurred) {
                        // Calculate distance to this block
                        float distance = sqrt(pow(ballX - blocks[layer][row][col].x, 2) + 
                                            pow(ballY - blocks[layer][row][col].y, 2));
                        
                        // Keep track of the closest collision
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
        // Remove the block
        blocks[collision.hitLayer][collision.hitRow][collision.hitCol].active = false;
        score += 10;
        blocksRemaining--;
        
        // Move ball out of the block to prevent tunneling
        ballX += collision.penetrationX;
        ballY += collision.penetrationY;
        
        // Bounce the ball based on which surface was hit
        if (collision.penetrationX != 0) {
            ballVelX = -ballVelX;
        }
        if (collision.penetrationY != 0) {
            ballVelY = -ballVelY;
        }
        
        // Optional: Add slight random variation to prevent predictable patterns
        // float randomFactor = 0.02f;
        // ballVelX += ((float)rand() / RAND_MAX - 0.5f) * randomFactor;
        // ballVelY += ((float)rand() / RAND_MAX - 0.5f) * randomFactor;
        
        // Clamp velocities to reasonable limits
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
        if (paddleX < -5.0f) paddleX = -5.0f;  // Clamp to boundary
    }
    if (rightPressed && paddleX < 5.0f) {
        paddleX += paddleSpeed;
        if (paddleX > 5.0f) paddleX = 5.0f;   // Clamp to boundary
    }

    // Store previous ball position
    float prevBallX = ballX;
    float prevBallY = ballY;
    
    // Check collisions BEFORE moving the ball (predictive)
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
        
        ballVelY = fabs(ballVelY); // Always bounce up
        
        // Add some spin based on where it hits the paddle
        float hitOffset = (ballX - paddleX) / (PADDLE_WIDTH_DEFAULT/2);
        ballVelX += hitOffset * 0.1f;
        
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
    drawSphere(ballX, ballY, ballZ, BALL_RADIUS_DEFAULT, 1.0f, 1.0f, 0.0f);
    
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
            leftPressed = true;
            // if (paddleX > -5.0f) paddleX -= 0.3f;
            break;
        case 'd':
        case 'D':
            rightPressed = true;
            // if (paddleX < 5.0f) paddleX += 0.3f;
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
            gameRunning = true;
            score = 0;
            leftPressed = false;
            rightPressed = false;
            initBlocks();
            break;
        case 27: // ESC key
            exit(0);
            break;
    }
}

// Add keyboard up function - tracks key release
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

// Special keys (arrow keys)
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            leftPressed = true;
            // if (paddleX > -5.0f) paddleX -= 0.3f;
            break;
        case GLUT_KEY_RIGHT:
            rightPressed = true;
            // if (paddleX < 5.0f) paddleX += 0.3f;
            break;
    }
}

// Add special keys up function - tracks arrow key release
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
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(specialKeysUp);
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