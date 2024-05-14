#include <windows.h>
#include <gl/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include<iostream>

using namespace std;

GLfloat Cx = 0, Cy = 0, Cz = 3;
GLfloat T = 0;
GLfloat wheelRot = 0;
GLfloat doorRotation = 0;
GLfloat windowRotation = 0;
GLfloat rotations[3] = { -30, 0, 35 };
int rotInd = 1;

const GLfloat pi = 3.14159265359;
GLfloat moveX = 0.0;
bool aroundHouse = false;

void Spin()
{
	if(aroundHouse)
		T = T - 0.25;

	glutPostRedisplay();
}
void Ground() {
	// Draw the outer white circle
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0); // white color
	for (int i = 0; i < 360; i++) {
		glVertex3f(cos(i) * 1.385, -0.5003, sin(i) * 1.385); // center at (0, -0.5, 0)
	}
	glEnd();
	// Draw the inner white circle
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0); // white color
	for (int i = 0; i < 360; i++) {
		glVertex3f(cos(i) * 0.8, -0.5001, sin(i) * 0.8); // center at (0, -0.5, 0)
	}
	glEnd();
	// Draw the inner black circle representing the ground
	glBegin(GL_POLYGON);
	glColor3f(0.25, 0.25, 0.25); // black color
	for (int i = 0; i < 360; i++) {
		glVertex3f(cos(i) * 1.3, -0.5002, sin(i) * 1.3); // smaller radius circle, same y-coordinate
	}
	glEnd();

}

void MyInit()
{
	glClearColor(0, 1, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 2, 10);
	glMatrixMode(GL_MODELVIEW);
}

