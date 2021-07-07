//  ========================================================================
//  COSC363: Computer Graphics (2021);  CSSE, University of Canterbury.
//
//  FILE NAME: Assingment1.cpp
//  Author: Oliver Cranshaw
//  ========================================================================

#define GL_CLAMP_TO_EDGE 0x812F

#include <iostream>
#include <cmath> 
#include <GL/freeglut.h>
#include "loadBMP.h"

using namespace std;

GLUquadric *q;    //Required for creating cylindrical objects
float angle = 0, look_x = 0, look_y = 0, look_z = 0, eye_x = 0, eye_y = 50, eye_z = 80;

float ball_1_y = 27.3;
float ball_2_y = 29.15;
float ball_3_y = 27.3;
float ball_4_y = 21;


float ball_max_hgt = 29.15;
float ball_min_hgt = 21;

float ball_1_speed_y = -0.7;
float ball_2_speed_y = 0;
float ball_3_speed_y = 0.6;
float ball_4_speed_y = 1.3;

float ball_1_dir = 0;
float ball_2_dir = 0;
float ball_3_dir = 1;
float ball_4_dir = 1;


float arm_rot = 0;
float arm_speed = 13.3;

const int N = 152;  // Total number of vertices on the base curve


float vx_init[N] = { 1, 1, 1, 1, 1.2, 1.2, 1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 1.3, 1.4, 1.6, 
					1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 1.3, 1.4, 
					1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 1.3, 
					1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 
					1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 
					1.2, 1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 
					1.3, 1.2, 1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 
					1.4, 1.3, 1.2, 1.3, 1.4, 1.6, 1.8, 1.9, 1.8, 1.6, 1.4, 1.3, 1.2, 1.2, 1, 1, 1, 1, 1};

float vy_init[N] = { 0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10,
					  10.5, 11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5, 16, 16.5, 17, 17.5, 18, 18.5, 19, 19.5, 20,
					  20.5, 21, 21.5, 22, 22.5, 23, 23.5, 24, 24.5, 25, 25.5, 26, 26.5, 27, 27.5, 28, 28.5, 29, 29.5, 30, 30.5, 31,
					  31.5, 32, 32.5, 33, 33.5, 34, 34.5, 35, 35.5, 36, 36.5,37,37.5,38,38.5,39,39.5,40,40.5,41,41.5,42,42.5,43,43.5,
						44,44.5,45,45.5,46,46.5,47,47.5,48,48.5,49,49.5,50,50.5,51,51.5,52,52.5,53,53.5,54,54.5,55,55.5,56,56.5,57,57.5,58,58.5,59,59.5,60,60.5,61,61.5,62,62.5,63,63.5,64,64.5,65,65.5,66,66.5,67,67.5,68,68.5,69,69.5,70,70.5,71,71.5,72,72.5,73,73.5,74,74.5,75,75.5 };
float vz_init[N] = { 0 };

GLuint txId[8]; 

