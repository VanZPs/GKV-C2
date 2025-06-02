#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class Image {
public:
    int width, height;
    unsigned char* pixels;
    
    Image(unsigned char* pixels, int width, int height);
    
    Image(int width, int height);
    
    ~Image();
    
private:
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;
};

Image* loadBMP(const char* filename);

int toInt(const char* bytes, int offset);

GLuint loadTexture(Image* image);

#endif
