// g++ "D:\sempr\dev\opengl-lab\glut-min.cpp" -o "D:\sempr\dev\opengl-lab\glut-min" -lfreeglut -lopengl32
#include <GL/glut.h>
#include <cmath>
#define PI 3.1415926535897932384626433832795

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
void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	// glBegin(GL_POLYGON);
	// glVertex2f(-0.5, -0.5);
	// glVertex2f(-0.5, 0.5);
	// glVertex2f(0.5, 0.5);
	// glVertex2f(0.5, -0.5);
	// glEnd();
	drawFilledCircle(0,0,1);
	glFlush();
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("simple");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}