#include <GL/glut.h>
#include <math.h>

// Rotasi bahu pada 3 sumbu
static int shoulderX = 0, shoulderY = 0, shoulderZ = 0;
// Rotasi siku pada 1 sumbu 
static int elbow = 0;
// Rotasi pergelangan pada 3 sumbu
static int wristX = 0, wristY = 0, wristZ = 0;

// Kontrol untuk semua ruas jari sekaligus
static int fingerJoint1 = 0;  
static int fingerJoint2 = 0;  
static int fingerJoint3 = 0;  

void init(void) {
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
}

void drawBlock(float length, float width, float height) {
   glPushMatrix();
   glScalef(length, width, height);
   glutWireCube(1.0);
   glPopMatrix();
}

void drawFingerSegment(float length, float width, float height) {
   glPushMatrix();
   glTranslatef(length/2, 0.0, 0.0);
   drawBlock(length, width, height);
   glPopMatrix();
}

void drawFinger(float length, float width, float height, int angle1, int angle2, int angle3) {
   float segment1 = length * 0.4;
   float segment2 = length * 0.3;
   float segment3 = length * 0.3;
   
   // Ruas pertama 
   glPushMatrix();
   glRotatef((GLfloat)angle1, 0.0, 0.0, 1.0); // Rotasi vertikal (tekuk ke bawah)
   drawFingerSegment(segment1, width, height);
   
   // Ruas kedua
   glTranslatef(segment1, 0.0, 0.0);
   glRotatef((GLfloat)angle2, 0.0, 0.0, 1.0); // Rotasi vertikal (tekuk ke bawah)
   drawFingerSegment(segment2, width * 0.9, height * 0.9); 
   
   // Ruas ketiga 
   glTranslatef(segment2, 0.0, 0.0);
   glRotatef((GLfloat)angle3, 0.0, 0.0, 1.0); // Rotasi vertikal (tekuk ke bawah)
   drawFingerSegment(segment3, width * 0.8, height * 0.8); 
   
   glPopMatrix();
}

// Membatasi nilai sudut dalam rentang tertentu
int clampAngle(int angle, int min, int max) {
   if (angle < min) return min;
   if (angle > max) return max;
   return angle;
}

void display(void) {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix();
   
   // Posisi awal
   glTranslatef(0.0, 0.0, 0.0);
   
   // Rotasi bahu
   glTranslatef(-1.0, 0.0, 0.0);
   glRotatef((GLfloat)shoulderX, 1.0, 0.0, 0.0);
   glRotatef((GLfloat)shoulderY, 0.0, 1.0, 0.0);
   glRotatef((GLfloat)shoulderZ, 0.0, 0.0, 1.0);
   
   // Lengan atas
   glPushMatrix();
   glTranslatef(1.0, 0.0, 0.0);
   drawBlock(2.0, 0.4, 0.4);
   glPopMatrix();
   
   // Siku 
   glTranslatef(2.0, 0.0, 0.0);
   glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
   
   // Lengan bawah 
   glPushMatrix();
   glTranslatef(1.0, 0.0, 0.0);
   drawBlock(2.0, 0.35, 0.35);
   glPopMatrix();
   
   // Pergelangan tangan 
   glTranslatef(2.0, 0.0, 0.0);
   glRotatef((GLfloat)wristX, 1.0, 0.0, 0.0);
   glRotatef((GLfloat)wristY, 0.0, 1.0, 0.0);
   glRotatef((GLfloat)wristZ, 0.0, 0.0, 1.0);
   
   // Telapak tangan
   glPushMatrix();
   glTranslatef(0.25, 0.0, 0.0);
   drawBlock(0.5, 0.2, 0.7);
   glPopMatrix();
   
   // Ibu jari
   glPushMatrix();
   glTranslatef(0.1, -0.15, -0.35); 
   glRotatef(45, 0.0, 1.0, 0.0);  // Rotasi sedikit ke samping
   glRotatef(-20, 1.0, 0.0, 0.0);  
   drawFinger(0.5, 0.08, 0.08, fingerJoint1, fingerJoint2, fingerJoint3);
   glPopMatrix();
   
   
   // Telunjuk 
   glPushMatrix();
   glTranslatef(0.5, 0.0, -0.21); 
   drawFinger(0.6, 0.06, 0.06, fingerJoint1, fingerJoint2, fingerJoint3);
   glPopMatrix();
   
   // Jari tengah 
   glPushMatrix();
   glTranslatef(0.5, 0.0, -0.07); 
   drawFinger(0.65, 0.065, 0.065, fingerJoint1, fingerJoint2, fingerJoint3);
   glPopMatrix();
   
   // Jari manis 
   glPushMatrix();
   glTranslatef(0.5, 0.0, 0.07); 
   drawFinger(0.6, 0.06, 0.06, fingerJoint1, fingerJoint2, fingerJoint3);
   glPopMatrix();
   
   // Kelingking
   glPushMatrix();
   glTranslatef(0.5, 0.0, 0.21); 
   drawFinger(0.5, 0.05, 0.05, fingerJoint1, fingerJoint2, fingerJoint3);
   glPopMatrix();
   
   glPopMatrix();
   glutSwapBuffers();
}

