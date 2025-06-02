#include "Game.h"
#include "Ball.h"
#include "Field.h"
#include "Hoop.h"
#include "Numbers.h"
#include "Light.h"
#include "TextureManager.h"


Game* GameInstance = nullptr;

void displayWrapper() {
    if (GameInstance) GameInstance->display();
}

void reshapeWrapper(int width, int height) {
    if (GameInstance) GameInstance->reshape(width, height);
}

void keyboardWrapper(unsigned char key, int x, int y) {
    if (GameInstance) GameInstance->keyPress(key, x, y);
}

void timerBallWrapper(int value) {
    if (GameInstance) GameInstance->timerBall(value);
}

void timerTimeWrapper(int value) {
    if (GameInstance) GameInstance->timerTime(value);
}

void timerStrengthWrapper(int value) {
    if (GameInstance) GameInstance->timerStrength(value);
}


Game* Game::getInstance() {
    if (GameInstance == nullptr) {
        GameInstance = new Game();
    }
    return GameInstance;
}

Game::Game()
    : scoreFlag(false), lightSwitch(0), animationActive(false), hardModeFlag(false),
      rotationSpeed(0.0f), timePassed(0.0f), angle(45.0f),
      ballStrength(1.0f), lookAngle(0.0f), initialTime(0), score(0),
      shadowsEnabled(false), // Inisialisasi shadowsEnabled
      windowWidth(800), windowHeight(600) {
    
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(static_cast<unsigned int>(seed));
}

Game::~Game() {

}

void Game::init(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE); // Tambahkan GLUT_MULTISAMPLE untuk anti-aliasing
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100); // Ubah posisi window awal
    glutCreateWindow("ShootIT - Basketball Game Enhanced");
    
    glutDisplayFunc(displayWrapper);
    glutReshapeFunc(reshapeWrapper);
    glutKeyboardFunc(keyboardWrapper);
    glutTimerFunc(30, timerTimeWrapper, 1); // Timer untuk logika game umum
    // timerBall dan timerStrength diatur saat dibutuhkan

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Latar belakang hitam jika skybox gagal atau tidak menutupi
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_NORMALIZE); // Penting jika menggunakan glScalef agar normal tetap benar untuk pencahayaan
    glEnable(GL_MULTISAMPLE); // Aktifkan anti-aliasing

    // Inisialisasi tekstur SETELAH konteks OpenGL dibuat
    TextureManager::initTextures();
    
    ball = std::make_unique<Ball>();
    field = std::make_unique<Field>();
    hoop = std::make_unique<Hoop>();
    numbers = std::make_unique<Numbers>();
    light = std::make_unique<Light>();
    
    score = 0;
    scoreFlag = false;
    lookAngle = 90.0f * PI / 180.0f; // Pandangan awal
    lightSwitch = 0;
    hardModeFlag = false;
    shadowsEnabled = false; // Bayangan mati secara default
    initialTime = time(nullptr);
    
    restart(); // Inisialisasi posisi bola dll.
}

void Game::run() {
    glutMainLoop();
}

void Game::restart() {
    animationActive = false;
    timePassed = 0.0f;
    angle = 45.0f;
    ball->setBackboardFlag(false);
    ballStrength = 1.0f;
    ball->initPosition(rng);
}

void Game::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLineWidth(3);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Setup kamera (gluLookAt)
    gluLookAt(
        100.0f * cos(lookAngle), 20.0f, 100.0f * sin(lookAngle),
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    );
    
    // Setup pencahayaan setelah kamera
    // Posisi cahaya headlight (jika aktif) akan relatif terhadap pandangan kamera (eye space)
    // Posisi cahaya default (GL_LIGHT0) akan tetap di world space jika diatur sebelum gluLookAt
    // atau di eye space jika diatur setelahnya. Light::setup kita dipanggil setelah gluLookAt.
    if (lightSwitch) {
        light->enableHeadlight();
    }
    light->setup(lightSwitch);
    
    // Gambar semua elemen 3D
    field->draw(); // Ini sekarang termasuk skybox, tanah, dll.
    
    numbers->drawSemaphore(initialTime, 5.0f);
    hoop->draw();
    numbers->drawScore(score);
    
    // Gambar bayangan bola jika diaktifkan
    // Hanya gambar bayangan jika bola "dimainkan" (animationActive)
    if (shadowsEnabled && animationActive) {
         drawBallShadow();
    }
    ball->draw(rotationSpeed); // Gambar bola utama

    if (!animationActive && !hardModeFlag) {
        ball->drawShootAssistance(ballStrength, angle);
    }

    // Gambar UI/Instruksi di atas segalanya
    drawInstructions();

    glutSwapBuffers();
}

