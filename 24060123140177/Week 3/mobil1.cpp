#include <GL/glut.h>
#include <math.h>

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawFilledStar(float cx, float cy, float outerRadius, float innerRadius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); 
    for (int i = 0; i <= 10; i++) {
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        float theta = 3.1415926f / 5.0f * i;
        float x = radius * sinf(theta);
        float y = radius * cosf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawStarBorder(float cx, float cy, float outerRadius, float innerRadius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 10; i++) {
        float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        float theta = 3.1415926f / 5.0f * i;
        float x = radius * sinf(theta);
        float y = radius * cosf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.98, 0.76, 0.84); 
    glBegin(GL_POLYGON);
        glVertex2f(-0.8, -0.25);  
        glVertex2f(0.8, -0.25);   
        glVertex2f(0.8, 0.1);    
        glVertex2f(0.6, 0.1);     
        glVertex2f(0.5, 0.3);     
        glVertex2f(-0.5, 0.3);    
        glVertex2f(-0.6, 0.1);    
        glVertex2f(-0.8, 0.1);    
    glEnd();
    
    glColor3f(0.7, 0.9, 0.9); 
    glBegin(GL_POLYGON);
        glVertex2f(-0.45, 0.1);
        glVertex2f(0.45, 0.1);
        glVertex2f(0.4, 0.25);
        glVertex2f(-0.4, 0.25);
    glEnd();
    
    glColor3f(0.0, 0.0, 0.0); 
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.1);
        glVertex2f(0.0, 0.25);
    glEnd();
    
    glBegin(GL_LINES);
        glVertex2f(0.0, -0.25);
        glVertex2f(0.0, 0.1);
    glEnd();
    glLineWidth(1.0);
    
	glColor3f(1.0, 1.0, 1.0); 
	drawCircle(-0.7, -0.1, 0.08, 30);

	glColor3f(1.0, 1.0, 0.0); 
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 15; i++) {  
    	float theta = (-3.1415926f/2) + (3.1415926f * float(i) / float(15));
    	float x = 0.04 * cosf(theta); 
    	float y = 0.04 * sinf(theta);
    	glVertex2f(x - 0.7, y - 0.1);  
	}
	
	glVertex2f(-0.7, -0.14);  
	glVertex2f(-0.7, -0.06);  
	glEnd();
    
    glColor3f(1.0, 0.0, 0.0); 
    glBegin(GL_POLYGON);
        glVertex2f(0.7, -0.15);
        glVertex2f(0.7, -0.05);
        glVertex2f(0.75, -0.05);
        glVertex2f(0.75, -0.15);
    glEnd();
    
   	
   	glColor3f(0.6, 0.6, 0.6); 
   	glBegin(GL_POLYGON);
    	glVertex2f(-0.18, 0.06);   
    	glVertex2f(-0.08, 0.06);  
    	glVertex2f(-0.08, 0.01);   
    	glVertex2f(-0.18, 0.01);   
	glEnd();
		
	glBegin(GL_POLYGON);
    	glVertex2f(0.32, 0.06);   
    	glVertex2f(0.42, 0.06);    
    	glVertex2f(0.42, 0.01);    
    	glVertex2f(0.32, 0.01);    
  	glEnd();
    
    glColor3f(0.0, 0.0, 0.0); 
    drawCircle(-0.5, -0.25, 0.12, 30);
    
    drawCircle(0.5, -0.25, 0.12, 30);
    
	glColor3f(1.0, 1.0, 1.0); 
	drawFilledStar(-0.5, -0.25, 0.08, 0.04);

	glColor3f(0.75, 0.75, 0.75); 
	glLineWidth(1.5);
	drawStarBorder(-0.5, -0.25, 0.08, 0.04);

	glColor3f(1.0, 1.0, 1.0); 
	drawFilledStar(0.5, -0.25, 0.08, 0.04);

	glColor3f(0.75, 0.75, 0.75); 
	drawStarBorder(0.5, -0.25, 0.08, 0.04);
    
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mobil 2D dengan OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
return 0;
}
