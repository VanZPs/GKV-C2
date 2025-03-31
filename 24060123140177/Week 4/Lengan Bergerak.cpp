#include <GL/glut.h>

static int shoulder = 0, elbow = 0, wrist = 0;
static int finger1 = 0, finger2 = 0, finger3 = 0, finger4 = 0, finger5 = 0;

void init(void) {
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void drawFinger(float length, float width, int angle) {
   glPushMatrix();
   glRotatef((GLfloat)angle, 0.0, 1.0, 0.0); 
   glTranslatef(0.0, length/2, 0.0);
   glScalef(width, length, width);
   glutWireCube(1.0);
   glPopMatrix();
}

void display(void) {
   glClear (GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0); 
   
   // Shoulder to elbow (upper arm)
   glTranslatef (-1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   
   // Elbow to wrist (lower arm)
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   
   // Wrist to palm (hand) 
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) wrist, 0.0, 0.0, 1.0);
   glRotatef (90.0, 0.0, 1.0, 0.0); 
   glTranslatef (0.0, 0.0, 0.5);
   
   // Draw palm 
   glPushMatrix();
   glScalef (1.0, 1.2, 0.3); 
   glutWireCube (1.0);
   glPopMatrix();
   
   // Thumb (jempol)
   glPushMatrix();
   glTranslatef (-0.4, -0.3, 0.0);
   glRotatef(-60, 0.0, 0.0, 1.0); 
   drawFinger(0.6, 0.2, finger1);
   glPopMatrix();
   
   // Index finger (telunjuk)
   glPushMatrix();
   glTranslatef (-0.3, 0.6, 0.0);
   drawFinger(0.7, 0.15, finger2);
   glPopMatrix();
   
   // Middle finger (jari tengah)
   glPushMatrix();
   glTranslatef (-0.1, 0.6, 0.0);
   drawFinger(0.8, 0.15, finger3); 
   glPopMatrix();
   
   // Ring finger (jari manis)
   glPushMatrix();
   glTranslatef (0.1, 0.6, 0.0);
   drawFinger(0.75, 0.15, finger4);
   glPopMatrix();
   
   // Little finger (kelingking)
   glPushMatrix();
   glTranslatef (0.3, 0.6, 0.0);
   drawFinger(0.6, 0.12, finger5); 
   glPopMatrix();
   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -6.0);  
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      // Shoulder controls
      case 's': shoulder = (shoulder + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S': shoulder = (shoulder - 5) % 360;
         glutPostRedisplay();
         break;
      
      // Elbow controls
      case 'e': elbow = (elbow + 5) % 360;
         glutPostRedisplay();
         break;
      case 'E': elbow = (elbow - 5) % 360;
         glutPostRedisplay();
         break;
      
      // Wrist controls
      case 'w': wrist = (wrist + 5) % 360;
         glutPostRedisplay();
         break;
      case 'W': wrist = (wrist - 5) % 360;
         glutPostRedisplay();
         break;
      
      // Finger controls
      case '1': finger1 = (finger1 + 5) % 90;  
         glutPostRedisplay();
         break;
      case '!': finger1 = (finger1 - 5) % 90;
         glutPostRedisplay();
         break;
      
      case '2': finger2 = (finger2 + 5) % 90; 
         glutPostRedisplay();
         break;
      case '@': finger2 = (finger2 - 5) % 90;
         glutPostRedisplay();
         break;
      
      case '3': finger3 = (finger3 + 5) % 90;  
         glutPostRedisplay();
         break;
      case '#': finger3 = (finger3 - 5) % 90;
         glutPostRedisplay();
         break;
      
      case '4': finger4 = (finger4 + 5) % 90;  
         glutPostRedisplay();
         break;
      case '$': finger4 = (finger4 - 5) % 90;
         glutPostRedisplay();
         break;
      
      case '5': finger5 = (finger5 + 5) % 90;  
         glutPostRedisplay();
         break;
      case '%': finger5 = (finger5 - 5) % 90;
         glutPostRedisplay();
         break;
      
      // Make all fingers curl at once
      case 'f': 
         finger1 = finger2 = finger3 = finger4 = finger5 = (finger1 + 5) % 90;
         glutPostRedisplay();
         break;
      case 'F': 
         finger1 = finger2 = finger3 = finger4 = finger5 = (finger1 - 5) % 90;
         glutPostRedisplay();
         break;
      
      // Reset position
      case 'r':
         shoulder = elbow = wrist = 0;
         finger1 = finger2 = finger3 = finger4 = finger5 = 0;
         glutPostRedisplay();
         break;
      case 27: exit(0);  
         break;
      default: break;
   }
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (700, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Lengan Bergerak");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
