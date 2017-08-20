/**************************************************************************************
FILENAME   : clock.cpp
AUTHOR     : Sek U Cheong
DATE       : 9-27-1999
LAST MODIFY: 10-3-1999

COMPILER   : MS Visual C++ 5.0
PLATFORM   : MS Windows NT 4.0
LIBs       : opengl32.lib glut32.lib glu32.lib


COMMENTS:
This program requires the OpenGL libraries and dynamic link libraries.
You need to tell the VC compiler to link the OpenGL libraries to your
object code. To do so you need to: 

  Go to Project menu -> Settings - > Link and add "opengl32.lib glut32.lib glu32.lib" 
  to the Object/Lib line

To run this program you must have a copy of GLU32.DLL and OPENGL32.DLL 
files installed either in your current directory (ie the directory where 
you run the program) or in the ..\winnt\system32 directory.

***************************************************************************************/


#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <time.h>

using namespace std;

const GLfloat fLineWidth  = 1.0;
struct tm *newtime;        // time
int old_sec;               // saved second
long ltime;                // local time

enum {VIEW, COLOR};

// string for roman numbers
string num1[12] = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII"};
// string for arabic numbers
string num2[12] = {"1","2","3","4","5","6","7","8","9", "10", "11","12"};

string *num=num1; // default numbers to display

int mode = VIEW; // default mode


GLsizei ww = 600, wh = 600; 		// startup window size
double eyeloc[3] = {0,0,15};
double pin_angle[3] ={90,90,90};
GLfloat light1[]={(GLfloat) 202/255, (GLfloat)122/255, (GLfloat)239/255, 1.0f, 1.0f};




// draw n balls with radii r, the distance between each ball is d
void drawBalls(GLfloat r, GLfloat d, int n) {
	GLfloat m = r*2+d;
	glPushMatrix();
	for (int k=0; k<n; k++) {
		glutSolidSphere(r,16,16);
		glTranslated(m, 0.0, 0.0);				
	}
	glPopMatrix();
}


