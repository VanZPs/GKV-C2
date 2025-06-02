#include "TextureManager.h"
#include <fstream>
#include <vector>
#include <iostream>

GLuint TextureManager::tex_court_floor = 0;
GLuint TextureManager::tex_backboard = 0;
GLuint TextureManager::tex_sky_front = 0;
GLuint TextureManager::tex_sky_back = 0;
GLuint TextureManager::tex_sky_left = 0;
GLuint TextureManager::tex_sky_right = 0;
GLuint TextureManager::tex_sky_up = 0;
GLuint TextureManager::tex_sky_down = 0;

GLuint TextureManager::loadBMP(const char * imagepath) {
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    unsigned char * data;

    FILE * file = fopen(imagepath, "rb");
    if (!file){
        std::cerr << "Error: Image could not be opened - " << imagepath << std::endl;
        return 0;
    }

    if (fread(header, 1, 54, file) != 54 ){
        std::cerr << "Error: Not a correct BMP file (header problem) - " << imagepath << std::endl;
        fclose(file);
        return 0;
    }

    if (header[0] != 'B' || header[1] != 'M'){
        std::cerr << "Error: Not a correct BMP file (invalid signature) - " << imagepath << std::endl;
        fclose(file);
        return 0;
    }

    if (*(int*)&(header[0x1E]) != 0) {
        std::cerr << "Error: BMP file is compressed (not supported) - " << imagepath << std::endl;
        fclose(file);
        return 0;
    }

    if (*(int*)&(header[0x1C]) != 24) {
        std::cerr << "Error: BMP file is not 24 bits per pixel (not supported) - " << imagepath << std::endl;
        fclose(file);
        return 0;
    }

    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;

    data = new unsigned char [imageSize];
    if (ftell(file) != dataPos) {
        fseek(file, dataPos, SEEK_SET);
    }
    fread(data, 1, imageSize, file);
    fclose(file);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    for (unsigned int i = 0; i < imageSize; i += 3) {
        unsigned char temp = data[i];
        data[i] = data[i+2];
        data[i+2] = temp;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    delete [] data;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return textureID;
}

void TextureManager::initTextures() {
    tex_sky_front = loadBMP("textures/sky_front.bmp");
    tex_sky_back = loadBMP("textures/sky_back.bmp");
    tex_sky_left = loadBMP("/Users/ladyakalascha/Downloads/gkv basket basic copy 2/textures/sky_left.bmp");
    tex_sky_right = loadBMP("Users/ladyakalascha/Downloads/gkv basket basic copy 2/textures/sky_right.bmp");
    tex_sky_up = loadBMP("textures/sky_up.bmp");
    tex_sky_down = loadBMP("textures/sky_down.bmp");

    if (tex_sky_front == 0) std::cerr << "Failed to load sky_front texture." << std::endl;
    if (tex_sky_back == 0) std::cerr << "Failed to load sky_back texture." << std::endl;
    if (tex_sky_left == 0) std::cerr << "Failed to load sky_left texture." << std::endl;
    if (tex_sky_right == 0) std::cerr << "Failed to load sky_right texture." << std::endl;
    if (tex_sky_up == 0) std::cerr << "Failed to load sky_up texture." << std::endl;
    if (tex_sky_down == 0) std::cerr << "Failed to load sky_down texture." << std::endl;
}
