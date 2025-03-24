// Nama	:	Ivan Pratomo Soelistio
// NIM	:	24060123120011

#include <GL/glut.h>

static int shoulder = 0, shoulderY = 0, elbow = 0, wrist = 0;
static int jempol = 0, telunjuk = 0, tengah = 0, manis = 0, kelingking = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    // Translasi untuk awal bahu
    glTranslatef(-1.3, 0.0, 0.0);
    
    // Rotasi dan translasi bahu
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulderY, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Menggambar bagian lengan atas
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Translasi dan rotasi siku
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    // Menggambar bagian lengan bawah
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Translasi dan rotasi pergelangan tangan
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    
    // Menggambar telapak tangan
	glPushMatrix();
    glScalef(0.8, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Menggambar jempol
    glPushMatrix();
    glTranslatef(0.0, -0.25, 0.4);
    glRotatef(-30.0 + (GLfloat)jempol, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    glScalef(0.6, 0.08, 0.08);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Menggambar jari telunjuk
    glPushMatrix();
    glTranslatef(0.4, 0.1, 0.25);
    glRotatef((GLfloat)telunjuk, 0.0, 0.0, 1.0);
    glTranslatef(0.35, 0.0, 0.0);
    glScalef(0.7, 0.08, 0.08);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Menggambar jari tengah
    glPushMatrix();
    glTranslatef(0.4, 0.1, 0.0);
    glRotatef((GLfloat)tengah, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    glScalef(0.8, 0.08, 0.08);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Menggambar jari manis
    glPushMatrix();
    glTranslatef(0.4, 0.1, -0.25);
    glRotatef((GLfloat)manis, 0.0, 0.0, 1.0);
    glTranslatef(0.35, 0.0, 0.0);
    glScalef(0.7, 0.08, 0.08);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Menggambar kelingking
    glPushMatrix();
    glTranslatef(0.4, 0.1, -0.45);
    glRotatef((GLfloat)kelingking, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glScalef(0.5, 0.07, 0.07);
    glutWireCube(1.0);
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

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();
            break;
        case 'S':
            shoulder = (shoulder - 5) % 360;
            glutPostRedisplay();
            break;
            
        // MODIFIKASI SAJA AGAR TANGANNYA BISA MUTER KE ARAH DEPAN BELAKANG
		case 'x':
		    shoulderY = (shoulderY + 5) % 360;
		    glutPostRedisplay();
		    break;
		case 'X':
		    shoulderY = (shoulderY - 5) % 360;
		    glutPostRedisplay();
		    break;
            
        case 'e':
            elbow = (elbow + 5) % 360;
            glutPostRedisplay();
            break;
        case 'E':
            elbow = (elbow - 5) % 360;
            glutPostRedisplay();
            break;
            
        case 'w':
            wrist = (wrist + 5) % 360;
            glutPostRedisplay();
            break;
        case 'W':
            wrist = (wrist - 5) % 360;
            glutPostRedisplay();
            break;
        
        
        // MENGGUNAKAN TOMBOL 1, 2, 3, 4, 5 UNTUK MENGGERAKAN JARI-JARINYA
        case '1':
            jempol = (jempol + 5) % 90;
            glutPostRedisplay();
            break;
        case '!':
            jempol = (jempol - 5) % 90;
            if (jempol < 0) jempol += 90;
            glutPostRedisplay();
            break;
            
        case '2':
            telunjuk = (telunjuk + 5) % 90;
            glutPostRedisplay();
            break;
        case '@':
            telunjuk = (telunjuk - 5) % 90;
            if (telunjuk < 0) telunjuk += 90;
            glutPostRedisplay();
            break;
            
        case '3':
            tengah = (tengah + 5) % 90;
            glutPostRedisplay();
            break;
        case '#':
            tengah = (tengah - 5) % 90;
            if (tengah < 0) tengah += 90;
            glutPostRedisplay();
            break;
            
        case '4':
            manis = (manis + 5) % 90;
            glutPostRedisplay();
            break;
        case '$':
            manis = (manis - 5) % 90;
            if (manis < 0) manis += 90;
            glutPostRedisplay();
            break;
            
        case '5':
            kelingking = (kelingking + 5) % 90;
            glutPostRedisplay();
            break;
        case '%':
            kelingking = (kelingking - 5) % 90;
            if (kelingking < 0) kelingking += 90;
            glutPostRedisplay();
            break;
            
        case 27: 
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