// draw a digit constructed by balls.
void drawDigit(int i, GLfloat r, GLfloat d) {	
	float m = 2*r+d;
	switch (i) {
		case 0:
			glPushMatrix();
				drawBalls(r,d ,4);		
				glRotated(-90.0,0, 0, 1);		
				glTranslated(m, 0.0 , 0.0);				
				drawBalls(r,d,6);
			glPopMatrix();	
			glPushMatrix();
				glTranslated(m, -6*m, 0.0);
				drawBalls(r,d,3);
				glRotated(90,0,0,1);
				glTranslated(m, -2*m , 0);
				drawBalls(r,d,6);
			glPopMatrix();
			break;
		case 1:
			glPushMatrix();
				glTranslated(3*m, 0.0, 0.0);
				glRotated(-90, 0, 0, 1);				
				drawBalls(r,d,7);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
				drawBalls(r,d,4);
				glTranslated(0, -3*m, 0);
				drawBalls(r,d, 4);
				glTranslated(0, -3*m, 0);
				drawBalls(r,d, 4);
			glPopMatrix();
			glPushMatrix();
				glTranslated(3*m, -m, 0);	
				glRotated(-90, 0, 0, 1);							
				drawBalls(r, d, 2);
				glTranslated(3*m, -3*m, 0);		
				drawBalls(r, d, 2);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
				drawBalls(r,d,4);
				glTranslated(0, -3*m, 0);
				drawBalls(r,d, 4);
				glTranslated(0, -3*m, 0);
				drawBalls(r,d, 4);
			glPopMatrix();
			glPushMatrix();
				glTranslated(3*m, -m, 0);	
				glRotated(-90, 0, 0, 1);							
				drawBalls(r, d, 2);
				glTranslated(3*m, 0, 0);		
				drawBalls(r, d, 2);
			glPopMatrix();
			break;
		case 4:
			glPushMatrix();				
				glTranslated(3*m, 0, 0);
				glRotated(-90, 0, 0, 1);			
				drawBalls(r,d,7);
			glPopMatrix();
			glPushMatrix();
				glRotated(-90, 0, 0, 1);
				drawBalls(r, d, 3);			
				glTranslated(3*m, 0 , 0);
				glRotated(90, 0, 0, 1);							
				drawBalls(r, d, 3);
			glPopMatrix();
			break;
		case 5:
			glPushMatrix();
				drawBalls(r,d,4);
				glTranslated(0, -3*m, 0);
				drawBalls(r,d, 4);
				glTranslated(0, -3*m, 0);
				drawBalls(r,d, 4);
			glPopMatrix();
			glPushMatrix();
				glTranslated(0, -m, 0);
				glRotated(-90, 0, 0, 1);
				drawBalls(r, d, 2);		
				glTranslated(3*m, 3*m, 0);
				drawBalls(r, d, 2);			
			glPopMatrix();
			break;
		case 6:
			glPushMatrix();
				glRotated(-90,0,0,1);
				drawBalls(r,d,7);
				glRotated(90,0,0,1);
				glTranslated(m,-6*m, 0);
				drawBalls(r,d,3);
			glPopMatrix();
			glPushMatrix();
				glTranslated(m,0,0);
				drawBalls(r,d,3);
				glTranslated(0,-3*m,0);
				drawBalls(r,d,3);
				glTranslated(2*m, 0,0);
				glRotated(-90, 0,0,1);				
				drawBalls(r,d,3);
			glPopMatrix();
			break;
		case 7:
			glPushMatrix();
				drawBalls(r,d,3);
				glTranslated(3*m, 0.0, 0.0);
				glRotated(-90, 0, 0, 1);				
				drawBalls(r,d,7);
			glPopMatrix();
			break;
		case 8:
			glPushMatrix();
				glRotated(-90,0,0,1);
				drawBalls(r,d,7);
				glRotated(90,0,0,1);
				glTranslated(m,-6*m, 0);
				drawBalls(r,d,2);
			glPopMatrix();
			glPushMatrix();
				glTranslated(m,0,0);
				drawBalls(r,d,2);
				glTranslated(0,-3*m,0);
				drawBalls(r,d,2);
				glTranslated(2*m, 3*m,0);
				glRotated(-90, 0,0,1);				
				drawBalls(r,d,7);
			glPopMatrix();
			break;
		case 9:
			glPushMatrix();
				drawBalls(r,d,3);
				glTranslated(0,-3*m,0);
				drawBalls(r,d,3);
				glRotated(90,0,0,1);
				glTranslated(m,0,0);
				drawBalls(r,d,2);
			glPopMatrix();
			glPushMatrix();				
				glTranslated(3*m, 0, 0);
				glRotated(-90, 0,0,1);				
				drawBalls(r,d,7);
			glPopMatrix();
			break;
			
				
	}
}


void drawDigitalTime(int h, int m, int s, GLfloat r, GLfloat d) {
	GLfloat l = r*2+d;
	if (h>=10) drawDigit(h / 10, r, d);
	glPushMatrix();
		glTranslated(1.8,0,0);
		drawDigit(h%10, r, d);
		glTranslated(2,0,0);		
		glPushMatrix();
			glRotated(-90,0,0,1);
			glTranslated(l,0,0);
			drawBalls(r,3*l,2);
		glPopMatrix();
		glTranslated(1,0,0);
		
		drawDigit(m/10, r, d);
		glTranslated(1.8,0,0);
		drawDigit(m%10, r, d);

		glTranslated(2,0,0);
		glPushMatrix();
			glRotated(-90,0,0,1);
			glTranslated(l,0,0);
			drawBalls(r,3*l,2);
		glPopMatrix();
		glTranslated(1,0,0);

		drawDigit(s/10, r, d);
		glTranslated(1.8,0,0);
		drawDigit(s%10, r, d);
	glPopMatrix();
}


// converts integer color value to GLfloat
inline GLfloat i2f(int n) {
	return (GLfloat) n / 255.0;
}


// polygon drawing routine
void polygon(int n, GLfloat poly[][3])
{
	int i;
	glBegin(GL_POLYGON);
	    for(i=0;i<n;i++)
	       glVertex3f(poly[i][0], poly[i][1], poly[i][2]);
	glEnd();
}


