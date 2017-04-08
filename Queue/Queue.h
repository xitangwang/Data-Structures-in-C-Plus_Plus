/******************************************************************************************
* Data Structures in C++ -- �����������ӡ
* ���ϼ������ 2017/3/18 11:40
* @author ������, xtwyzh@gmail.com, xtwroot.com
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