void reshape(int w, int h) {
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(65.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -5.0); 
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      // Kontrol shoulder X
      case 'q': 
            shoulderX = (shoulderX + 5) % 360; 
            glutPostRedisplay(); 
            break;
      case 'Q': 
            shoulderX = (shoulderX - 5) % 360; 
            glutPostRedisplay(); 
            break;
      
      // Kontrol shoulder Y
      case 'w': 
            shoulderY = (shoulderY + 5) % 360; 
            glutPostRedisplay(); 
            break;
      case 'W': 
            shoulderY = (shoulderY - 5) % 360; 
            glutPostRedisplay(); 
            break;
      
      // Kontrol shoulder Z
      case 's': 
            shoulderZ = (shoulderZ + 5) % 360; 
            glutPostRedisplay(); 
            break;
      case 'S': 
            shoulderZ = (shoulderZ - 5) % 360; 
            glutPostRedisplay(); 
            break;
      
      // Kontrol elbow - dengan batasan seperti siku manusia (0-150 derajat)
      case 'e': 
            elbow = clampAngle(elbow + 5, 0, 150); 
            glutPostRedisplay(); 
            break;
      case 'E': 
            elbow = clampAngle(elbow - 5, 0, 150); 
            glutPostRedisplay(); 
            break;
      
      // Kontrol wrist X
      case 'd': 
            wristX = clampAngle(wristX + 5, -90, 90); 
            glutPostRedisplay(); 
            break;
      case 'D': 
            wristX = clampAngle(wristX - 5, -90, 90); 
            glutPostRedisplay(); 
            break;
      
      // Kontrol wrist Y
      case 'f': 
            wristY = clampAngle(wristY + 5, -90, 90); 
            glutPostRedisplay(); 
            break;
      case 'F': 
            wristY = clampAngle(wristY - 5, -90, 90); 
            glutPostRedisplay(); 
            break;
      
      // Kontrol wrist Z
      case 'g': 
            wristZ = clampAngle(wristZ + 5, -90, 90); 
            glutPostRedisplay(); 
            break;
      case 'G': 
            wristZ = clampAngle(wristZ - 5, -90, 90); 
            glutPostRedisplay(); 
            break;
      
      // Kontrol untuk semua jari ruas pertama
      case 'k': 
            fingerJoint1 = clampAngle(fingerJoint1 + 5, 0, 90); 
            glutPostRedisplay(); 
            break;
      case 'K': 
            fingerJoint1 = clampAngle(fingerJoint1 - 5, 0, 90); 
            glutPostRedisplay(); 
            break;
      
      // Kontrol untuk semua jari ruas kedua
      case 'l': 
            fingerJoint2 = clampAngle(fingerJoint2 + 5, 0, 90); 
            glutPostRedisplay(); 
            break;
      case 'L': 
            fingerJoint2 = clampAngle(fingerJoint2 - 5, 0, 90); 
            glutPostRedisplay(); 
            break;
      
      // Kontrol untuk semua jari ruas ketiga
      case 'p': 
            fingerJoint3 = clampAngle(fingerJoint3 + 5, 0, 90); 
            glutPostRedisplay(); 
            break;
      case 'P': 
            fingerJoint3 = clampAngle(fingerJoint3 - 5, 0, 90); 
            glutPostRedisplay(); 
            break;
      
      // Posisi mengepal
      case 'o':
            fingerJoint1 = 90;
            fingerJoint2 = 90;
            fingerJoint3 = 90;
            glutPostRedisplay();
            break;
      
      // Reset posisi
      case 'r':
            shoulderX = shoulderY = shoulderZ = 0;
            elbow = 0;
            wristX = wristY = wristZ = 0;
            fingerJoint1 = fingerJoint2 = fingerJoint3 = 0;
            glutPostRedisplay();
            break;
      
      case 27:  // ESC key - exit
            exit(0);
            break;
      
      default:
            break;
   }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800, 600);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Tangan");
   init();
   glEnable(GL_DEPTH_TEST);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
