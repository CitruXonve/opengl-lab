#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

#include "GL\glut.h"
#include <cstdio>
#include <ctime>
#include <cstring>
#define ROTATE_RATE 0.025f
#define SELFROTATE_RATE 0.05f
#define MAX_CHAR 128
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) { // 如果是第一次调用，执行初始化
						 // 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;
		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);
		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}
void Initial()
{
	GLfloat light0_diffuse[] = { 1.0f,0.5f,0.0f,1.0f };//light0中漫反射光分量
	GLfloat light0_position[] = { 10.0f,20.0f,-150.0f,1.0f };//light0的坐标位置
	GLfloat light0_direction[] = { 0.0f,0.0f,-1.0f };//light0的聚光灯方向角
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);//light0在太阳中心
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
	glEnable(GL_DEPTH_TEST);// 启用深度测试
	glEnable(GL_LIGHTING);// 启用光源
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);//启用颜色材质模式
	glFrontFace(GL_CCW);// 指定逆时针绕法表示多边形正面
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);//背景
}

void ChangeSize(int w, int h)
{
	if (h == 0)h = 1;
	glViewport(0, 0, w, h);// 设置视区尺寸
	glMatrixMode(GL_PROJECTION);//指定当前操作投影矩阵堆栈
	glLoadIdentity();//重置投影矩阵
	gluPerspective(35.0, (float)w / (float)h, 1.0, 500.0);//指定透视投影的观察空间
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

double CalFrequency()
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
void callFPS() {
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(-30.0f, 30.0f);
	char* str = new char[12];
	sprintf(str, "FPS = %.3lf", CalFrequency());
	drawString(str);
}
void Display(void)
{
	static float angle1 = 0.0f, angle2 = 0.0f;
	//angle1地球绕太阳旋转的角度，angle2月亮绕地球旋转的角度
	GLfloat sun_emission[] = { 0.6f,0.0f,0.0f,1.0f };//太阳颜色
	GLfloat earth_emission[] = { 0.0f,0.0f,0.8f,1.0f };//地球颜色
	GLfloat moon_emission[] = { 0.98f,0.625f,0.12f,1.0f };//月亮颜色
	GLfloat light1_diffuse[] = { 0.5f,0.8f,0.0f,1.0f };//光源light1中漫反射光分量
	GLfloat light1_position[] = { 50.0f,100.0f,100.0f,1.0f };//光源light1的坐标位置
	GLfloat light1_direction[] = { 0.0f,0.0f,-1.0f };//光源light1的聚光灯方向角
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清除颜色和深度缓冲区
	glMatrixMode(GL_MODELVIEW);//指定当前操作模型视图矩阵堆栈
	glLoadIdentity();//重置模型视图矩阵
	glTranslatef(0.0f, 0.0f, -150.0f);//将图形沿z轴负向移动150.0f
	//绘制太阳
	glEnable(GL_LIGHT1);
	callFPS();
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_emission);
	glutSolidSphere(12.0f, 30, 30);//绘制太阳
	glDisable(GL_LIGHT1);
	//绘制地球
	glPushMatrix();//保存当前的矩阵视图模型
	glRotatef(angle1, 0.0f, 10.0f, 1.0f);//旋转一定角度
	glTranslatef(40.0f, 0.0f, 0.0f);//绕x轴正向移动40.0f
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, earth_emission);
	glutSolidSphere(6.0f, 20, 20);//绘制地球
	//绘制月亮
	glRotatef(angle2, 0.0f, 1.0f, 0.0f);
	glTranslatef(15.0f, 0.0f, 0.0f);//绕x轴方向移动15.0f
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moon_emission);
	glutSolidSphere(3.0f, 20, 20);//绘制月亮
	glPopMatrix();//恢复矩阵视图模型
	angle1 += ROTATE_RATE;//增加旋转步长，产生动画效果
	if (angle1 >= 360.0f)
		angle1 -= 360.0f;
	angle2 += SELFROTATE_RATE;
	if (angle2 >= 360.0f)
		angle2 -= 360.0f;

	glutSwapBuffers();
}
// void TimerFunc(int x)
//
// {
//
// 	printf("FPS = %f\n", CalFrequency());
//          glutPostRedisplay();
//
//          glutTimerFunc(50,TimerFunc,1);
//
// }
void Update() {
	glutPostRedisplay();
	// glutTimerFunc(50,TimerFunc,1);
	  // Display();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(400, 200);
	glutCreateWindow("Sun, Moon and Earth");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(Display);
	glutIdleFunc(Update);
	//  glutTimerFunc(50,TimerFunc,1);
	Initial();
	glutMainLoop();
	return 0;
}
