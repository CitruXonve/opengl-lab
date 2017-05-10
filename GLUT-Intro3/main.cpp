#include <GL/gl.h>
#include <GL/glut.h>

const int day = 200; // day�ı仯����0��359

void display() {
    //glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);
    glFlush();
    glutSwapBuffers();
}

void update(){

}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(512,512);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("The glut hello world program");
    glClearColor(0.1, 0.2, 0.5, 1.0);
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutMainLoop(); // Infinite event loop
    return 0;
 }
