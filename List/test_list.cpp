/******************************************************************************************
* Data Structures in C++ -- list 测试用例
* 丁酉鸡年正月 2017/2/19 11:56
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"List.h"
#include<iostream>

using namespace std;

void main()
{
	List<int> list;

	for (int i = 0; i < 10; ++i)
	{
		list.insertAsLast(i);
	}

	for (int i = 0;i < 10;++i)
	{
		cout << list[i] << " ";
	}


	cin.get();
}