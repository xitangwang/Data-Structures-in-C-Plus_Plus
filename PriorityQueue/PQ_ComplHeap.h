/******************************************************************************************
* Data Structures in C++ -- 优先级队列完全二叉树实现
* 丁酉鸡年七月 2017/9/9 12:11
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "../vector/vector.h"
#include "PQ.h"

// 需要用到的宏
#define InHeap(n,i) (((-1) < (i)) && ((i) < (n)))
#define Parent(i) ((i - 1) >> 1)
#define LastInternal(n) Parent(n - 1)
#define LChild(i) ((i >> 1) + 1)
#define RChild(i) ((i >> 1) + 2)
#define ParentValid(i) ((-1) < Parent(i))
#define LChildValid(n,i) (InHeap(n,LChild(i)))
#define RChildValid(n,i) (InHeap(n,RChild(i)))
#define Bigger(PQ,i,j)  (PQ[i] > PQ[j] ? i : j)
#define ProperParent(PQ,n,i) \
			(RChildValid(n,i) ? Bigger(PQ,i,RChild(i),Bigger(PQ,i,LChild(i))) : \
			(LChildValid(n,i) ? Bigger(PQ,i,LChild(i)) : i))
				
template <typename T>
class PQ_ComplHeap : public PQ<T>, public Vector<T> 
{
protected:
	Rank percolateDown(Rank n, Rank i); // 下滤
	Rank percolateUp(Rank i); // 上滤
	void heapify(Rank i); // Floyd建堆算法
public:
	PQ_ComplHeap() {}
	PQ_ComplHeap(T* A, Rank n) { this->copyFrom(A, 0, n);heapify(n); }
	void insert(T item);
	T getMax();
	T delMax();
}; // PQ_ComplHeap

template<typename T>
inline Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
{
	Rank j;
	while (i != (j = ProperParent(this->_elem, n, i)))
	{
		swap(this->_elem[i], this->_elem[j]; i = j;
	}
	return i;
}

template<typename T>
inline Rank PQ_ComplHeap<T>::percolateUp(Rank i)
{
	while (ParentValid(i) && i != Bigger(this->_elem, i, Parent(i))) // 在父节点较小的情况下
	{
		swap(this->_elem[i], this->_elem[Parent(i)]);
		i = Parent(i);
	}
	return i;
}

template<typename T>
inline void PQ_ComplHeap<T>::heapify(Rank n)
{
	for (int i = LastInternal(n);InHeap(n, i);--i)
		percolateDown(n, i);
}

template<typename T>
inline void PQ_ComplHeap<T>::insert(T item)
{
	Vector<T>::insert(item);
	percolateUp(this->_size - 1);
}

template<typename T>
inline T PQ_ComplHeap<T>::getMax()
{
	return this->_elem[0];
}

template<typename T>
inline T PQ_ComplHeap<T>::delMax()
{
	T res = this->_elem[0];
	this->_elem[0] = this->_elem[this->_size - 1];
	Vector<T>::remove(this->_size - 1);
	percolateDown(this->_size, 0);
	return res;
}