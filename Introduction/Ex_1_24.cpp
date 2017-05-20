/******************************************************************************************
* Data Structures in C++ -- 用L型积木组合一个右上角缺失的正方形2^n * 2^n 的棋盘(面积为：4^n - 1)
* 丁酉鸡年四月 2017/5/8 16:58
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"gl/glut.h"

// 覆盖基准点在(x, y)的n >= 1阶棋盘
// 四种缺口方向，由(dx, dy)指定：(+1, +1)东北、(+1, -1)东南、(-1, +1)西北、(-1, -1)西南
// 算法的起始调用入口为cover(n, 0, 0, 1, 1)：基准点在(0, 0)、缺口朝向东北的n阶棋盘

void draw_cube(int x,int y,int dx,int dy)
{
	//if(!(dx == 1 && dy == 1))
	//	glRecti(x, y, x + 1, y + 1);
	//if (!(dx == 1 && dy == -1))
	//	glRecti(x, y, x + 1, x - 1);
	glRecti(x - 1, y - 1, x + 1, y + 1);
	glColor3b(255, 255, 255);
	glRecti(x, y, x + dx, y + dy);
	glFlush();
}

void place(int x, int y, int dx, int dy)
{
	glColor3b(200,200,200);
	draw_cube(x, y, dx, dy);
}

void cover_r(int n,int x = 0,int y = 0,int dx = 1,int dy = 1)
{
	int s = 1 << (n - 1); // 子棋盘的边长：2^(n-1)
	place(x + dx * (s - 1), y + dy * (s - 1), dx, dy); // 首先用一块L型积木覆盖中心
	if(1 < n) // 只要棋盘还为完全覆盖，则递归覆盖四个子棋盘
	{
		cover_r(n - 1, x, y, dx, dy);
		cover_r(n - 1, x + dx * s, y + dy * s, dx, dy);
		cover_r(n - 1, x + dx * (2 * s - 1), y, -dx, dy);
		cover_r(n - 1, x, y + dy * (2 * s - 1), dx, -dy);
	}
}

void cover_i(int n, int x = 0, int y = 0, int dx = 1, int dy = 1)
{

}

void init(void)
{
	glClearColor(0, 0, 0, 0);
	glShadeModel(GL_FLAT);
}

void reshape(int w,int h)
{
	glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
}



void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	cover_r(4);
}

int main(int argc,char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("这就是演习");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}
