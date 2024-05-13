#include <windows.h>
#include <gl/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<iostream>

using namespace std;

GLfloat T = 180;
void Spin()
{
	T = T + 0.01;
	if (T > 360)
		T = 0;
	glutPostRedisplay();
}

void MyInit()
{
	glClearColor(0, 1, 0, 1);
	glEnable(GL_DEPTH_TEST);
}


void PyramidFace(GLfloat A[], GLfloat B[], GLfloat C[])
{
	glBegin(GL_POLYGON);
		glVertex3fv(A);
		glVertex3fv(B);
		glVertex3fv(C);
	glEnd();
}
void Pyramid(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[])
{
	PyramidFace(V0, V1, V2);
	PyramidFace(V0, V1, V3);
	PyramidFace(V0, V3, V4);
	PyramidFace(V0, V4, V2);
}

void RectangleFace(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[])
{
	glBegin(GL_POLYGON);
		glVertex3fv(A);
		glVertex3fv(B);
		glVertex3fv(C);
		glVertex3fv(D);
	glEnd();
}
void Rectangle(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
	//draw faces
	RectangleFace(V0, V1, V2, V3); //Front

	RectangleFace(V4, V5, V6, V7); //Back

	RectangleFace(V4, V0, V3, V7); //Left

	RectangleFace(V1, V5, V6, V2); //Right

	RectangleFace(V0, V1, V5, V4); //Top

	RectangleFace(V3, V2, V6, V7); //Bottom
}

void DrawHouse()
{
	//1st floor
	GLfloat floor1[8][3] = {
		// front face
		{-0.5, 0.0, 0.5},
		{0.5, 0.0, 0.5},
		{0.5, -0.4, 0.5},
		{-0.5, -0.4, 0.5},
		// back face Z values become negatives
		{-0.5, 0.0, -0.5},
		{0.5, 0.0, -0.5},
		{0.5, -0.4, -0.5},
		{-0.5, -0.4, -0.5},
	};
	// left window 
	GLfloat Window1[4][3] = {
		{0.30, -0.15, 0.50001},
		{0.20, -0.15, 0.50001},
		{0.20, -0.25, 0.50001},
		{0.30, -0.25, 0.50001}
	};
	// right window
	GLfloat Window2[4][3] = {
		{-0.30, -0.15, 0.50001},
		{-0.20, -0.15, 0.50001},
		{-0.20, -0.25, 0.50001},
		{-0.30, -0.25, 0.50001}
	};
	// door
	GLfloat Door[4][3] = {
		{0.05, -0.4, 0.50001},
		{0.05, -0.25, 0.50001},
		{-0.05, -0.25, 0.50001},
		{-0.05, -0.4, 0.50001}
	};

	// 2nd floor	
	GLfloat floor2[8][3] = {
		// front face
		{-0.5, 0.4, 0.5},
		{0.5, 0.4, 0.5},
		{0.5, 0.0, 0.5},
		{-0.5, 0.0, 0.5},
		// back face Z values become negatives
		{-0.5, 0.4, -0.5},
		{0.5, 0.4, -0.5},
		{0.5, -0.0, -0.5},
		{-0.5, -0.0, -0.5},
	};
	// left window 
	GLfloat Window3[4][3] = {
		{0.30, 0.15, 0.50001},
		{0.20, 0.15, 0.50001},
		{0.20, 0.25, 0.50001},
		{0.30, 0.25, 0.50001}
	};
	// right window
	GLfloat Window4[4][3] = {
		{-0.30, 0.15, 0.50001},
		{-0.20, 0.15, 0.50001},
		{-0.20, 0.25, 0.50001},
		{-0.30, 0.25, 0.50001}
	};
	// roof
	GLfloat Roof[5][3] = {
		// pyramid tip
		{0.0, 0.75, 0},
		// pyramid base
		{-0.5, 0.4, 0.5},
		{0.5, 0.4, 0.5},
		{-0.5, 0.4, -0.5},
		{0.5, 0.4, -0.5},

	};

	

	glRotatef(T, 0, 1, 0); // rotate
	
	
	
	// draw the 1st floor walls
	glColor3f(0.8f, 0.6f, 0.4f);
	Rectangle(floor1[0], floor1[1], floor1[2], floor1[3], floor1[4], floor1[5], floor1[6], floor1[7]);

	// window
	glColor3f(1, 1, 1);
	RectangleFace(Window1[0], Window1[1], Window1[2], Window1[3]);
	RectangleFace(Window2[0], Window2[1], Window2[2], Window2[3]);

	// door
	RectangleFace(Door[0], Door[1], Door[2], Door[3]);
	

	// draw the 2nd floor walls
	glColor3f(0.8f, 0.7f, 0.5f);
	Rectangle(floor2[0], floor2[1], floor2[2], floor2[3], floor2[4], floor2[5], floor2[6], floor2[7]);

	// window
	glColor3f(1, 1, 1);
	RectangleFace(Window3[0], Window3[1], Window3[2], Window3[3]);
	RectangleFace(Window4[0], Window4[1], Window4[2], Window4[3]);

	// draw roof
	glColor3f(0.7f, 0.2f, 0.1f);
	Pyramid(Roof[0], Roof[1], Roof[2], Roof[3], Roof[4]);
}
void DrawBike() {

}


void Display()
{
	// emptys the buffer before drawing again
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// store the original matrix of the shapes
	glLoadIdentity();
	// draws house
	DrawHouse();
	// draws bike
	DrawBike();
	// scene is rendered in the back buffer and swapped to the front to be displayed
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	// window initilization
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800,800);

	// color model and double buffer for 3d and depth buffer for Z  axis
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Basic OpenGL program");
	
	MyInit();

	// ptr to function to execute and display
	glutDisplayFunc(Display);

	// call back function that uses spin to rotate objects
	glutIdleFunc(Spin);

	// the main loop to keep displaying
	glutMainLoop();
	return 0;
}
