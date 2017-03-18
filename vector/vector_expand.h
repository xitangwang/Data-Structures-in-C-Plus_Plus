/******************************************************************************************
* Data Structures in C++
* 丙申猴年腊月廿六 2017/1/23
* 西唐王, xtwyzh@gmail.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "vector.h"

template <typename T> 
void Vector<T>::expand()
{
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	//copyForm(oldElem, 0, _size);
	for (int i=0;i<_size;++i)
	{
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}

