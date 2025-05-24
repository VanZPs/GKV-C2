#include <GL/glut.h>
#include <GL/glu.h>

void drawWheel(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90, 0, 0, 1); 
    
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 0.3, 0.3, 0.2, 20, 20);
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    gluDisk(quad, 0.0, 0.3, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.2);
    glRotatef(180, 1, 0, 0);
    gluDisk(quad, 0.0, 0.3, 20, 20);
    glPopMatrix();
    
    gluDeleteQuadric(quad);
    glPopMatrix();
}

void drawCar() {
    glPushMatrix();
    
    GLfloat materialSpecular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat materialShininess[] = {100.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
    
    glColor3f(0.5, 0.5, 0.5);
    
    glPushMatrix();
    glScalef(2.0, 0.5, 1.0);
    glutSolidCube(2.0);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0, 0.75, 0.0);
    glScalef(1.0, 0.5, 0.7);
    glutSolidCube(2.0);
    glPopMatrix();
    
    glColor3f(0.0, 0.0, 0.0);
    
    float wheelPositions[4][3] = {
        {-1.4, -0.5,  0.9}, {1.4, -0.5,  0.9},
        {-1.4, -0.5, -0.9}, {1.4, -0.5, -0.9}
    };
    
    for (int i = 0; i < 4; i++) {
        drawWheel(wheelPositions[i][0], wheelPositions[i][1], wheelPositions[i][2]);
    }
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    gluLookAt(3, 3, 5, 0, 0, 0, 0, 1, 0);
    
    drawCar();
    
    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearDepth(1.0f);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glClearColor(0.53, 0.81, 0.98, 1.0); // Warna biru langit
    
    // Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPos[] = {2.0, 2.0, 2.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    GLfloat lightAmbient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat lightDiffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / h, 0.1, 50);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Car with GLUT");
    
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    
    return 0;
}