//----------------------------------------------------------
void loadTexture()
{
	glGenTextures(8, txId); 	// Create 8 texture ids

	glBindTexture(GL_TEXTURE_2D, txId[0]);
	loadBMP("back.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[1]);
	loadBMP("bottom.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[2]);
	loadBMP("front.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[3]);
	loadBMP("left.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[4]);
	loadBMP("right.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[5]);
	loadBMP("top.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
	glBindTexture(GL_TEXTURE_2D, txId[6]);
	loadBMP("WoodTexture.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBindTexture(GL_TEXTURE_2D, txId[7]);
	loadBMP("VaseTexture.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

//-------------------------------------------------------------------
void createSkybox()
{
	//back
	glBindTexture(GL_TEXTURE_2D, txId[0]);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0.0, 1.0);     glVertex3f(-200, 200, -200);
	glTexCoord2f(0.0, 0.0);     glVertex3f(-200, 0, -200);
	glTexCoord2f(1.0, 0.0);     glVertex3f(200, 0, -200);
	glTexCoord2f(1.0, 1.0);     glVertex3f(200, 200, -200);
	glEnd();

	//bottom
	glBindTexture(GL_TEXTURE_2D, txId[1]);
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(1.0, 0.0);     glVertex3f(-200, 0, -200);
	glTexCoord2f(1.0, 1.0);     glVertex3f(-200, 0, 200);
	glTexCoord2f(0.0, 1.0);     glVertex3f(200, 0, 200);
	glTexCoord2f(0.0, 0.0);     glVertex3f(200, 0, -200);
	glEnd();

	//front
	glBindTexture(GL_TEXTURE_2D, txId[2]);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0, 1.0);     glVertex3f(200, 200, 200);
	glTexCoord2f(0.0, 0.0);     glVertex3f(200, 0, 200);
	glTexCoord2f(1.0, 0.0);     glVertex3f(-200, 0, 200);
	glTexCoord2f(1.0, 1.0);     glVertex3f(-200, 200, 200);
	glEnd();

	//left
	glBindTexture(GL_TEXTURE_2D, txId[3]);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(1.0, 1.0);     glVertex3f(-200, 200, -200);
	glTexCoord2f(0.0, 1.0);     glVertex3f(-200, 200, 200);
	glTexCoord2f(0.0, 0.0);     glVertex3f(-200, 0, 200);
	glTexCoord2f(1.0, 0.0);     glVertex3f(-200, 0, -200);
	glEnd();

	//right
	glBindTexture(GL_TEXTURE_2D, txId[4]);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);     glVertex3f(200, 200, -200);
	glTexCoord2f(1.0, 1.0);     glVertex3f(200, 200, 200);
	glTexCoord2f(1.0, 0.0);     glVertex3f(200, 0, 200);
	glTexCoord2f(0.0, 0.0);     glVertex3f(200, 0, -200);
	glEnd();


	//top
	glBindTexture(GL_TEXTURE_2D, txId[5]);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0, 1.0);     glVertex3f(-200, 200, -200);
	glTexCoord2f(1.0, 0.0);     glVertex3f(-200, 200, 200);
	glTexCoord2f(0.0, 0.0);     glVertex3f(200, 200, 200);
	glTexCoord2f(0.0, 1.0);     glVertex3f(200, 200, -200);
	glEnd();
}

//-- Ground Plane --------------------------------------------------------
void floor()
{
	glDisable(GL_LIGHTING);
	glColor3f(0.7, 0.7,  0.7);			//Floor colour

	for(int i = -200; i <= 200; i +=5)
	{
		glBegin(GL_LINES);			//A set of grid lines on the xz-plane
			glVertex3f(-200, 0, i);
			glVertex3f(200, 0, i);
			glVertex3f(i, 0, -200);
			glVertex3f(i, 0, 200);
		glEnd();
	}
	glEnable(GL_LIGHTING);
}

void drawCyclinder() {
	
	glBindTexture(GL_TEXTURE_2D, txId[6]);
	GLUquadric *q = gluNewQuadric();
	gluQuadricDrawStyle (q, GLU_FILL);
	gluQuadricNormals (q, GLU_SMOOTH);
	gluQuadricTexture(q, GL_TRUE);
	gluCylinder(q, 3, 5, 18, 30, 30);
}

void drawCentreCylinder() {
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[6]);
	GLUquadric *q = gluNewQuadric();
	gluQuadricDrawStyle (q, GLU_FILL);
	gluQuadricNormals (q, GLU_SMOOTH);
	gluQuadricTexture(q, GL_TRUE);
	gluCylinder(q, 2, 3, 18, 30, 30);
	glDisable(GL_TEXTURE_2D);
}
	

void drawSphere() {
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[7]);
	GLUquadric *q = gluNewQuadric();
	gluQuadricDrawStyle (q, GLU_FILL);
	gluQuadricNormals (q, GLU_SMOOTH);
	gluQuadricTexture(q, GL_TRUE);
	gluSphere (q, 3, 30, 30);
	glDisable(GL_TEXTURE_2D);
}

//------Event handler for special key events -------------------------------------
void special(int key, int x, int y)
{

	if (key == GLUT_KEY_LEFT) angle -= 0.1;  //Change direction
	else if (key == GLUT_KEY_RIGHT) angle += 0.1;
	else if (key == GLUT_KEY_DOWN)
	{  //Move backward
		eye_x -= 0.6 * sin(angle);
		eye_z += 0.6 * cos(angle);
	}
	else if (key == GLUT_KEY_UP)
	{ //Move forward
		eye_x += 0.6 * sin(angle);
		eye_z -= 0.6 * cos(angle);
	}

	else if (key == GLUT_KEY_PAGE_UP) eye_y++;
	else if (key == GLUT_KEY_PAGE_DOWN) eye_y--;
	else if (key == GLUT_KEY_HOME) look_y++;
	else if (key == GLUT_KEY_END) look_y--;

	look_x = eye_x + 100 * sin(angle);
	look_z = eye_z - 100 * cos(angle);


	glutPostRedisplay();
}

//--------------------------------------------------------------------------------
void initialise()
{ 
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};

	q = gluNewQuadric();
	loadTexture();

	glClearColor(1., 1., 1., 1.);  //Background colour 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_SMOOTH);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

}

void normal(float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3)
{
	float nx, ny, nz;
	nx = y1 * (z2 - z3) + y2 * (z3 - z1) + y3 * (z1 - z2);
	ny = z1 * (x2 - x3) + z2 * (x3 - x1) + z3 * (x1 - x2);
	nz = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);

	glNormal3f(nx, ny, nz);
}


//--------------------------------------------------------------------------------
void display() 
{
    float lgt_pos[] = {30.0f, 50.0f, 50.0f, 1.0f};	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_MODELVIEW);								
	glLoadIdentity();
	gluPerspective(45., 1., 1., 500);

	gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
	
	glPushMatrix();
	glTranslatef(0.0, -0.1, 0.0);
	floor();
	glPopMatrix();
	
	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
	
		createSkybox();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	float vx[N], vy[N], vz[N];
	float wx[N], wy[N], wz[N];

	for (int i = 0; i < N; i++)		
	{
		vx[i] = vx_init[i];
		vy[i] = vy_init[i];
		vz[i] = vz_init[i];
	}
	
	float shadowMat[16] = { 50.0f,0,0,0, -5.0f,0,-100.0f,-1, 0,0,50.0f,0, 0,0,0,50.0f };
	glDisable(GL_LIGHTING);
	
	glColor3f(0., 0., 0.);
	glPushMatrix();
		glTranslatef(0, 0.1, 0);
		glMultMatrixf(shadowMat);
		glTranslatef(30, 18, 0);	
		glRotatef(90.0, 1, 0, 0);
		drawCyclinder();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0.1, 0);
		glMultMatrixf(shadowMat);
		glTranslatef(-30, 18, 0);
		glRotatef(90.0, 1, 0, 0);
		drawCyclinder();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0.1, 0);
		glMultMatrixf(shadowMat);
		glTranslatef(0, 18, 30);
		glRotatef(90.0, 1, 0, 0);
		drawCyclinder();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 0.1, 0);
		glMultMatrixf(shadowMat);
		glTranslatef(0, 18, -30);
		glRotatef(90.0, 1, 0, 0);
		drawCyclinder();
	glPopMatrix();
	
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	
		glPushMatrix();
			glTranslatef(30, 18, 0);	
			glRotatef(90.0, 1, 0, 0);
			drawCyclinder();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-30, 18, 0);
			glRotatef(90.0, 1, 0, 0);
			drawCyclinder();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 18, 30);
			glRotatef(90.0, 1, 0, 0);
			drawCyclinder();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 18, -30);
			glRotatef(90.0, 1, 0, 0);
			drawCyclinder();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(30, ball_1_y, 0);
			drawSphere();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-30, ball_3_y, 0);
			drawSphere();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, ball_2_y, 30);
			drawSphere();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, ball_4_y, -30);
			drawSphere();
		glPopMatrix();


		glPushMatrix();
			glTranslatef(0, 18, 0);
			glRotatef(90.0, 1, 0, 0);
			drawCentreCylinder();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 21, 0);
			drawSphere();
		glPopMatrix();
		
		glDisable(GL_TEXTURE_2D);
		glColor3f(1, 0.1, 0.1);
		glPushMatrix();
			glTranslatef(0, 25, 0);
			glRotatef(90.0, 1, 0, 0);
			glRotatef(arm_rot, 0, 0, 1);
			glTranslatef(0, -37.5, 0);

			for (int j = 0; j < 36; j++) //36 slices in 10 deg steps
			{
				for (int i = 0; i < N; i++) //N vertices along each slice
				{
					wx[i] = vx[i] * cos(0.174533) + vz[i] * sin(0.174533); //Get transformed points W using 10 deg rotn
					wy[i] = vy[i];
					wz[i] = -vx[i] * sin(0.174533) + vz[i] * cos(0.174533);
				}
				glBegin(GL_TRIANGLE_STRIP); //Create triangle strip using V, W
				for (int i = 0; i < N; i++) {
					if (i > 0) normal(vx[i - 1], vy[i - 1], vz[i - 1],
						wx[i - 1], wy[i - 1], wz[i - 1],
						vx[i], vy[i], vz[i]);
					glVertex3f(vx[i], vy[i], vz[i]);
					if (i > 0) normal(wx[i - 1], wy[i - 1], wz[i - 1],
						wx[i], wy[i], wz[i],
						vx[i], vy[i], vz[i]);
					glVertex3f(wx[i], wy[i], wz[i]);
				}
				glEnd();
				//Copy W array to V for next iteration
				for (int i = 0; i < N; i++)
				{
					vx[i] = wx[i];
					vy[i] = wy[i];
					vz[i] = wz[i];
				}
		}
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();									
}

