/******************************************************************************************
* Data Structures in C++ -- 优先级队列左式堆实现
* 丁酉鸡年七月 2017/9/9 15:11
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "PQ.h"
#include "../BinTree/BinTree.h"


template <typename T>
static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b)
{
	if (!a) return b;
	if (!b) return a;
	if (lt(a->data, b->data)) swap(a, b);
	a->rChild = merge(a->rChild, b);
	a->rChild->parent = a;
	if (!a->lChild || a->lChild->npl < a->rChild->npl)
		swap(a->lChild, a->rChild);
	a->npl = a->rChild ? a->rChild->npl + 1 : 1;
	return a;
}	

template <typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T>
{
public:
	PQ_LeftHeap() {  }
	PQ_LeftHeap(T* E, int n) //
	{
		for (int i = 0;i < n;i++) insert(E[i]);
	}
	void insert(T);
	T getMax();
	T delMax();
};

template<typename T>
inline void PQ_LeftHeap<T>::insert(T)
{
	BinNodePosi(T) v = new PQ_LeftHeap<T>(e);
	_root = merge(_root, v);
	_root->parent = nullptr;
	++_size;
}

template<typename T>
inline T PQ_LeftHeap<T>::getMax()
{
	return this->_root->data;
}

template<typename T>
inline T PQ_LeftHeap<T>::delMax()
{
	BinNodePosi(T) lHeap = _root->lChild;
	BinNodePosi(T) rHeap = _root->rChild;
	T e = _root->data;delete _root;--_size;
	merge(lHeap, rHeap);
	if (_root) _root->parent = nullptr;
	return e;
}
