/******************************************************************************************
* Data Structures in C++ -- 二叉树输出打印
* 丁酉鸡年二月 2017/3/18 11:40
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "../List/List.h"

template <typename T>
class Queue :public List<T>
{
public:
	T  dequeue()
	{
		return  remove(first());
	}

	void enqueue(T const& item)
	{
		insertAsLast(item);
	}

};