// string darwing routine
void drawString(GLfloat fSize, char *str)
{
	char *p;
	glPushMatrix();			
		glScalef(fSize/500, fSize/500, fSize/500); // set font size
		for (p = str; *p; p++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	glPopMatrix();
}



// sets the lighting and shading mode
void init() {
	GLfloat light_position[]={50, 50, 50.0, 0.0};    // light position
	GLfloat mat_specular[]={0.8f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[]={50.0};	
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_DEPTH_TEST); 

	glViewport(0,0,ww,wh);
	glShadeModel(GL_SMOOTH);
    glClearColor(0.0,0.0,0.0,0.0);

    time( &ltime );
    newtime = gmtime( &ltime );
	old_sec = newtime->tm_sec;
	pin_angle[0] = 90 + newtime->tm_sec*6;
	pin_angle[1] = 90 + newtime->tm_min*6 + newtime->tm_sec/10;
	pin_angle[2] = 90 + newtime->tm_hour*30 + newtime->tm_min/2;

}


void display() {
    // different light sources
	static GLfloat light2[]={i2f(255), i2f(226), i2f(60), 1.0f, 1.0f}; 
	static GLfloat light3[]={i2f(255), i2f(214), i2f(142), 1.0f, 1.0f};

	static GLfloat r=0.15f, d=0.05f; // ball radius and distance
	static int k;

	// polgonys used to draw the pins and scales of the colck
	GLfloat pin1[4][3]={{-1,0,0},{0,0.2f,0},{10,0,0}, {0,-0.2f,0}}; // second pin
	GLfloat pin2[4][3]={{-1,0,0},{0,0.6f,0},{8,0,0},{0,-0.6f,0}};   // minute pin
	GLfloat pin3[4][3]={{-1,0,0},{0,0.8f,0},{5,0,0},{0,-0.8f,0}};   // hour pin
	GLfloat scale1[4][3]={{-2,0.5f,0}, {2,0.5f,0}, {2,-0.5f,0},{-2,-0.5f,0}}; // scales

	

	glClearColor(0.0,0.0,0.0,0.0);   // clears view port
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(	eyeloc[0], eyeloc[1], eyeloc[2],    // sets view location
		        0.0, 0.0, 0.0,  
				0.0, 1.0, 0.0);


	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1);       // sets lighting mode	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutSolidTorus(0.3, 14, 128, 128);              // draws the farme of the clock
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glRotated(180,0,1,0);
	glPushMatrix();
	glRotated(pin_angle[0],0,0,1);                 // sets the right angle of the pin
	glColor3f(i2f(255), i2f(103), i2f(99));        // sets color
	polygon(4,pin1);                               // darws the pin
	glPopMatrix();
	

	// draws the minute pin
	glPushMatrix();
	glRotated(pin_angle[1],0,0,1);	
	glColor3f(i2f(8),i2f(196),i2f(128));
	polygon(4,pin2);
	glPopMatrix();


	//draws the hour pin
	glPushMatrix();
	glRotated(pin_angle[2],0,0,1);		
	glColor3f(i2f(2),i2f(126),i2f(172));
	polygon(4,pin3);
	glPopMatrix();
	glPopMatrix();


	// draws the hour scale
	glColor3f(0.82f, 0.72f, 0.32f);	
	for (k=0; k<12; k++) {
		glPushMatrix();
			glRotated(k*30,0,0,1);
			glTranslatef(13, 0, 0);
			glScalef(0.2f,0.1f,1);
			glColor3f(1,(GLfloat)169/255, (GLfloat)112/255);
			polygon(4,scale1);		
		glPopMatrix();
	}


	// draws the minute scale
	for (k=0; k<60; k++) {
		glPushMatrix();
			glRotated(k*6,0,0,1);
			glTranslatef(13, 0, 0);
			glScalef(0.2f,1,1);
			glColor3f(1,(GLfloat)169/255, (GLfloat)112/255);
			glBegin(GL_LINES);
				glVertex3f(0,0,0);
				glVertex3f(2,0,0);
			glEnd();
		glPopMatrix();
	}

	// draws the number on the clock
	glColor3f(i2f(198),i2f(255),i2f(217));
	for (k=0; k<12; k++) {	
		glPushMatrix();			
		glRotated(60-k*30,0,0,1);	
		glTranslated(11,0,0);
		glRotated(-60+k*30,0,0,1);
		drawString(6, (char*) num[k].c_str());
		glPopMatrix();
	}
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light2);

	// draws a nob
	glutSolidSphere(0.3,32,32);	

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light3);	// changs light color
	glTranslated(-6.5f,7,0);						
	// draws the digital clock
	drawDigitalTime(newtime->tm_hour,newtime->tm_min,newtime->tm_sec, r, d);


	glOrtho(0.0,ww-1.0, 0.0,wh-1.0,-1.0,1.0);	
	glMatrixMode(GL_MODELVIEW); 
	glFlush();
	glutSwapBuffers();
}



