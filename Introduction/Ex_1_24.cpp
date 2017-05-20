/******************************************************************************************
* Data Structures in C++ -- ��L�ͻ�ľ���һ�����Ͻ�ȱʧ��������2^n * 2^n ������(���Ϊ��4^n - 1)
* ���ϼ������� 2017/5/8 16:58
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"gl/glut.h"

// ���ǻ�׼����(x, y)��n >= 1������
// ����ȱ�ڷ�����(dx, dy)ָ����(+1, +1)������(+1, -1)���ϡ�(-1, +1)������(-1, -1)����
// �㷨����ʼ�������Ϊcover(n, 0, 0, 1, 1)����׼����(0, 0)��ȱ�ڳ��򶫱���n������

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
	int s = 1 << (n - 1); // �����̵ı߳���2^(n-1)
	place(x + dx * (s - 1), y + dy * (s - 1), dx, dy); // ������һ��L�ͻ�ľ��������
	if(1 < n) // ֻҪ���̻�Ϊ��ȫ���ǣ���ݹ鸲���ĸ�������
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
	glutCreateWindow("�������ϰ");

	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}
