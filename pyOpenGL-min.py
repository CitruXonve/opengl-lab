#!/usr/bin/python
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glFlush()
    glutSwapBuffers()

def update():
    pass

def main():
    glutInit(sys.argv)
    glutInitWindowSize(512, 512)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH)
    glutCreateWindow("The glut hello world program")
    glClearColor(0.1, 0.555555, 1.0)
    glutDisplayFunc(display)
    glutIdleFunc(update)
    glutMainLoop()

main()
