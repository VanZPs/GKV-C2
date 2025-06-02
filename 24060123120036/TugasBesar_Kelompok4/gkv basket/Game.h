#ifndef GAME_H
#define GAME_H

#include "platform.h"

class Ball;
class Field;
class Hoop;
class Numbers;
class Light;

class Game {
public:
    static Game* getInstance();
    
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    
    void init(int argc, char** argv);
    void run();
    void restart();
    
    void display();
    void reshape(int width, int height);
    void keyPress(unsigned char key, int x, int y);
    void timerBall(int value);
    void timerTime(int value);
    void timerStrength(int value);
    
    bool isAnimationActive() const { return animationActive; }
    void setAnimationActive(bool active) { animationActive = active; }
    
    float getRotationSpeed() const { return rotationSpeed; }
    float getTimePassed() const { return timePassed; }
    float getAngle() const { return angle; }
    float getBallStrength() const { return ballStrength; }
    float getLookAngle() const { return lookAngle; }
    int getScore() const { return score; }
    bool getScoreFlag() const { return scoreFlag; }
    bool getHardModeFlag() const { return hardModeFlag; }
    int getLightSwitch() const { return lightSwitch; }
    time_t getInitialTime() const { return initialTime; }
    bool areShadowsEnabled() const { return shadowsEnabled; }
    
    void setRotationSpeed(float speed) { rotationSpeed = speed; }
    void setTimePassed(float time) { timePassed = time; }
    void setAngle(float a) { angle = a; }
    void setBallStrength(float strength) { ballStrength = strength; }
    void setLookAngle(float angleVal) { lookAngle = angleVal; }
    void setScore(int s) { score = s; }
    void setScoreFlag(bool flag) { scoreFlag = flag; }
    void setHardModeFlag(bool flag) { hardModeFlag = flag; }
    void setLightSwitch(int light) { lightSwitch = light; }
    
    std::unique_ptr<Ball> ball;
    std::unique_ptr<Field> field;
    std::unique_ptr<Hoop> hoop;
    std::unique_ptr<Numbers> numbers;
    std::unique_ptr<Light> light;
    
private:
    Game();
    ~Game();
    
    void renderBitmapString(float x, float y, void *font, const char *string) const;
    void drawInstructions() const;
    void drawBallShadow() const;

    bool scoreFlag;
    int lightSwitch;
    bool animationActive;
    bool hardModeFlag;
    float rotationSpeed;
    float timePassed;
    float angle;
    float ballStrength;
    float lookAngle;
    time_t initialTime;
    int score;
    bool shadowsEnabled;
    
    int windowWidth;
    int windowHeight;
    
    std::mt19937 rng;
};

void displayWrapper();
void reshapeWrapper(int width, int height);
void keyboardWrapper(unsigned char key, int x, int y);
void timerBallWrapper(int value);
void timerTimeWrapper(int value);
void timerStrengthWrapper(int value);

#endif