void openRightWindows() {
	if (windowRotation) {
		glTranslatef(-0.265f, 0.001f, 0.642f);
		glRotatef(windowRotation, 0, 1, 0);
	}
}
void openLeftWindows() {
	if (windowRotation) {
		glTranslatef(-0.62f, 0.001f, 0.163f);
		glRotatef(windowRotation, 0, 1, 0);
	}
}
void openDoor() {
	if (doorRotation == 73.0f) {
		glTranslatef(-0.44f, 0.0f, 0.4f);
		glRotatef(doorRotation, 0, 1, 0);
	}
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

	glColor3f(0, 0, 0);

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
		{0.5, -0.5, 0.5},
		{-0.5, -0.5, 0.5},
		// back face Z values become negatives
		{-0.5, 0.0, -0.5},
		{0.5, 0.0, -0.5},
		{0.5, -0.5, -0.5},
		{-0.5, -0.5, -0.5},
	};
	// 2nd floor	
	GLfloat floor2[8][3] = {
		// front face
		{-0.5, 0.5, 0.5},
		{0.5, 0.5, 0.5},
		{0.5, 0.0, 0.5},
		{-0.5, 0.0, 0.5},
		// back face Z values become negatives
		{-0.5, 0.5, -0.5},
		{0.5, 0.5, -0.5},
		{0.5, -0.0, -0.5},
		{-0.5, -0.0, -0.5},
	};
	// lower right
	GLfloat Window1[4][3] = {
		{0.20, -0.2, 0.50001},  // upperleft
		{0.30, -0.2, 0.50001}, // upper right
		{0.30, -0.3, 0.50001}, // bottom right
		{0.20, -0.3, 0.50001} // bottom left
	};
	// lower left
	GLfloat Window2[4][3] = {
		{-0.30, -0.2, 0.50001}, // upper left
		{-0.20, -0.2, 0.50001}, // upper right
		{-0.20, -0.3, 0.50001}, // lower right
		{-0.30, -0.3, 0.50001}  // lower left
	};
	// upper right 
	GLfloat Window3[4][3] = {
		{0.30, 0.2, 0.50001},
		{0.20, 0.2, 0.50001},
		{0.20, 0.3, 0.50001},
		{0.30, 0.3, 0.50001}
	};
	// upper left 
	GLfloat Window4[4][3] = {
		{-0.30, 0.2, 0.50001},
		{-0.20, 0.2, 0.50001},
		{-0.20, 0.3, 0.50001},
		{-0.30, 0.3, 0.50001}
	};
	// door
	GLfloat Door[4][3] = {
		{0.05, -0.5, 0.5001},
		{0.05, -0.3, 0.5001},
		{-0.05, -0.3, 0.5001},
		{-0.05, -0.5, 0.5001}
	};

	// roof
	GLfloat Roof[5][3] = {
		// pyramid tip
		{0.0, 0.8, 0},
		// pyramid base
		{-0.5, 0.5, 0.5},
		{0.5, 0.5, 0.5},
		{-0.5, 0.5, -0.5},
		{0.5, 0.5, -0.5},

	};

	// draw the 1st floor walls
	glColor3f(0.8f, 0.6f, 0.4f);
	Rectangle(floor1[0], floor1[1], floor1[2], floor1[3], floor1[4], floor1[5], floor1[6], floor1[7]);

	// draw the 2nd floor walls
	glColor3f(0.8f, 0.7f, 0.5f);
	Rectangle(floor2[0], floor2[1], floor2[2], floor2[3], floor2[4], floor2[5], floor2[6], floor2[7]);

	// windows
	glColor3f(1, 1, 1);
	// windows on the right side
	glPushMatrix();
		openRightWindows();
		RectangleFace(Window1[0], Window1[1], Window1[2], Window1[3]);
		RectangleFace(Window3[0], Window3[1], Window3[2], Window3[3]);
	glPopMatrix();
	// windows on the left side
	glPushMatrix();
		openLeftWindows();
		RectangleFace(Window2[0], Window2[1], Window2[2], Window2[3]);
		RectangleFace(Window4[0], Window4[1], Window4[2], Window4[3]);
	glPopMatrix();

	// door
	glColor3f(0.7f, 0.2f, 0.1f);
	glPushMatrix(); 
		openDoor();
		RectangleFace(Door[0], Door[1], Door[2], Door[3]);
	glPopMatrix();
	
	// draw roof
	glColor3f(0.7f, 0.2f, 0.1f);
	Pyramid(Roof[0], Roof[1], Roof[2], Roof[3], Roof[4]);
	
	// shadows
	glColor3f(0, 0, 0);
	RectangleFace(Door[0], Door[1], Door[2], Door[3]);
	RectangleFace(Window1[0], Window1[1], Window1[2], Window1[3]);
	RectangleFace(Window2[0], Window2[1], Window2[2], Window2[3]);
	RectangleFace(Window3[0], Window3[1], Window3[2], Window3[3]);
	RectangleFace(Window4[0], Window4[1], Window4[2], Window4[3]);
}


void Cuboid(GLfloat vertices[8][3]) {
	// Draw top
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
		glVertex3fv(vertices[i]);
	glEnd();
	// Draw buttom
	glBegin(GL_POLYGON);
	for (int i = 4; i < 8; i++)
		glVertex3fv(vertices[i]);
	glEnd();

	// Draw sides
	for (int i = 0; i < 4; i++) {
		glBegin(GL_POLYGON);
		int nxt = (i + 1) % 4;
		glVertex3fv(vertices[i]);
		glVertex3fv(vertices[nxt]);
		glVertex3fv(vertices[nxt + 4]);
		glVertex3fv(vertices[i + 4]);
		glEnd();
	}
}

void PointToCuboid(GLfloat center[3]) {
	GLfloat dist = 0.006;
	GLfloat OC[8][3] = {
		{center[0] - dist, center[1] - dist, center[2] - dist},
		{center[0] + dist, center[1] - dist, center[2] - dist},
		{center[0] + dist, center[1] - dist, center[2] + dist},
		{center[0] - dist, center[1] - dist, center[2] + dist},

		{center[0] - dist, center[1] + dist, center[2] - dist},
		{center[0] + dist, center[1] + dist, center[2] - dist},
		{center[0] + dist, center[1] + dist, center[2] + dist},
		{center[0] - dist, center[1] + dist, center[2] + dist}
	};
	Cuboid(OC);
}


