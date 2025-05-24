#include <GLUT/glut.h>
#include "stdlib.h"

static int shoulder = 0, elbow = 0, wrist = 0, wristTwist = 0;
static int thumb1 = 20, thumb2 = 20, thumbTwist = 0;
static int indexBase = 0, indexMiddle = 0, indexTip = 0;
static int middleBase = 0, middleMiddle = 0, middleTip = 0;
static int ringBase = 0, ringMiddle = 0, ringTip = 0;
static int pinkyBase = 0, pinkyMiddle = 0, pinkyTip = 0;
static int sceneRotation = 0;

// agar dia kereset
static int shoulderDir = 1, elbowDir = 1, wristDir = 1, wristTwistDir = 1;
static int thumb1Dir = 1, thumb2Dir = 1, thumbTwistDir = 1;
static int indexBaseDir = 1, indexMiddleDir = 1, indexTipDir = 1;
static int middleBaseDir = 1, middleMiddleDir = 1, middleTipDir = 1;
static int ringBaseDir = 1, ringMiddleDir = 1, ringTipDir = 1;
static int pinkyBaseDir = 1, pinkyMiddleDir = 1, pinkyTipDir = 1;

// limitasi pergerakan seperti tangan asli
static const int SHOULDER_MIN = -90, SHOULDER_MAX = 90;
static const int ELBOW_MIN = 0, ELBOW_MAX = 150;
static const int WRIST_MIN = -80, WRIST_MAX = 80;
static const int WRIST_TWIST_MIN = -90, WRIST_TWIST_MAX = 90;
static const int THUMB_MIN = 0, THUMB_MAX = 60;
static const int FINGER_MIN = 0, FINGER_MAX = 80;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawWireSegment(float length, float width, float height) {
    glPushMatrix();
    glScalef(length, width, height);
    glutWireCube(1.0);
    glPopMatrix();
}

