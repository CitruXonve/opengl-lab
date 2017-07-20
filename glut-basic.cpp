#pragma comment(lib,"opengl32.lib")
#include <cmath>
#include <GL/glut.h>

#define PI                  3.1415926535897932384626433832795

/*
 * Function that handles the drawing of a circle using the triangle fan
 * method. This will create a filled circle.
 *
 * Params:
 *	x (GLFloat) - the x position of the center point of the circle
 *	y (GLFloat) - the y position of the center point of the circle
 *	radius (GLFloat) - the radius that the painted circle will have
 */
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 360; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

/*
 * Function that handles the drawing of a circle using the line loop
 * method. This will create a hollow circle.
 *
 * Params:
 *	x (GLFloat) - the x position of the center point of the circle
 *	y (GLFloat) - the y position of the center point of the circle
 *	radius (GLFloat) - the radius that the painted circle will have
 */
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int lineAmount = 100; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) { 
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)), 
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}

void drawRound(const double radius, const double pos[], const unsigned char color[]) {
	glColor3f(color[0], color[1], color[2]);

	double x1 = pos[0], y1 = pos[1];

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (double angle = 1.0f;angle < 361.0f;angle += 0.2)
	{
		double x2 = x1 + sin(angle)*radius;
		double y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}

	glEnd();
}

void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.75);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.75, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();

	double pos[]={100.0,100.0};
	unsigned char color[]={127,127,127};

	//drawRound(10,pos,color);


	// glEnable(GL_POINT_SMOOTH);
	// glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	// glPointSize(10);
	// glPoint(10.0, 10.0, 0.0);
	drawFilledCircle(0.0,0.0,1.0);

	glFlush();
}

void init()
{
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("basic");
	glutDisplayFunc(mydisplay);

	init();

	glutMainLoop();
}
