#ifndef FIELD_H
#define FIELD_H

#include "platform.h"

class Field {
public:
    Field() = default;
    ~Field() = default;
    
    void draw() const;
    
private:
    void setupMaterial() const;
    void drawLines(float radius) const;
    void drawFloor() const;

    // Elemen lingkungan yang sudah ada
    void drawTree(float x, float y, float z) const;
    void drawBush(float x, float y, float z) const;
    void drawCloud(float x, float y, float z, float scale) const;
    void drawScenery() const;
    void drawClouds() const;

    // Elemen baru
    void drawExtendedGround() const;
    void drawDistantScenery() const; // Untuk danau, gunung, dll.
    void drawSkybox() const;
};

#endif 