void Game::reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    
    if (height == 0) height = 1;
    float aspect = static_cast<float>(width) / height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, aspect, 1.0f, 1200.0f); // Far clipping plane ditingkatkan untuk scenery
    glMatrixMode(GL_MODELVIEW); // Kembali ke modelview matrix
}

void Game::keyPress(unsigned char key, int x, int y) {
    switch (key) {
        case ' ':
            if (!animationActive && numbers->isTimeUp()) {
                animationActive = true;
                timePassed = 0.0f; // Reset waktu untuk fisika peluncuran baru
                glutTimerFunc(30, timerBallWrapper, 0); // Interval timer lebih cepat untuk animasi lebih halus
            }
            break;
        case 'w': case 'W':
            if (!animationActive) {
                angle += 3.0f;
                if (angle > 89.0f) angle = 89.0f;
                glutPostRedisplay();
            }
            break;
        case 's': case 'S':
            if (!animationActive) {
                angle -= 3.0f;
                if (angle < -89.0f) angle = -89.0f; // Sudut bisa negatif
                glutPostRedisplay();
            }
            break;
        case 'a': case 'A':
            lookAngle += (5.0f * PI / 180.0f);
            glutPostRedisplay();
            break;
        case 'd': case 'D':
            lookAngle -= (5.0f * PI / 180.0f);
            glutPostRedisplay();
            break;
        case 'l': case 'L':
            lightSwitch = !lightSwitch;
            glutPostRedisplay();
            break;
        case 'j': case 'J':
            if (!animationActive && numbers->isTimeUp()) {
                ballStrength += 0.015f;
                if (ballStrength > 1.5f) ballStrength = 1.5f;

                glutPostRedisplay();
            }
            break;
        case 'k': case 'K':
            if (!animationActive && numbers->isTimeUp()) {
                ballStrength -= 0.015f;
                if (ballStrength < 0.5f) ballStrength = 0.5f;
                glutPostRedisplay();
            }
            break;
        case 'h': case 'H':
            hardModeFlag = !hardModeFlag;
            glutPostRedisplay();
            break;
        case 'x': case 'X': // Toggle bayangan
            shadowsEnabled = !shadowsEnabled;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

void Game::timerBall(int value) {
    if (value != 0) { //
        return;
    }

    rotationSpeed += 30.0f; //
    timePassed += 0.65f; //
    ball->updatePosition(timePassed, angle, ballStrength); //

    if (ball->getX() >= -50.0f && ball->getX() <= -40.0f &&
        ball->getY() <= 15.0f && ball->getY() >= 8.0f) {
        angle = 90.0f; //
        scoreFlag = true; //
    }

    if (ball->checkBackboardCollision()) { //
        ball->setBackboardFlag(true); //
    }

    if (ball->checkFloorCollision()) { //
        restart(); //
        if (scoreFlag && numbers->isTimeUp()) { //
            score++; //
            scoreFlag = false; //
        }
    }

    glutPostRedisplay(); //
    if (animationActive) { //
        glutTimerFunc(60, timerBallWrapper, 0); //
    }
}

void Game::timerTime(int value) {
    if (value != 1) {
        return;
    }

    if (!numbers->isTimeUp()) {
        // Game over, restart sesi game
        restart();
        initialTime = time(nullptr);
        score = 0;

    }
    
    glutPostRedisplay();
    glutTimerFunc(1000, timerTimeWrapper, 1); // Cek waktu setiap 1 detik (1000ms)
}

void Game::timerStrength(int value) {
    if (value != 2) {
        return;
    }
    
    if (!animationActive) {
        glutPostRedisplay();
    }
}

// Helper untuk render text
void Game::renderBitmapString(float x, float y, void *font, const char *string) const {
    glRasterPos2f(x, y);
    for (const char* c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void Game::drawInstructions() const {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glColor3f(0.0f, 0.0f, 0.545f);

    const char* instructionLines[] = {
            "Spasi      : Tembakkan Bola",
            "W / S      : Atur Sudut (+/-)",
            "J / K      : Atur Kekuatan (+/-)",
            "A / D      : Putar Kamera Kiri/Kanan",
            "L          : Nyalakan/Matikan Lampu Sorot",
            "H          : Mode Sulit (Bantuan Bidik Mati/Hidup)",
            "X          : Nyalakan/Matikan Bayangan",
            "ESC        : Keluar dari Permainan"
    };
    int numLines = sizeof(instructionLines) / sizeof(const char*);
    float yPos = windowHeight - 15.0f;

    for (int i = 0; i < numLines; ++i) {
        renderBitmapString(10.0f, yPos, GLUT_BITMAP_HELVETICA_18, instructionLines[i]);
        yPos -= 22.0f;
    }
    
    std::string hardModeStatusText = "Hard Mode: " + std::string(hardModeFlag ? "ON" : "OFF");
    renderBitmapString(10.0f, yPos, GLUT_BITMAP_HELVETICA_18, hardModeStatusText.c_str());
    yPos -= 22.0f;
    
    std::string shadowStatusText = "Shadows: " + std::string(shadowsEnabled ? "ON" : "OFF");
    renderBitmapString(10.0f, yPos, GLUT_BITMAP_HELVETICA_18, shadowStatusText.c_str());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Game::drawBallShadow() const {
    glPushAttrib(GL_LIGHTING_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT | GL_ENABLE_BIT);
    glPushMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glDepthMask(GL_FALSE);
    
    glColor4f(0.08f, 0.08f, 0.08f, 0.6f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0f, -1.0f);


    GLfloat groundPlane[4] = {0.0f, 1.0f, 0.0f, 40.001f};

    GLfloat lightShadowPosition[4];
    lightShadowPosition[0] = 20.0f;
    lightShadowPosition[1] = 50.0f;
    lightShadowPosition[2] = 30.0f;
    lightShadowPosition[3] = 1.0f;
    
    GLfloat shadowMatrix[16];
    GLfloat dot = groundPlane[0] * lightShadowPosition[0] +
                  groundPlane[1] * lightShadowPosition[1] +
                  groundPlane[2] * lightShadowPosition[2] +
                  groundPlane[3] * lightShadowPosition[3];

    shadowMatrix[0]  = dot - lightShadowPosition[0] * groundPlane[0];
    shadowMatrix[1]  = 0.0f - lightShadowPosition[1] * groundPlane[0];
    shadowMatrix[2]  = 0.0f - lightShadowPosition[2] * groundPlane[0];
    shadowMatrix[3]  = 0.0f - lightShadowPosition[3] * groundPlane[0];

    shadowMatrix[4]  = 0.0f - lightShadowPosition[0] * groundPlane[1];
    shadowMatrix[5]  = dot - lightShadowPosition[1] * groundPlane[1];
    shadowMatrix[6]  = 0.0f - lightShadowPosition[2] * groundPlane[1];
    shadowMatrix[7]  = 0.0f - lightShadowPosition[3] * groundPlane[1];

    shadowMatrix[8]  = 0.0f - lightShadowPosition[0] * groundPlane[2];
    shadowMatrix[9]  = 0.0f - lightShadowPosition[1] * groundPlane[2];
    shadowMatrix[10] = dot - lightShadowPosition[2] * groundPlane[2];
    shadowMatrix[11] = 0.0f - lightShadowPosition[3] * groundPlane[2];

    shadowMatrix[12] = 0.0f - lightShadowPosition[0] * groundPlane[3];
    shadowMatrix[13] = 0.0f - lightShadowPosition[1] * groundPlane[3];
    shadowMatrix[14] = 0.0f - lightShadowPosition[2] * groundPlane[3];
    shadowMatrix[15] = dot - lightShadowPosition[3] * groundPlane[3];

    glPushMatrix();
        glMultMatrixf(shadowMatrix);
        glTranslatef(ball->getX(), ball->getY(), 0.0f);
        glutSolidSphere(3.0, 20, 20);
    glPopMatrix();

    glDisable(GL_POLYGON_OFFSET_FILL);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glPopMatrix();
    glPopAttrib();
}
