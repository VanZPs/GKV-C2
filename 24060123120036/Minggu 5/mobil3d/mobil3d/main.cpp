//
//  main.cpp
//  mobil3d
//
//  Created by aris on 30/03/25.
//

#include <GLUT/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Kamera menghadap sedikit ke bawah agar lebih terlihat
    gluLookAt(0, 8, 20,  0, 0, 0,  0, 1, 0);
    
    // Mobil (Bodi)
    glPushMatrix();
    glColor3f(0.8, 0.1, 0.1);
    glScalef(4.0, 1.0, 2.0);
    glutSolidCube(2);
    glPopMatrix();
    
    // Ban Mobil
    glPushMatrix();
    glColor3f(0.6, 0.6, 0.6);
    glTranslatef(-1.2, -1.0, 1.2);
    glutSolidTorus(0.3, 0.5, 10, 20);
    glTranslatef(2.4, 0, 0);
    glutSolidTorus(0.3, 0.5, 10, 20);
    glTranslatef(0, 0, -2.4);
    glutSolidTorus(0.3, 0.5, 10, 20);
    glTranslatef(-2.4, 0, 0);
    glutSolidTorus(0.3, 0.5, 10, 20);
    glPopMatrix();
    
    // Kabin Mobil
    glPushMatrix();
    glColor3f(0.3, 0.3, 0.3);
    glTranslatef(0, 1.5, 0);
    glScalef(2.0, 1.0, 1.5);
    glutSolidCube(2);
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, ratio, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    // Tambahkan pencahayaan agar lebih realistis
    GLfloat light_position[] = { 5.0, 10.0, 10.0, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
}

void idle() {
    glutPostRedisplay(); // Render ulang terus-menerus
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Creative Car");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle); // Tambahkan idle agar terus menggambar ulang
    glutMainLoop();
    return 0;
}
