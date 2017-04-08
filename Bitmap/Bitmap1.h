/******************************************************************************************
* Data Structures in C++ -- Bitmap接口及实现
* 丁酉鸡年二月 2017/3/19 19:46
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
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

	void set(int i) //将第i位置为true
	{
		expand(i);
		M[i] = true;
	}

	void clear(int i) //将第i位置为false
	{
		expand(i);
		M[i] = false;
	}

	bool test(int i) //测试第i位是否位true
	{
		if (i > N)
			return false;
		return M[i] == true;
	}

	void expand(int n) //如果空间不足则扩张
	{
		if (n < N)
			return;
		bool* m = new bool[2 * n];
		memcpy(m, M, N);
		N = 2 * n;delete M;M = m;
	}

	/*DSA*/   void print(int n) //逐位打印以检验位图内容，非必需接口
		/*DSA*/ {
		expand(n); for (int i = 0; i < n; i++)
		{
			printf(test(i) ? "1" : "0");
			if ((i + 1) % 8 == 0)
				printf("\n");
		}
	}
};