void drawWireFinger(float baseLength, float middleLength, float tipLength,
                 float width, float height, int baseAngle, int middleAngle, int tipAngle) {
    // Base segment
    glRotatef((GLfloat)baseAngle, 0.0, 0.0, 1.0);
    drawWireSegment(baseLength, width, height);
    
    
    glTranslatef(baseLength/2, 0.0, 0.0);
    glRotatef((GLfloat)middleAngle, 0.0, 0.0, 1.0);
    glTranslatef(middleLength/2, 0.0, 0.0);
    drawWireSegment(middleLength, width*0.9, height*0.9);
    
    
    glTranslatef(middleLength/2, 0.0, 0.0);
    glRotatef((GLfloat)tipAngle, 0.0, 0.0, 1.0);
    glTranslatef(tipLength/2, 0.0, 0.0);
    drawWireSegment(tipLength, width*0.8, height*0.8);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    // rotasi Y axis
    glRotatef((GLfloat)sceneRotation, 0.0, 1.0, 0.0);
    
    // Reset color to white for wire frames
    glColor3f(1.0, 1.0, 1.0);
    
    // Bahu
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Lengan Atas
    glPushMatrix();
    glScalef(2.0, 0.4, 0.6);
    glutWireCube(1.0);
    glPopMatrix();
    
    //Bahu
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Lengan Bawah
    glPushMatrix();
    glScalef(2.0, 0.4, 0.6);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Pergelangn tangan
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)wristTwist, 1.0, 0.0, 0.0);
    glTranslatef(0.4, 0.0, 0.0);
    
    // Telapak Tangan
    glPushMatrix();
    glScalef(0.8, 0.3, 0.7);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Jempol
    glPushMatrix();
    glTranslatef(0.0, -0.15, -0.35);
    
    glRotatef(-90.0, 0.0, 1.0, 0.0);  // Reversed for right hand
    glRotatef(-45.0, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)thumbTwist, 0.0, 1.0, 0.0);
    
    glRotatef((GLfloat)thumb1, 0.0, 0.0, 1.0);
    drawWireSegment(0.25, 0.18, 0.18);
    
    glTranslatef(0.125, 0.0, 0.0);
    glRotatef((GLfloat)thumb2, 0.0, 0.0, 1.0);
    glTranslatef(0.125, 0.0, 0.0);
    drawWireSegment(0.25, 0.16, 0.16);
    glPopMatrix();
    
    // Telunjuk
    glPushMatrix();
    glTranslatef(0.4, 0.0, -0.25); // Changed to negative Z for right hand
    drawWireFinger(0.3, 0.25, 0.2, 0.12, 0.12, indexBase, indexMiddle, indexTip);
    glPopMatrix();
    
    // Jari Tengah
    glPushMatrix();
    glTranslatef(0.4, 0.0, -0.08); // Changed to negative Z for right hand
    drawWireFinger(0.32, 0.28, 0.22, 0.13, 0.13, middleBase, middleMiddle, middleTip);
    glPopMatrix();
    
    // Jari Cincin
    glPushMatrix();
    glTranslatef(0.4, 0.0, 0.12); // Changed to positive Z for right hand
    drawWireFinger(0.3, 0.26, 0.2, 0.12, 0.12, ringBase, ringMiddle, ringTip);
    glPopMatrix();
    
    // Jari kelingking
    glPushMatrix();
    glTranslatef(0.4, 0.0, 0.3); // Changed to positive Z for right hand
    drawWireFinger(0.25, 0.2, 0.16, 0.1, 0.1, pinkyBase, pinkyMiddle, pinkyTip);
    glPopMatrix();
    
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void resetHand() {
    shoulder = 0;
    elbow = 0;
    wrist = 0;
    wristTwist = 0;
    thumb1 = 20;
    thumb2 = 20;
    thumbTwist = 0;
    indexBase = 0;
    indexMiddle = 0;
    indexTip = 0;
    middleBase = 0;
    middleMiddle = 0;
    middleTip = 0;
    ringBase = 0;
    ringMiddle = 0;
    ringTip = 0;
    pinkyBase = 0;
    pinkyMiddle = 0;
    pinkyTip = 0;
    
    shoulderDir = 1;
    elbowDir = 1;
    wristDir = 1;
    wristTwistDir = 1;
    thumb1Dir = 1;
    thumb2Dir = 1;
    thumbTwistDir = 1;
    indexBaseDir = 1;
    indexMiddleDir = 1;
    indexTipDir = 1;
    middleBaseDir = 1;
    middleMiddleDir = 1;
    middleTipDir = 1;
    ringBaseDir = 1;
    ringMiddleDir = 1;
    ringTipDir = 1;
    pinkyBaseDir = 1;
    pinkyMiddleDir = 1;
    pinkyTipDir = 1;
    
    glutPostRedisplay();
}


