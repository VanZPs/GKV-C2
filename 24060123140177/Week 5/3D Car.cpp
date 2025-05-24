#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

float xrot = 0.0f;
float yrot = 0.0f;
float zrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;

float zoom = 4.0f; 
float pastelRed[3] = {0.96f, 0.59f, 0.59f};
float headlightYellow[3] = {1.0f, 0.95f, 0.0f};
float windowBlue[3] = {0.0f, 0.3f, 0.8f};

void init(void) {
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
    GLfloat light_position[] = {5.0f, 5.0f, 5.0f, 1.0f};
    GLfloat light_ambient[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat light_diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    GLfloat light1_position[] = {-5.0f, 5.0f, -5.0f, 1.0f};
    GLfloat light1_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light1_diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
    
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    glEnable(GL_NORMALIZE);
    
    printf("\n=== Kontrol Keyboard ===\n");
    printf("A/D: Putar kiri/kanan (sumbu Y)\n");
    printf("W/S: Putar atas/bawah (sumbu X)\n");
    printf("Z/X: Zoom in/out\n");
    printf("R: Reset posisi\n");
    printf("ESC: Keluar\n");
}

void drawWheel(float radius, float width) {
    GLUquadricObj *cylinder = gluNewQuadric();
    
    gluQuadricNormals(cylinder, GLU_SMOOTH);
    
    GLfloat mat_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat mat_diffuse[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat mat_specular[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat mat_shininess[] = {30.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    
    glColor3f(0.1f, 0.1f, 0.1f);
    
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    gluCylinder(cylinder, radius, radius, width, 16, 2);
    gluDisk(cylinder, 0.0f, radius, 16, 2);
    glTranslatef(0.0f, 0.0f, width);
    gluDisk(cylinder, 0.0f, radius, 16, 2);
    glPopMatrix();
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    GLfloat rim_ambient[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat rim_diffuse[] = {0.9f, 0.9f, 0.9f, 1.0f};
    GLfloat rim_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat rim_shininess[] = {100.0f};
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, rim_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rim_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, rim_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, rim_shininess);
    
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    gluDisk(cylinder, 0.0f, radius * 0.6f, 12, 2);
    glTranslatef(0.0f, 0.0f, width);
    gluDisk(cylinder, 0.0f, radius * 0.6f, 12, 2);
    glPopMatrix();
    
    gluDeleteQuadric(cylinder);
}

void drawCar() {
    glDisable(GL_LIGHTING);
    
    glColor3fv(pastelRed);
    
    glPushMatrix();
    glScalef(1.8f, 0.3f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.6f, 0.1f, 0.0f);
    glScalef(0.6f, 0.2f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.7f, 0.1f, 0.0f);
    glScalef(0.4f, 0.2f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);
    glScalef(1.0f, 0.3f, 0.7f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3fv(windowBlue);
    
    glPushMatrix();
    glTranslatef(0.5f, 0.3f, 0.0f);
    glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.4f, 0.2f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.5f, 0.3f, 0.0f);
    glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
    glScalef(0.4f, 0.2f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.35f);
    glScalef(0.7f, 0.2f, 0.03f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, -0.35f);
    glScalef(0.7f, 0.2f, 0.03f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0f);
    
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.4f, 0.4f);
    glVertex3f(0.0f, 0.0f, 0.4f);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.4f, -0.4f);
    glVertex3f(0.0f, 0.0f, -0.4f);
    glEnd();
    
    glColor3f(0.3f, 0.3f, 0.3f);
    
    glPushMatrix();
    glTranslatef(0.2f, 0.15f, 0.4f);
    glScalef(0.1f, 0.02f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.2f, 0.15f, 0.4f);
    glScalef(0.1f, 0.02f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.2f, 0.15f, -0.4f);
    glScalef(0.1f, 0.02f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.2f, 0.15f, -0.4f);
    glScalef(0.1f, 0.02f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3fv(headlightYellow);
    
    glPushMatrix();
    glTranslatef(0.9f, 0.1f, 0.25f);
    glScalef(0.05f, 0.1f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.9f, 0.1f, -0.25f);
    glScalef(0.05f, 0.1f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(1.0f, 0.0f, 0.0f);
    
    glPushMatrix();
    glTranslatef(-0.9f, 0.1f, 0.25f);
    glScalef(0.05f, 0.1f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.9f, 0.1f, -0.25f);
    glScalef(0.05f, 0.1f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glColor3f(0.3f, 0.3f, 0.3f);
    glPushMatrix();
    glTranslatef(0.9f, 0.0f, 0.0f);
    glScalef(0.1f, 0.1f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.9f, 0.0f, 0.0f);
    glScalef(0.1f, 0.1f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    glEnable(GL_LIGHTING);
    
    glPushMatrix();
    glTranslatef(0.5f, -0.1f, 0.4f);
    drawWheel(0.15f, 0.08f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0.5f, -0.1f, -0.4f);
    drawWheel(0.15f, 0.08f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.5f, -0.1f, 0.4f);
    drawWheel(0.15f, 0.08f);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.5f, -0.1f, -0.4f);
    drawWheel(0.15f, 0.08f);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    gluLookAt(
        0.0f, 1.0f, zoom,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    );
    
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);
    
    glDisable(GL_LIGHTING);
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, -0.3f, -10.0f);
    glVertex3f(-10.0f, -0.3f, 10.0f);
    glVertex3f(10.0f, -0.3f, 10.0f);
    glVertex3f(10.0f, -0.3f, -10.0f);
    glEnd();
    
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for (int i = -10; i <= 10; i++) {
        glVertex3f(i, -0.29f, -10.0f);
        glVertex3f(i, -0.29f, 10.0f);
        glVertex3f(-10.0f, -0.29f, i);
        glVertex3f(10.0f, -0.29f, i);
    }
    glEnd();
    
    drawCar();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    } else {
        mouseDown = false;
    }
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;
        
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    float rotationSpeed = 5.0f;
    float zoomSpeed = 0.2f;
    
    switch(key) {
        case 'w': case 'W':
            xrot += rotationSpeed;
            break;
        case 's': case 'S':
            xrot -= rotationSpeed;
            break;
        case 'a': case 'A':
            yrot += rotationSpeed;
            break;
        case 'd': case 'D':
            yrot -= rotationSpeed;
            break;
        case 'z': case 'Z':
            zoom -= zoomSpeed;
            if (zoom < 1.0f) zoom = 1.0f;
            break;
        case 'x': case 'X':
            zoom += zoomSpeed;
            if (zoom > 10.0f) zoom = 10.0f;
            break;
        case 'r': case 'R':
            xrot = 0.0f;
            yrot = 0.0f;
            zrot = 0.0f;
            zoom = 4.0f;
            break;
        case 27:
            exit(0);
            break;
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Mobil");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    
    return 0;
}
