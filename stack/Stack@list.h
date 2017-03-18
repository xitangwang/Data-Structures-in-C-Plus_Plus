/******************************************************************************************
* Data Structures in C++ -- Stack@list ADT interface
* 丙申猴年腊月廿八 2017/1/25 17:28
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"../List/List.h"
template <typename T>class Stack :public List<T>
{
public:
	void push(T const& e) { insertAsLast(e); }
	T pop() { return remove(last()); }
	T& top() { return last()->data; }
};