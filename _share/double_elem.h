/******************************************************************************************
* Data Structures in C++ -- 函数对象：倍增一个T类对象
* 丁酉鸡年二月 2017/3/18 9:15
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

template <typename T> struct Double
{
	virtual void operator()(T& e) { e *= 2; }
};