void Wheel(GLfloat center[3], float radius) {
	GLfloat pi = 3.14159265359;
	int seg = 60;
	for (int i = 0; i < seg; i += 1) {
		GLfloat x = radius * cos(((GLfloat)i / (GLfloat)seg) * 2 * pi);
		GLfloat y = radius * sin(((GLfloat)i / (GLfloat)seg) * 2 * pi);
		GLfloat p[3] = { center[0] + x, center[1] + y, center[2] };
		PointToCuboid(p);
	}
}

void WheelBody(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat z2, GLfloat diff, bool rear = false) {
	// Wheel body
	GLfloat C[4][8][3] = {
	{
		{x2 - diff, y1, z1},
		{x2, y1, z1},
		{x2, y1, z1 - diff},
		{x2 - diff, y1, z1 - diff},

		{x1 - diff, y2, z1},
		{x1, y2, z1},
		{x1, y2, z1 - diff},
		{x1 - diff, y2, z1 - diff}
	},
	{
		{x2 - diff, y1, z2},
		{x2, y1, z2},
		{x2, y1, z2 - diff},
		{x2 - diff, y1, z2 - diff},

		{x1 - diff, y2, z2},
		{x1, y2, z2},
		{x1, y2, z2 - diff},
		{x1 - diff, y2, z2 - diff}
	},
	{
		{x2 - diff, y1, z1},
		{x2, y1, z1},
		{x2, y1, z2 - diff},
		{x2 - diff, y1, z2 - diff},

		{x2 - diff, y1 - diff, z1},
		{x2, y1 - diff, z1},
		{x2, y1 - diff, z2 - diff},
		{x2 - diff, y1 - diff, z2 - diff},
	},
	{
		{x1 - diff, y2, z1},
		{x1, y2, z1},
		{x1, y2, z2 - diff},
		{x1 - diff, y2, z2 - diff},

		{x1 - diff, y2 - diff, z1},
		{x1, y2 - diff, z1},
		{x1, y2 - diff, z2 - diff},
		{x1 - diff, y2 - diff, z2 - diff},
	}
	};


	glColor3f(0, 0, 0);
	for (int i = 0; i < 4; i++)
		Cuboid(C[i]);

	// wheel itself
	GLfloat WheelCentre[3] = { x2 - diff, y1, (z1 + z2) / 2};
	if(rear)
		WheelCentre[0] = x1 - diff, WheelCentre[1] = y2;
	Wheel(WheelCentre, 0.04);

	if (!rear) {
		// Handle support
		GLfloat midZ = (z1 + z2) / 2;
		GLfloat Support[8][3] = {
			{x1 - diff, y2, midZ},
			{x1, y2, midZ},
			{x1, y2, midZ - diff},
			{x1 - diff, y2, midZ - diff},

			{x1 - diff, y2 + 0.03, midZ},
			{x1, y2 + 0.03, midZ},
			{x1, y2 + 0.03, midZ - diff},
			{x1 - diff, y2 + 0.03, midZ - diff}
		};

		Cuboid(Support);

		// Handle

		GLfloat Handle[8][3] = {
			{x1 - diff, y2 + 0.03, midZ + 0.03},
			{x1, y2 + 0.03, midZ + 0.03},
			{x1, y2 + 0.03, midZ - diff - 0.03},
			{x1 - diff, y2 + 0.03, midZ - diff - 0.03},

			{x1 - diff, y2 + 0.04, midZ + 0.03},
			{x1, y2 + 0.04, midZ + 0.03},
			{x1, y2 + 0.04, midZ - diff - 0.03},
			{x1 - diff, y2 + 0.04, midZ - diff - 0.03}
		};

		Cuboid(Handle);
	}

	GLfloat dist = 0.006;
	GLfloat r = 0.04;
	GLfloat ratio = 0.6;
	GLfloat rad = ratio * 2 * pi;
	GLfloat sinRes = r * sin(rad);
	GLfloat cosRes = r * cos(rad);
	// Wheel support
	GLfloat Support[3][8][3] = {
		{
			{WheelCentre[0] - dist - cosRes, WheelCentre[1] - dist + sinRes, WheelCentre[2] - dist},
			{WheelCentre[0] + dist - cosRes, WheelCentre[1] - dist + sinRes, WheelCentre[2] - dist},
			{WheelCentre[0] + dist - cosRes, WheelCentre[1] - dist + sinRes, WheelCentre[2] + dist},
			{WheelCentre[0] - dist - cosRes, WheelCentre[1] - dist + sinRes, WheelCentre[2] + dist},

			{WheelCentre[0] - dist, WheelCentre[1] - dist, WheelCentre[2] - dist},
			{WheelCentre[0] + dist, WheelCentre[1] - dist, WheelCentre[2] - dist},
			{WheelCentre[0] + dist, WheelCentre[1] - dist, WheelCentre[2] + dist},
			{WheelCentre[0] - dist, WheelCentre[1] - dist, WheelCentre[2] + dist},
		},
		{
			{WheelCentre[0] - dist, WheelCentre[1] - dist, WheelCentre[2] - dist},
			{WheelCentre[0] + dist, WheelCentre[1] - dist, WheelCentre[2] - dist},
			{WheelCentre[0] + dist, WheelCentre[1] - dist, WheelCentre[2] + dist},
			{WheelCentre[0] - dist, WheelCentre[1] - dist, WheelCentre[2] + dist},

			{WheelCentre[0] - dist, WheelCentre[1] - dist + r, WheelCentre[2] - dist},
			{WheelCentre[0] + dist, WheelCentre[1] - dist + r, WheelCentre[2] - dist},
			{WheelCentre[0] + dist, WheelCentre[1] - dist + r, WheelCentre[2] + dist},
			{WheelCentre[0] - dist, WheelCentre[1] - dist + r, WheelCentre[2] + dist},
		},
		{
			{WheelCentre[0] - dist + cosRes, WheelCentre[1] - dist + sinRes, WheelCentre[2] - dist},
			{WheelCentre[0] + dist + cosRes, WheelCentre[1] - dist + sinRes, WheelCentre[2] - dist},
			{WheelCentre[0] + dist + cosRes, WheelCentre[1] - dist + sinRes, WheelCentre[2] + dist},
			{WheelCentre[0] - dist + cosRes, WheelCentre[1] - dist + sinRes, WheelCentre[2] + dist},

			{WheelCentre[0] - dist, WheelCentre[1] - dist, WheelCentre[2] - dist},
			{WheelCentre[0] + dist, WheelCentre[1] - dist, WheelCentre[2] - dist},
			{WheelCentre[0] + dist, WheelCentre[1] - dist, WheelCentre[2] + dist},
			{WheelCentre[0] - dist, WheelCentre[1] - dist, WheelCentre[2] + dist},
		}
	};

	for (int i = 0; i < 3; i++)
		Cuboid(Support[i]);
}

