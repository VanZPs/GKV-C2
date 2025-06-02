#include "Numbers.h"

Numbers::Numbers() : timeUp(true) {
}

void Numbers::drawDigit(int number, float size) const {
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
        glBegin(GL_LINE_STRIP);

        switch (number) {
            case 1:
                glVertex3f(size/2, 0, 0);
                glVertex3f(size/2, size, 0);
                break;
            case 2:
                glVertex3f(size/2, 0, 0);
                glVertex3f(0, 0, 0);
                glVertex3f(0, size/2, 0);
                glVertex3f(size/2, size/2, 0);
                glVertex3f(size/2, size, 0);
                glVertex3f(0, size, 0);
                break;
            case 3:
                glVertex3f(0, 0, 0);
                glVertex3f(size/2, 0, 0);
                glVertex3f(size/2, size/2, 0);
                glVertex3f(0, size/2, 0);
                glVertex3f(size/2, size/2, 0);
                glVertex3f(size/2, size, 0);
                glVertex3f(0, size, 0);
                break;
            case 4:
                glVertex3f(size/2, 0, 0);
                glVertex3f(size/2, size, 0);
                glVertex3f(size/2, size/2, 0);
                glVertex3f(0, size/2, 0);
                glVertex3f(0, size, 0);
                break;
            case 5:
                glVertex3f(0, 0, 0);
                glVertex3f(size/2, 0, 0);
                glVertex3f(size/2, size/2, 0);
                glVertex3f(0, size/2, 0);
                glVertex3f(0, size, 0);
                glVertex3f(size/2, size, 0);
                break;
            case 6:
                glVertex3f(0, size/2, 0);
                glVertex3f(0, 0, 0);
                glVertex3f(size/2, 0, 0);
                glVertex3f(size/2, size/2, 0);
                glVertex3f(0, size/2, 0);
                glVertex3f(0, size, 0);
                glVertex3f(size/2, size, 0);
                break;
            case 7:
                glVertex3f(size/2, 0, 0);
                glVertex3f(size/2, size/2, 0);
                glVertex3f(size/2, size, 0);
                glVertex3f(0, size, 0);
                break;
            case 8:
                glVertex3f(0, size/2, 0);
                glVertex3f(0, 0, 0);
                glVertex3f(size/2, 0, 0);
                glVertex3f(size/2, size/2, 0);
                glVertex3f(0, size/2, 0);
                glVertex3f(0, size, 0);
                glVertex3f(size/2, size, 0);
                glVertex3f(size/2, size/2, 0);
                break;
            case 9:
                glVertex3f(0, 0, 0);
                glVertex3f(size/2, 0, 0);
                glVertex3f(size/2, size/2, 0);
                glVertex3f(0, size/2, 0);
                glVertex3f(0, size, 0);
                glVertex3f(size/2, size, 0);
                glVertex3f(size/2, size/2, 0);
                break;
            case 0:
                glVertex3f(0, 0, 0);
                glVertex3f(size/2, 0, 0);
                glVertex3f(size/2, size, 0);
                glVertex3f(0, size, 0);
                glVertex3f(0, 0, 0);
                break;
            default:
                glVertex3f(0, 0, 0);
                glVertex3f(size/2, 0, 0);
                glVertex3f(size/2, size, 0);
                glVertex3f(0, size, 0);
                glVertex3f(0, 0, 0);
                break;
        }
            
        glEnd();
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
}

void Numbers::drawNumber(int number, float size) const {
    number = std::max(0, std::min(99, number));
    
    glPushMatrix();
        drawDigit(number / 10, size);

        glTranslatef(size - 1.0f, 0.0f, 0.0f);
        drawDigit(number % 10, size);
    glPopMatrix();
}

bool Numbers::drawTime(time_t start, float size) {
    time_t currentTime = time(nullptr);
    time_t passedTime = difftime(currentTime, start);
    struct tm* timeInfo = localtime(&passedTime);
    
    // remaining time
    int counter = 90 - 60 * timeInfo->tm_min - timeInfo->tm_sec;
    
    if (counter < 0) {
        timeUp = false;
        counter = 0;
    } else {
        timeUp = true;
    }

    drawNumber(counter, size);
    
    return timeUp;
}

void Numbers::drawSemaphore(time_t start, float size) {
    glPushMatrix();
        //papan score
        constexpr GLfloat tableAmbient[] = {0.8f, 0.8f, 0.8f, 1.0f};
        constexpr GLfloat tableDiffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
        constexpr GLfloat tableSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        constexpr GLfloat shinessTable = 40.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, tableAmbient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tableDiffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tableSpecular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shinessTable);
        
        // Posisi
        glTranslatef(0.0f, 40.0f, -20.0f);
        
        //menggambar papan
        glPushMatrix();
            glScalef(1.0f, 0.6f, 1.0f);
            glutSolidCube(4.0f * size - 1.0f);
        glPopMatrix();
        
        // timer sebelah kiri
        glPushMatrix();
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            glScalef(-1.0f, 1.0f, 1.0f);
            glTranslatef(-size/1.5f, -size/2.0f, -size*2.0f);
            drawTime(start, size);
        glPopMatrix();
        
        // timer sebelah kanan
        glPushMatrix();
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            glTranslatef(-size/1.5f, -size/2.0f, size*2.0f);
            drawTime(start, size);
        glPopMatrix();
        
        //timer belakang
        glPushMatrix();
            glScalef(-1.0f, 1.0f, 1.0f);
            glTranslatef(-size/1.5f, -size/2.0f, -size*2.0f);
            drawTime(start, size);
        glPopMatrix();
        
        // timer depan
        glPushMatrix();
            glTranslatef(-size/1.5f, -size/2.0f, size*2.0f);
            drawTime(start, size);
        glPopMatrix();
    
    glPopMatrix();
}

void Numbers::drawScore(int score) const {
    glPushMatrix();
        glTranslatef(-48.0f, 25.0f, 3.0f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        drawNumber(score, 5.0f);
    glPopMatrix();
}
