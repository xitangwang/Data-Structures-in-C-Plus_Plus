/******************************************************************************************
* Data Structures in C++ -- 优先级队列ADT接口
* 丁酉鸡年七月 2017/9/9 10:11
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

template <typename T> struct PQ
{
	virtual void insert(T item) = 0;
	virtual T getMax() = 0;
	virtual T delMax() = 0;
};