void BicycleMid(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2, GLfloat z1, GLfloat diff) {
	GLfloat cdiff = 0.01;

	GLfloat C1[8][3] = {
		{x1, y2, z1 - diff},
		{x1 - diff, y2, z1 - diff},
		{x1 - diff, y2, z1},
		{x1, y2, z1},

		{x1 - 0.13, y1, z1 - diff},
		{x1 - 0.12, y1, z1 - diff},
		{x1 - 0.12, y1, z1},
		{x1 - 0.13, y1, z1}
	};

	Cuboid(C1);

	// Chair
	GLfloat Chair[8][3] = {
		{x2 + cdiff, y1, z1 - 0.01},
		{x2 - diff - cdiff, y1, z1 - 0.01},
		{x2 - diff - cdiff, y1, z1},
		{x2 + cdiff, y1, z1},

		{x2 + cdiff, y1 - 0.02, z1 - 0.01},
		{x2 - diff - cdiff, y1 - 0.02, z1 - 0.01},
		{x2 - diff - cdiff, y1 - 0.02, z1},
		{x2 + cdiff, y1 - 0.02, z1}
	};

	Cuboid(Chair);
}

void DrawBike() {
	glPushMatrix();
	glRotatef(T, 0, 1, 0);
	// Front wheel
	glPushMatrix();
	if(rotInd == 0)
		glTranslatef(0.475, 0, 0.115);
	else if(rotInd == 2)
		glTranslatef(-0.51, 0, 0.14);
	glRotatef(wheelRot, 0, 1, 0);

	WheelBody(-0.02 + moveX, -0.06 + moveX, -0.44, -0.34, 0.9, 0.93, 0.01);
	glPopMatrix();
	// Connect the two wheels
	BicycleMid(0.1 + moveX, 0.06 + moveX, -0.34, -0.44, 0.91, 0.01);
	// Rear wheel
	WheelBody(0.1 + moveX, 0.06 + moveX, -0.34, -0.44, 0.9, 0.93, 0.01, true);
	glPopMatrix();
}

