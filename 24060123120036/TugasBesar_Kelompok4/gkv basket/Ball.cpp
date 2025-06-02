#include "Ball.h"

Ball::Ball()
    : xPos(0.0f), yPos(0.0f), type(BallType::BASKET_BALL),
      velocityX(0.0f), velocityY(0.0f), backboardCollision(false) {
}

void Ball::initPosition(std::mt19937& rng) {
    std::uniform_real_distribution<float> probDist(0.0f, 1.0f);
    std::uniform_real_distribution<float> xDist(-20.0f, 40.0f); // -20 to 40
    std::uniform_real_distribution<float> yDist(-30.0f, 30.0f); // -30 to 30

    if (probDist(rng) <= 0.66f) {
        type = BallType::BASKET_BALL;
    } else {
        type = BallType::BOWLING_BALL;
    }

    xPos = xDist(rng);
    yPos = yDist(rng);
    
    velocityX = 0.0f;
    velocityY = 0.0f;
    backboardCollision = false;
}

void Ball::draw(float ballRotation) const {
    constexpr GLfloat basketballAmbient[] = {0.9f, 0.45f, 0.0f, 1.0f};
    constexpr GLfloat basketballDiffuse[] = {1.0f, 0.5f, 0.1f, 1.0f};
    constexpr GLfloat basketballSpecular[] = {0.4f, 0.4f, 0.4f, 1.0f};
    
    constexpr GLfloat bowlingballAmbient[] = {0.6f, 0.6f, 0.6f, 1.0f};
    constexpr GLfloat bowlingballDiffuse[] = {0.1f, 0.1f, 0.1f, 1.0f};
    constexpr GLfloat bowlingballSpecular[] = {0.4f, 0.4f, 0.4f, 1.0f};

    constexpr GLfloat shinessBall = 20.0f;
    
    glPushMatrix();

        if (type == BallType::BASKET_BALL) {
            glMaterialfv(GL_FRONT, GL_AMBIENT, basketballAmbient);
            glMaterialfv(GL_FRONT, GL_SPECULAR, basketballSpecular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, basketballDiffuse);
            glMaterialf(GL_FRONT, GL_SHININESS, shinessBall);
        } else if (type == BallType::BOWLING_BALL) {
            glMaterialfv(GL_FRONT, GL_AMBIENT, bowlingballAmbient);
            glMaterialfv(GL_FRONT, GL_SPECULAR, bowlingballSpecular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, bowlingballDiffuse);
            glMaterialf(GL_FRONT, GL_SHININESS, shinessBall);
        }

        glTranslatef(xPos, yPos, 0.0f);
        glRotatef(ballRotation, 0.0f, 0.0f, 1.0f);
        glutSolidSphere(3.0, 50, 50);
    glPopMatrix();
}

void Ball::updatePosition(float time, float angle, float ballStrength) {
    const float angleDeg = angle * static_cast<float>(PI) / 180.0f;
    float v0x, v0y;
    
    if (type == BallType::BASKET_BALL) {
            v0x = ballStrength * -3.5f;
            v0y = ballStrength * 7.0f;
        } else {
            v0x = ballStrength * -2.75f;
            v0y = ballStrength * 5.5f;
        }

        velocityX = (v0x * cos(angleDeg));
        velocityY = (v0y * sin(angleDeg) - 0.5f * time); // faktor gravitasi asli adalah 0.5f dikali 'time'

    if (backboardCollision) {
        velocityX *= -1.0f;
        backboardCollision = false;
    }

        xPos += velocityX;
        yPos += velocityY;
}

void Ball::setBackboardFlag(bool flag) {
    backboardCollision = flag;
}

bool Ball::checkBackboardCollision() const {
    return (xPos >= -55.0f && xPos <= -45.0f && yPos > 3.0f && yPos < 25.0f);
}

bool Ball::checkFloorCollision() const {
    return (yPos <= -40.0f);
}

void Ball::drawShootAssistance(float ballStrength, float angle) const {
    glPushMatrix();
    
        constexpr GLfloat shadowBallAmbient[] = {0.9f, 0.9f, 0.9f, 0.5f};
        constexpr GLfloat shadowBallDiffuse[] = {0.7f, 0.7f, 0.7f, 0.5f};
        constexpr GLfloat shadowBallSpecular[] = {0.0f, 0.0f, 0.0f, 0.5f};
        constexpr GLfloat shadowShininess = 10.0f;
    
        glMaterialfv(GL_FRONT, GL_AMBIENT, shadowBallAmbient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, shadowBallDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, shadowBallSpecular);
        glMaterialf(GL_FRONT, GL_SHININESS, shadowShininess);
        
        glTranslatef(xPos, yPos, 0.0f);
        glRotatef(90.0f - angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, 5.0f, 0.0f);
        
        glPushMatrix();

            const int shadowNum = static_cast<int>((ballStrength * 10.0f - 5.0f) / 2.0f);
            

            glutSolidSphere(1.0, 20, 20);
            

            for (int i = 0; i < shadowNum; i++) {
                glTranslatef(0.0f, 3.0f, 0.0f);
                glutSolidSphere(1.0, 20, 20);
            }
        glPopMatrix();
    glPopMatrix();
}
