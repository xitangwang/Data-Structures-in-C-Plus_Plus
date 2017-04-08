/******************************************************************************************
* Data Structures in C++ -- Bitmap�ӿڼ�ʵ��
* ���ϼ������ 2017/3/19 19:46
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include <string.h>
#include <cstdio>

class Bitmap
{
private:
	bool* M;int N;
public:

	Bitmap(int n  = 8)
	{
		M = new bool[8];
		N = 8;
	}

	void set(int i) //����iλ��Ϊtrue
	{
		expand(i);
		M[i] = true;
	}

	void clear(int i) //����iλ��Ϊfalse
	{
		expand(i);
		M[i] = false;
	}

	bool test(int i) //���Ե�iλ�Ƿ�λtrue
	{
		if (i > N)
			return false;
		return M[i] == true;
	}

	void expand(int n) //����ռ䲻��������
	{
		if (n < N)
			return;
		bool* m = new bool[2 * n];
		memcpy(m, M, N);
		N = 2 * n;delete M;M = m;
	}

	/*DSA*/   void print(int n) //��λ��ӡ�Լ���λͼ���ݣ��Ǳ���ӿ�
		/*DSA*/ {
		expand(n); for (int i = 0; i < n; i++)
		{
			printf(test(i) ? "1" : "0");
			if ((i + 1) % 8 == 0)
				printf("\n");
		}
	}
};