void updateAngle(int *angle, int *direction, int min_val, int max_val, int step) {
    *angle += (*direction) * step;
    
    if (*angle >= max_val) {
        *angle = max_val;
        *direction = -1;  // Change direction when max is reached
    } else if (*angle <= min_val) {
        *angle = min_val;
        *direction = 1;   // Change direction when min is reached
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Scene rotation controls
        case 'a':  // Rotate scene left (around Y-axis)
            sceneRotation = (sceneRotation + 5) % 360;
            glutPostRedisplay();
            break;
        case 'd':  // Rotate scene right (around Y-axis)
            sceneRotation = (sceneRotation - 5) % 360;
            glutPostRedisplay();
            break;
            
        // Reset hand to initial position
        case '0':
            resetHand();
            break;
            
        // Shoulder controls
        case 's':
            updateAngle(&shoulder, &shoulderDir, SHOULDER_MIN, SHOULDER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'S':
            updateAngle(&shoulder, &shoulderDir, SHOULDER_MIN, SHOULDER_MAX, -5);
            glutPostRedisplay();
            break;
            
        // Elbow controls
        case 'e':
            updateAngle(&elbow, &elbowDir, ELBOW_MIN, ELBOW_MAX, 5);
            glutPostRedisplay();
            break;
        case 'E':
            updateAngle(&elbow, &elbowDir, ELBOW_MIN, ELBOW_MAX, -5);
            glutPostRedisplay();
            break;
            
        // Wrist controls
        case 'w':
            updateAngle(&wrist, &wristDir, WRIST_MIN, WRIST_MAX, 5);
            glutPostRedisplay();
            break;
        case 'W':
            updateAngle(&wrist, &wristDir, WRIST_MIN, WRIST_MAX, -5);
            glutPostRedisplay();
            break;
            
        // Wrist twist controls
        case 'q':
            updateAngle(&wristTwist, &wristTwistDir, WRIST_TWIST_MIN, WRIST_TWIST_MAX, 5);
            glutPostRedisplay();
            break;
        case 'Q':
            updateAngle(&wristTwist, &wristTwistDir, WRIST_TWIST_MIN, WRIST_TWIST_MAX, -5);
            glutPostRedisplay();
            break;
            
        // Thumb controls
        case 't':
            updateAngle(&thumb1, &thumb1Dir, THUMB_MIN, THUMB_MAX, 5);
            glutPostRedisplay();
            break;
        case 'T':
            updateAngle(&thumb1, &thumb1Dir, THUMB_MIN, THUMB_MAX, -5);
            glutPostRedisplay();
            break;
        case 'y':
            updateAngle(&thumb2, &thumb2Dir, THUMB_MIN, THUMB_MAX, 5);
            glutPostRedisplay();
            break;
        case 'Y':
            updateAngle(&thumb2, &thumb2Dir, THUMB_MIN, THUMB_MAX, -5);
            glutPostRedisplay();
            break;
        // Thumb twist control
        case 'g':
            updateAngle(&thumbTwist, &thumbTwistDir, -45, 45, 5);
            glutPostRedisplay();
            break;
        case 'G':
            updateAngle(&thumbTwist, &thumbTwistDir, -45, 45, -5);
            glutPostRedisplay();
            break;
            
        // Index finger controls
        case 'i':
            updateAngle(&indexBase, &indexBaseDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'I':
            updateAngle(&indexBase, &indexBaseDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
        case 'j':
            updateAngle(&indexMiddle, &indexMiddleDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'J':
            updateAngle(&indexMiddle, &indexMiddleDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
        case 'k':
            updateAngle(&indexTip, &indexTipDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'K':
            updateAngle(&indexTip, &indexTipDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
            
        // Middle finger controls
        case 'm':
            updateAngle(&middleBase, &middleBaseDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'M':
            updateAngle(&middleBase, &middleBaseDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
        case 'n':
            updateAngle(&middleMiddle, &middleMiddleDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'N':
            updateAngle(&middleMiddle, &middleMiddleDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
        case 'b':
            updateAngle(&middleTip, &middleTipDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'B':
            updateAngle(&middleTip, &middleTipDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
            
        // Ring finger controls
        case 'r':
            updateAngle(&ringBase, &ringBaseDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'R':
            updateAngle(&ringBase, &ringBaseDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
        case 'f':
            updateAngle(&ringMiddle, &ringMiddleDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'F':
            updateAngle(&ringMiddle, &ringMiddleDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
        case 'v':
            updateAngle(&ringTip, &ringTipDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'V':
            updateAngle(&ringTip, &ringTipDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
            
        // Pinky finger controls
        case 'p':
            updateAngle(&pinkyBase, &pinkyBaseDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'P':
            updateAngle(&pinkyBase, &pinkyBaseDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
        case 'o':
            updateAngle(&pinkyMiddle, &pinkyMiddleDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'O':
            updateAngle(&pinkyMiddle, &pinkyMiddleDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
        case 'l':
            updateAngle(&pinkyTip, &pinkyTipDir, FINGER_MIN, FINGER_MAX, 5);
            glutPostRedisplay();
            break;
        case 'L':
            updateAngle(&pinkyTip, &pinkyTipDir, FINGER_MIN, FINGER_MAX, -5);
            glutPostRedisplay();
            break;
            
        case 27:  // ESC key
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tangan Kematian");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
