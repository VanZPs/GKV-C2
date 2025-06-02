#ifndef PLATFORM_H
#define PLATFORM_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <ctime>
#include <random>
#include <chrono>
#include <functional>

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #ifdef _WIN32
        #include <windows.h>
    #endif
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/freeglut.h>
#endif

constexpr double PI = 3.141592653589793;

enum class BallType {
    BASKET_BALL = 1,
    BOWLING_BALL = 2
};

class Game;
extern Game* GameInstance;

#endif // PLATFORM_H
