/******************************************************************************************
* Data Structures in C++ -- 四联表节点
* 丁酉鸡年润六月 2017/8/12 9:00
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "../Entry/Entry.h"
#define QlistNodePosi(T) QuadlistNode<T> *

template <typename T> struct QuadlistNode
{
	T entry;
	QlistNodePosi(T) pred;QlistNodePosi(T) succ;
	QlistNodePosi(T) above;QlistNodePosi(T) below;
	QuadlistNode
	(T e = T(), QlistNodePosi(T) p = nullptr, QlistNodePosi(T) s = nullptr,
		QlistNodePosi(T) a = nullptr, QlistNodePosi(T) b = nullptr) : entry(e), pred(p), succ(s), above(a), below(b) {}

	QlistNodePosi(T) insertAsSuccAbove
	(T const& e, QlistNodePosi(T) b = nullptr);
};

template <typename T> QlistNodePosi(T) QuadlistNode<T>::insertAsSuccAbove(T const& e, QlistNodePosi(T) b = nullptr)
{
	QlistNodePosi(T) x = new QuadlistNode<T>(e, this, succ, nullptr, b);
	succ->pred = x; succ = x;
	if (b) b->above = x;
	return x;
}
