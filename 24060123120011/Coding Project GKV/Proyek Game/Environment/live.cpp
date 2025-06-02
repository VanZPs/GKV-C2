#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// Texture ID for wood texture
GLuint woodTextureID;

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
    
    // Read the 54-byte header
    if (fread(header, 1, 54, file) != 54) {
        printf("Error: Not a correct BMP file\n");
        fclose(file);
        return 0;
    }
    
    // Check if it's a BMP file
    if (header[0] != 'B' || header[1] != 'M') {
        printf("Error: Not a BMP file\n");
        fclose(file);
        return 0;
    }
    
    // Read image information
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    
    // Some BMP files have missing information
    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;
    
    // Create buffer
    data = new unsigned char[imageSize];
    
    // Read the actual data from file
    fseek(file, dataPos, SEEK_SET);
    fread(data, 1, imageSize, file);
    fclose(file);
    
    // Convert BGR to RGB (BMP stores in BGR format)
    for (unsigned int i = 0; i < imageSize; i += 3) {
        unsigned char temp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = temp;
    }
    
    // Generate OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    delete[] data;
    return textureID;
}

// Initialize environment (load textures)
void initEnvironment() {
    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    
    // Load wood texture
    woodTextureID = loadBMPTexture("Environment/wood.bmp");
    if (woodTextureID == 0) {
        printf("Warning: Failed to load wood texture. Walls will be untextured.\n");
    }
}

// Draw textured quad
void drawTexturedQuad(float x1, float y1, float z1, float x2, float y2, float z2, 
                     float x3, float y3, float z3, float x4, float y4, float z4,
                     float texRepeatX = 1.0f, float texRepeatY = 1.0f) {
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z1);
        glTexCoord2f(texRepeatX, 0.0f); glVertex3f(x2, y2, z2);
        glTexCoord2f(texRepeatX, texRepeatY); glVertex3f(x3, y3, z3);
        glTexCoord2f(0.0f, texRepeatY); glVertex3f(x4, y4, z4);
    glEnd();
}

// Draw environment boundaries with wood texture
void drawEnvironmentBoundaries() {
    if (woodTextureID == 0) return; // Don't draw if texture failed to load
    
    // Enable texturing and bind wood texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, woodTextureID);
    glColor3f(1.0f, 1.0f, 1.0f); // White color to show texture properly
    
    // Calculate texture repeat based on wall size
    float wallWidth = 12.0f;  // Width of walls (from -6 to 6)
    float wallHeight = 14.0f; // Height of walls (from -6 to 8)
    float wallDepth = 6.0f;   // Depth of walls (from -2 to 4)
    
    // Texture repetition for better visual appearance
    float texRepeatX = wallWidth / 2.0f;  // Repeat texture every 2 units
    float texRepeatY = wallHeight / 2.0f; // Repeat texture every 2 units
    float texRepeatZ = wallDepth / 2.0f;  // Repeat texture every 2 units
    
    // Bottom wall (parallel to y-plane) - floor level
    drawTexturedQuad(-6.0f, -6.0f, -2.0f,  // Bottom left front
                     6.0f, -6.0f, -2.0f,   // Bottom right front
                     6.0f, -6.0f, 4.0f,    // Bottom right back
                     -6.0f, -6.0f, 4.0f,   // Bottom left back
                     texRepeatX, texRepeatZ);
    
    // Left wall (parallel to z-plane)
    drawTexturedQuad(-6.0f, -6.0f, -2.0f,  // Bottom front
                     -6.0f, -6.0f, 4.0f,   // Bottom back
                     -6.0f, 8.0f, 4.0f,    // Top back
                     -6.0f, 8.0f, -2.0f,   // Top front
                     texRepeatZ, texRepeatY);
    
    // Right wall (parallel to z-plane)
    drawTexturedQuad(6.0f, -6.0f, 4.0f,    // Bottom back
                     6.0f, -6.0f, -2.0f,   // Bottom front
                     6.0f, 8.0f, -2.0f,    // Top front
                     6.0f, 8.0f, 4.0f,     // Top back
                     texRepeatZ, texRepeatY);
    
    // Top wall (parallel to x-plane) - ceiling
    drawTexturedQuad(-6.0f, 8.0f, 4.0f,    // Top left back
                     6.0f, 8.0f, 4.0f,     // Top right back
                     6.0f, 8.0f, -2.0f,    // Top right front
                     -6.0f, 8.0f, -2.0f,   // Top left front
                     texRepeatX, texRepeatZ);
    
    // Back wall (parallel to x-plane) - optional, for enclosed feeling
    drawTexturedQuad(-6.0f, -6.0f, 4.0f,   // Bottom left
                     6.0f, -6.0f, 4.0f,    // Bottom right
                     6.0f, 8.0f, 4.0f,     // Top right
                     -6.0f, 8.0f, 4.0f,    // Top left
                     texRepeatX, texRepeatY);
    
    glDisable(GL_TEXTURE_2D);
}

// Placeholder for floor drawing (to be implemented later)
void drawEnvironmentFloor() {
    // TODO: Implement floor drawing with different texture/pattern
    // This is left empty as requested - for later implementation
}

// Placeholder for particle effects (to be implemented later)
void drawEnvironmentParticles() {
    // TODO: Implement particle effects
    // This is left empty as requested - for later implementation
}