void reshape(int w, int h) {
	double aspect_ratio;
	aspect_ratio = (double)w / (double) ((h==0) ? 1:h); // resets the ratio
	glViewport(0, 0, w, h);      // reset the viewport
	glMatrixMode(GL_PROJECTION); // sets projection mode
	glLoadIdentity();
    gluPerspective(90.0, aspect_ratio, 1.0, 256.0);
	glMatrixMode(GL_MODELVIEW);
	ww = w;
	wh = h;
}



void idle(void) {
	time( &ltime );
    newtime = localtime( &ltime ); 
	// sets the right angle for the clock pins
	if (newtime->tm_sec!=old_sec) { // is time changed?
		old_sec = newtime->tm_sec;
		pin_angle[0] = 90 + newtime->tm_sec*6;
		pin_angle[1] = 90 + newtime->tm_min*6 + newtime->tm_sec/10;
		pin_angle[2] = 90 + newtime->tm_hour*30 + newtime->tm_min/2;
		display();
	}
}



void keyfun(unsigned char key, int x ,int y) {
	switch (key) {
		case '7':
			switch (mode) {
				case VIEW: eyeloc[0]+=2; break;
				case COLOR: light1[0]+=0.01f; break;				
			}
			break;
		case '9':
			switch (mode) {
				case VIEW: eyeloc[0]-=2; break;
				case COLOR: light1[0]-=0.01f; break;				
			}			
			break;
		case '4':
			switch (mode) {
				case VIEW: eyeloc[1]+=2; break;
				case COLOR: light1[1]+=0.01f; break;			
			}			
			break;			
		case '6':
			switch (mode) {
				case VIEW: eyeloc[1]-=2; break;
				case COLOR: light1[1]-=0.01f; break;				
			}						
			break;
		case '1':
			switch (mode) {
				case VIEW: eyeloc[2]+=2; break;
				case COLOR: light1[2]+=0.01f; break;				
			}									
			break;
		case '3':
			switch (mode) {
				case VIEW: eyeloc[2]-=2; break;
				case COLOR: light1[2]-=0.01f; break;				
			}											
			break;
		case 'T':
		case 't':
			if (num==num1) {
				num=num2; 
				cout << "** displaying Arabic numbers"<< endl;
			} else {
				num=num1;
				cout << "** displaying Roman numbers"<< endl;
			}
			break;
		case 'V':
		case 'v':
			cout <<"** view mode" << endl;
			cout <<"     (7/9) -> (+/-) eyex" << endl;
			cout <<"     (4/6) -> (+/-) eyey" << endl;
			cout <<"     (1/3) -> (+/-) eyez" << endl;
			mode = VIEW;
			break;
		case 'C':
		case 'c':
			cout <<"** color mode" << endl;
			cout <<"     (7/9) -> (+/-) R" << endl;
			cout <<"     (4/6) -> (+/-) G" << endl;
			cout <<"     (1/3) -> (+/-) B" << endl;
			mode = COLOR;
			break;
	}
	idle(); // redraws the clock;
}



int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("Sek's 3D Clock");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLineWidth(fLineWidth);
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyfun);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
    return 0;
}