void move(int time)
{


	ball_1_y += ball_1_speed_y;
	ball_2_y += ball_2_speed_y;
	ball_3_y += ball_3_speed_y;
	ball_4_y += ball_4_speed_y;

	arm_rot += arm_speed;

		if (arm_rot >= 359) {
		arm_rot = 0;
	}


	if (ball_1_y <= ball_min_hgt) {
		ball_1_speed_y = 1.4;
		ball_1_dir = 1;
	}
	if (ball_2_y <= ball_min_hgt) {
		ball_2_speed_y = 1.4;
		ball_2_dir = 1;
	}
	if (ball_3_y <= ball_min_hgt) {
		ball_3_speed_y = 1.4;
		ball_3_dir = 1;
	}
	if (ball_4_y <= ball_min_hgt) {
		ball_4_speed_y = 1.4;
		ball_4_dir = 1;
	}






	if (ball_1_y >= ball_max_hgt) {
		ball_1_dir = 0;
	}
	if (ball_2_y >= ball_max_hgt) {
		ball_2_dir = 0;
	}
	if (ball_3_y >= ball_max_hgt) {
		ball_3_dir = 0;
	}
	if (ball_4_y >= ball_max_hgt) {
		ball_4_dir = 0;
	}
	

	ball_1_speed_y -= 0.1;
	ball_2_speed_y -= 0.1;
	ball_3_speed_y -= 0.1;
	ball_4_speed_y -= 0.1;

	glutPostRedisplay();


	glutTimerFunc(50, move, 0);
}



//--------------------------------------------------------------------------------
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (800, 800); 
   glutInitWindowPosition (50, 50);
   glutCreateWindow ("Kinda Cool");
   initialise();

   glutTimerFunc(50, move, 0);
   glutDisplayFunc(display); 
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}
