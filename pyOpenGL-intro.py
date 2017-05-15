#!/usr/bin/python
# coding:utf-8
import random
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

ROTATE_RATE = 0.25
SELFROTATE_RATE = 1.0

a1 = a2 = 0


def init():
    light0_diffuse = [1.0, 0.5, 0.0, 1.0]  # light0中漫反射光分量
    light0_position = [10.0, 20.0, -150.0, 1.0]  # light0的坐标位置
    light0_direction = [0.0, 0.0, -1.0]  # light0的聚光灯方向角
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse)  # light0在太阳中心
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position)
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction)
    glEnable(GL_DEPTH_TEST)  # 启用深度测试
    glEnable(GL_LIGHTING)  # 启用光源
    glEnable(GL_LIGHT0)
    glEnable(GL_COLOR_MATERIAL)  # 启用颜色材质模式
    glFrontFace(GL_CCW)  # 指定逆时针绕法表示多边形正面
    glClearColor(0.75, 0.75, 0.75, 1.0)  # 背景


def display():
    global a1
    global a2
    angle1=a1
    angle2=a2
    # angle1地球绕太阳旋转的角度，angle2月亮绕地球旋转的角度
    sun_emission=[0.6,0.0,0.0,1.0]#太阳颜色
    earth_emission=[0.0,0.0,0.8,1.0]#地球颜色
    moon_emission=[0.98,0.625,0.12,1.0]#月亮颜色
    light1_diffuse=[0.5,0.8,0.0,1.0]#光源light1中漫反射光分量
    light1_position=[50.0,100.0,100.0,1.0]#光源light1的坐标位置
    light1_direction=[0.0,0.0,-1.0]#光源light1的聚光灯方向角
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)#清除颜色和深度缓冲区
    glMatrixMode(GL_MODELVIEW)#指定当前操作模型视图矩阵堆栈
    glLoadIdentity()#重置模型视图矩阵
    glTranslatef(0.0,0.0,-150.0)#将图形沿z轴负向移动150.0
    # 绘制太阳
    glEnable(GL_LIGHT1)#callFPS()     glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse)
    glLightfv(GL_LIGHT1,GL_POSITION,light1_position)
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,light1_direction)
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,sun_emission)
    glutSolidSphere(12.0,30,30)#绘制太阳
    glDisable(GL_LIGHT1)
    # 绘制地球
    glPushMatrix()#保存当前的矩阵视图模型
    glRotatef(angle1,0.0,10.0,1.0)#旋转一定角度
    glTranslatef(40.0,0.0,0.0)#绕x轴正向移动40.0
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,earth_emission)
    glutSolidSphere(6.0,20,20)#绘制地球
    # 绘制月亮
    glRotatef(angle2,0.0,1.0,0.0)
    glTranslatef(15.0,0.0,0.0)#绕x轴方向移动15.0
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,moon_emission)
    glutSolidSphere(3.0,20,20)#绘制月亮
    glPopMatrix()#恢复矩阵视图模型
    angle1+=ROTATE_RATE#增加旋转步长，产生动画效果
    if angle1>=360.0:
              angle1-=360.0
    angle2+=SELFROTATE_RATE
    if angle2>=360.0:
              angle2-=360.0
    glutSwapBuffers()
    a1=angle1
    a2=angle2

def ChangeSize(w, h):
    if h==0:
        h=1
    glViewport(0,0,w,h)# 设置视区尺寸
    glMatrixMode(GL_PROJECTION)#指定当前操作投影矩阵堆栈
    glLoadIdentity()#重置投影矩阵
    gluPerspective(35.0,float(w)/float(h),1.0,500.0)#指定透视投影的观察空间
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

# def TimerFunc(x):
# 	# printf("FPS = %f\n", CalFrequency());
#     glutPostRedisplay()
#     glutTimerFunc(50,TimerFunc,1)


def update():
    glutPostRedisplay()

    # glutTimerFunc(50,TimerFunc,1)
    # display()

def plotpoints():
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(1,0,0)
    glBegin(GL_TRIANGLES)
    glVertex2f(0,0)
    glVertex2f(1,0)
    glVertex2f(1,1)
    glEnd()
    glFlush()

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(640,480)
    glutInitWindowPosition(400,200)
    glutCreateWindow(b"Sun, Moon and Earth")
    init()
    glutReshapeFunc(ChangeSize)
    glutDisplayFunc(display)
    glutIdleFunc(update)
    # glutTimerFunc(50,TimerFunc,1)

    glutMainLoop()

if __name__=="__main__":
    main()
