/******************************************************************************************
* Data Structures in C++ -- �������󣺱���һ��T�����
* ���ϼ������ 2017/3/18 9:15
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

template <typename T> struct Double
{
	virtual void operator()(T& e) { e *= 2; }
};