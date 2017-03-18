/******************************************************************************************
* Data Structures in C++ -- get fibnacci
* 丙申猴年腊月廿七 2017/1/24
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

class Fib
{
private:
	int f, g;
public:
	 Fib(int n)
	{
		f = 1;
		g = 0;
		while (g < n)
			next();
	}
	int get() const { return g; }
	int next() { g += f; f = g - f; return g; }
	int prev() { f = g - f; g -= f; return g; }
};
