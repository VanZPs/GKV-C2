#ifndef LIVE_ENVIRONMENT_H
#define LIVE_ENVIRONMENT_H

#include <GL/glut.h>

// Environment constants
#define ENV_BOUNDARY_COLOR_R 0.3f
#define ENV_BOUNDARY_COLOR_G 0.3f
#define ENV_BOUNDARY_COLOR_B 0.3f

#define ENV_WALL_LEFT -6.0f
#define ENV_WALL_RIGHT 6.0f
#define ENV_WALL_BOTTOM -6.0f
#define ENV_WALL_TOP 8.0f
#define ENV_WALL_FRONT -2.0f
#define ENV_WALL_BACK 4.0f

#define ENV_LIGHT_POS_X 0.0f
#define ENV_LIGHT_POS_Y 5.0f
#define ENV_LIGHT_POS_Z 5.0f

#define ENV_BACKGROUND_R 0.1f
#define ENV_BACKGROUND_G 0.1f
#define ENV_BACKGROUND_B 0.2f

// Floor constants
#define FLOOR_THICKNESS 0.5f
#define FLOOR_Y_POSITION (ENV_WALL_BOTTOM - FLOOR_THICKNESS/2)

// Environment function declarations
void initEnvironment();
void drawEnvironmentBoundaries();
void setupEnvironmentLighting();
bool isWithinEnvironmentBounds(float x, float y, float z);
void drawEnvironmentFloor();
void drawEnvironmentParticles(); // For future effects
GLuint loadBMPTexture(const char* filename);
void enableTexturing();
void disableTexturing();

#endif // LIVE_ENVIRONMENT_H