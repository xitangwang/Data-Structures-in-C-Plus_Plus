/******************************************************************************************
* Data Structures in C++ -- ���ȼ�����ADT�ӿ�
* ���ϼ������� 2017/9/9 10:11
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

template <typename T> struct PQ
{
	virtual void insert(T item) = 0;
	virtual T getMax() = 0;
	virtual T delMax() = 0;
};