void mouseclk(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		moveX = 0;
		aroundHouse = true;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		moveX = 0;
		aroundHouse = false;
	}
}

void button(unsigned char button, int x, int y) {
	switch (button) {
	case 'o': 
		doorRotation = 73.0f;
		break;
	case 'c': 
		doorRotation = 0.0f;
		break;
	case 'O':  
		windowRotation = 73.0f;
		break;
	case 'C':  
		windowRotation = 0.0f;
		break;
	case 'f': 
		moveX -= 0.05;
		rotInd = 1;
		wheelRot = 0;
		T = 0;
		aroundHouse = false;
		break;
	case 'b':
		moveX += 0.05;
		rotInd = 1;
		wheelRot = 0;
		T = 0;
		aroundHouse = false;
		break;
	case 'r':
		moveX = 0;
		if (rotInd != 0) {
			rotInd--;
			wheelRot = rotations[rotInd];
		}
		break;
	case 'l':
		moveX = 0;
		if (rotInd != 2) {
			rotInd++;
			wheelRot = rotations[rotInd];
		}
		break;

	// camera hotkeys
	case '4':
		Cx = Cx - 0.5;
		break;
	case '7':
		Cx = Cx + 0.5;
		break;
	case '5':
		Cy = Cy - 0.5;
		break;
	case '8':
		Cy = Cy + 0.5;
		break;
	case '6':
		Cz = Cz - 0.5;
		break;
	case '9':
		Cz = Cz + 0.5;
		break;
	default:
		break;
	}

	glutPostRedisplay();  // Tell GLUT to redraw the scene (if needed)
}

void Display()
{
	// emptys the buffer before drawing again
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// store the original matrix of the shapes
	glLoadIdentity();
	gluLookAt(Cx, Cy, Cz, 0, 0, 0, 0, 1, 0);
	// draws the ground
	Ground();
	// translate the ground down to be the base of the house

	// draws house
	DrawHouse();
	// draws bike
	DrawBike();
	// scene is rendered in the back buffer and swapped to the front to be displayed
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	// window initilization
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 800);

	// color model and double buffer for 3d and depth buffer for Z  axis
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Basic OpenGL program");

	MyInit();
	glutMouseFunc(mouseclk);
	glutKeyboardFunc(button);
	// ptr to function to execute and display
	glutDisplayFunc(Display);

	// call back function that uses spin to rotate objects
	glutIdleFunc(Spin);

	// the main loop to keep displaying
	glutMainLoop();
	return 0;
}