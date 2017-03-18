/******************************************************************************************
* Data Structures in C++ -- Stack@vector ADT interface
* �����������إ�� 2017/1/25 12:19
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"../vector/vector.h"
template <typename T>class Stack:public Vector<T>
{
public:
	void push(T const& e) { insert(size(), e); }
	T pop() { return remove(size() - 1); }
	T& top() { return (*this)[size(0 - 1)]; }
};