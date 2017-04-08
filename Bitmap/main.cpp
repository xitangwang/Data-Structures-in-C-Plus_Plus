/******************************************************************************************
* Data Structures in C++ -- Bitmap测试用例
* 丁酉鸡年二月 2017/3/20 9:42
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"Bitmap1.h"
#include <iostream>

int main()
{
	Bitmap bitmap;
	bitmap.set(7);
	bitmap.print(64);
	std::cin.get();
	return 0;
}
