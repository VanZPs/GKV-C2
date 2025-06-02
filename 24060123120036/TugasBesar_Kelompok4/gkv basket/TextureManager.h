#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "platform.h"

class TextureManager {
public:
    // Fungsi untuk memuat tekstur BMP
    static GLuint loadBMP(const char * imagepath);

    // ID Tekstur
    static GLuint tex_court_floor;
    static GLuint tex_backboard;
    static GLuint tex_sky_front, tex_sky_back, tex_sky_left, tex_sky_right, tex_sky_up, tex_sky_down;

    static void initTextures();
};

#endif 
