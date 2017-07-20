//============================================================
// STUDENT NAME: XU ZONGDI
// NUS User ID.: t0915251
// COMMENTS TO GRADER: 
// All the required task is accomplished, along with a "pause" hotkey added and
// FPS rates that can be shown on the window title.
// The console window is hidden.
// ============================================================

#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") 

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctime>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CONSTANTS
/////////////////////////////////////////////////////////////////////////////

#define PI                  3.1415926535897932384626433832795

#define MAX_NUM_OF_DISCS    100     // Limit the number of discs.
#define MIN_RADIUS          10.0    // Minimum radius of disc.
#define MAX_RADIUS          40.0    // Maximum radius of disc.
#define NUM_OF_SIDES        18      // Number of polygon sides to approximate a disc.

#define MIN_X_SPEED         1.0     // Minimum speed of disc in X direction.
#define MAX_X_SPEED         20.0    // Maximum speed of disc in X direction.
#define MIN_Y_SPEED         1.0     // Minimum speed of disc in Y direction.
#define MAX_Y_SPEED         20.0    // Maximum speed of disc in Y direction.

#define DESIRED_FPS         30      // Approximate desired number of frames per second.


/////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
/////////////////////////////////////////////////////////////////////////////

typedef struct discType
{
	double pos[2];          // The X and Y coordinates of the center of the disc.
	double speed[2];        // The velocity of the disc in X and Y directions. Can be negative.
	double radius;          // Radius of the disc.
	unsigned char color[3]; // R, G, B colors of the disc.
} discType;


int numDiscs = 0;                   // Number of discs that have been added.

discType disc[MAX_NUM_OF_DISCS];  // Array for storing discs.

bool drawWireframe = false;         // Draw polygons in wireframe if true, otherwise
									// otherwise polygons are filled.

bool paused = false;

int winWidth = 800;                 // Window width in pixels.
int winHeight = 600;                // Window height in pixels.

float cachedSin[NUM_OF_SIDES + 1];	// Pre-computed sine values.
float cachedCos[NUM_OF_SIDES + 1];	// Pre-computed cosine values.

// Generate a random integer ranging from [low, high]

int randInt(int low, int high) {
	return low + rand() % (high - low + 1);
}

// Generate a random float ranging from [low, high]

float randFloat(float low, float high) {
	return (high - low) * (rand() *1.0f / RAND_MAX) + low;
}

// Generate a random double-precision float ranging from [-1.0, 1.0]

double randDbl() {
	return rand()*2.0 / RAND_MAX - 1;
}

/*
* Function that handles the drawing of a circle using the triangle fan
* method. This will create a filled circle.
*/
void drawColorFilledCircle(GLfloat x, GLfloat y, GLfloat radius, const GLubyte color[3]) {
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(color[0], color[1], color[2]);
	glVertex2f(x, y); // center of circle
	for (int i = 0; i <= NUM_OF_SIDES;i++) {
		glVertex2f(
			x + (radius * cachedCos[i]),
			y + (radius * cachedSin[i])
		);
	}
	glEnd();
}

/*
* Create a filled circle filled with default color.
*/
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
	const GLubyte color[] = { 127,127,127 };
	drawColorFilledCircle(x, y, radius, color);
}

// Calculate the current frame rate
double CalcFPS()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;
	++count;
	if (count <= 50)
		return save;
	count = 0;
	last = current;
	current = clock();
	timegap = (current - last) / (double)CLK_TCK;
	save = 50.0 / timegap;
	return save;
}

// Show FPS rate on the window title
void displayFPS() {
	static char str[30] = {};
	sprintf(str, "assign1 current FPS: %.1lf", CalcFPS());
	glutSetWindowTitle(str);
	//drawString(str);
}

/////////////////////////////////////////////////////////////////////////////
// Draw the disc in its color using GL_TRIANGLE_FAN.
/////////////////////////////////////////////////////////////////////////////
void DrawDisc(const discType *d)
{
	//===========================
	// WRITE YOUR CODE HERE.
	//===========================

	drawColorFilledCircle(d->pos[0], d->pos[1], d->radius, d->color);
}

/////////////////////////////////////////////////////////////////////////////
// The display callback function.
/////////////////////////////////////////////////////////////////////////////

void MyDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (drawWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	for (int i = 0; i < numDiscs; i++) DrawDisc(&disc[i]);

	//glClearColor(0.0, 0.0, 0.0, 1.0);

	//glFlush(); // for single buffering
	glutSwapBuffers(); // for double buffering

	//displayFPS();
}

/////////////////////////////////////////////////////////////////////////////
// The mouse callback function.
// If mouse left button is pressed, a new disc is created with its center 
// at the mouse cursor position. The new disc is assigned the followings:
// (1) a random radius between MIN_RADIUS and MAX_RADIUS,
// (2) a random speed in X direction in the range 
//     from -MAX_X_SPEED to -MIN_X_SPEED, and from MIN_X_SPEED to MAX_X_SPEED.
// (3) a random speed in Y direction in the range 
//     from -MAX_Y_SPEED to -MIN_Y_SPEED, and from MIN_Y_SPEED to MAX_Y_SPEED.
// (4) R, G, B color, each ranges from 0 to 255.
/////////////////////////////////////////////////////////////////////////////

void MyMouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (numDiscs >= MAX_NUM_OF_DISCS) {
			//printf("Already reached maximum number of discs.\n");
			MessageBox(NULL, "Already reached maximum number of discs.\n", "Error",
				MB_OK | MB_ICONEXCLAMATION);
			glutPostRedisplay();
		}
		else
		{
			//===========================
			// WRITE YOUR CODE HERE.
			//===========================

			//Generate a random disc

			discType &cur = disc[numDiscs];

			cur.radius = randFloat(MIN_RADIUS, MAX_RADIUS);
			cur.pos[0] = x;cur.pos[1] = y;
			cur.color[0] = randInt(0, 255);
			cur.color[1] = randInt(0, 255);
			cur.color[2] = randInt(0, 255);

			cur.speed[0] = (randDbl() > 0.0 ? 1 : -1)* randFloat(MIN_X_SPEED, MAX_X_SPEED);
			cur.speed[1] = (randDbl() > 0.0 ? 1 : -1)* randFloat(MIN_Y_SPEED, MAX_Y_SPEED);

			numDiscs++;
			glutPostRedisplay();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// The reshape callback function.
// It also sets up the viewing.
/////////////////////////////////////////////////////////////////////////////

void MyReshape(int w, int h)
{
	winWidth = w;
	winHeight = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

	//===========================
	// WRITE YOUR CODE HERE.
	//===========================
	glLoadIdentity();
	glOrtho(0, w, h, 0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/////////////////////////////////////////////////////////////////////////////
// The keyboard callback function.
/////////////////////////////////////////////////////////////////////////////

void MyKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		// Quit program.
	case 'q':
	case 'Q': exit(0);
		break;

		// Toggle wireframe or filled polygons.
	case 'w':
	case 'W': drawWireframe = !drawWireframe;
		glutPostRedisplay();
		break;

		// Reset and erase all discs.
	case 'r':
	case 'R': numDiscs = 0;
		glutPostRedisplay();
		break;
	case 'p':
	case 'P': paused = !paused;

		// Pause the updating of circles
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Updates the positions of all the discs.
//
// Increments the position of each disc by its speed in each of the
// X and Y directions. Note that the speeds can be negative.
// At its new position, if the disc is entirely or partially outside the
// left window boundary, then shift it right so that it is inside the
// window and just touches the left window boundary. Its speed in the X 
// direction must now be reversed (negated). Similar approach is 
// applied for the cases of the right, top, and bottom window boundaries.
/////////////////////////////////////////////////////////////////////////////

void UpdateAllDiscPos(void)
{
	if (paused) return;
	for (int i = 0; i < numDiscs; i++)
	{
		//===========================
		// WRITE YOUR CODE HERE.
		//===========================

		discType &cur = disc[i];
		cur.pos[0] += cur.speed[0];
		if (cur.pos[0] <= cur.radius || cur.pos[0] >= winWidth - cur.radius) { //bounce
			cur.speed[0] *= -1;
			if (cur.pos[0] < cur.radius)
				cur.pos[0] = cur.radius;
			else
				cur.pos[0] = winWidth - cur.radius;
		}

		cur.pos[1] += cur.speed[1];
		if (cur.pos[1] <= cur.radius || cur.pos[1] >= winHeight - cur.radius) {  //bounce
			cur.speed[1] *= -1;
			if (cur.pos[1] < cur.radius)
				cur.pos[1] = cur.radius;
			else
				cur.pos[1] = winHeight - cur.radius;
		}

	}
	glutPostRedisplay();
}



/////////////////////////////////////////////////////////////////////////////
// The init function.
// It initializes some OpenGL states.
/////////////////////////////////////////////////////////////////////////////

void MyInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0); // Black background color.
	glShadeModel(GL_FLAT);
}

/*
* The glutTimerFunc() callback function
*/
void timerProc(int id)
{
	displayFPS();
	UpdateAllDiscPos();
	glutTimerFunc(1000 / DESIRED_FPS, timerProc, 0);// Call glutTimerFunc() once more to keep looping  
}

/*
* Pre-compute the vertices for a unit-radius disc
*/
void CalcCached() {
	for (int i = 0; i <= NUM_OF_SIDES;i++) {
		cachedCos[i] = cos(i *  PI*2.0f / NUM_OF_SIDES);
		cachedSin[i] = sin(i * PI*2.0f / NUM_OF_SIDES);
	}
}

/////////////////////////////////////////////////////////////////////////////
// The main function.
/////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	// Initializing random generator
	srand(time(NULL));
	// Pre-compute
	CalcCached();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("assign1");

	MyInit();

	// Register the callback functions.
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(MyMouse);
	glutKeyboardFunc(MyKeyboard);
	//glutIdleFunc(UpdateAllDiscPos);
	glutTimerFunc(1000 / DESIRED_FPS, timerProc, 0);
	// replace glutIdleFunc() to prevent excessively frequent update

	// Display user instructions in a popup window.
	char instruct[255];
	sprintf(instruct, "Click LEFT MOUSE BUTTON in window to add new disc.\n");
	sprintf(instruct + strlen(instruct), "Press 'p' to pause or resume.\n");
	sprintf(instruct + strlen(instruct), "Press 'w' to toggle wireframe.\n");
	sprintf(instruct + strlen(instruct), "Press 'r' to erase all discs.\n");
	sprintf(instruct + strlen(instruct), "Press 'q' to quit.\n");

	MessageBox(NULL, instruct, "Instruction",
		MB_OK | MB_ICONEXCLAMATION);

	// Enter GLUT event loop.
	glutMainLoop();
	return 0;
}
