/******************************************************************************************
* Data Structures in C++ -- List interface realize
* 丙申猴年腊月廿七 2017/1/24 23:28
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"List.h"
#include"../杂项/comparator.h"

template <typename T>
void List<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	header->pred = nullptr;
	trailer->pred = header;
	trailer->succ = nullptr;
	_size = 0;
}

template <typename T>
int List<T>::clear()
{
	int oldSize = _size;
	while (0 < _size)
		remove(header->succ);
	return oldSize;
}

template <typename T>//assert: p为合法位置，且至少有n-1个后继节点
void List<T>::copyNodes(ListNode<T>* p, int n)
{
	init();
	while(n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template <typename T>
void List<T>::merge(ListNode<T>*& p, int n, List<T>& L, ListNode<T>* q, int m)
{
	// assert: this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
	// L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
    // 注意：在弻幵排序乀类癿场合，有可能 this == L && rank(p) + n = rank(q)
	ListNodePosi(T) pp = p->pred;
	while(0<m)
		if((0<n)&&(p->data<=q->data))
			{ if (q == (p = p->succ))break; --n; }
		else
			{ insertBefore(p, L.remove((q = q->succ)->pred)); m--; }
	p = pp->succ;
}

template <typename T>
void List<T>::mergeSort(ListNode<T>*& p, int n)
{
	if (n < 2)
		return;
	int m = n >> 1;
	ListNodePosi(T) q = p; for (int i = 0; i < m; ++i)q = q->succ;
	mergeSort(p, m); mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}

template <typename T>
void List<T>::selectionSort(ListNode<T>* p, int n)
{
	ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
	for (int i = 0; i < n; ++i)
		tail = tail->succ;
	while(1<n)
	{
		ListNodePosi(T) max = selectMax(head->succ, n);
		insertBefore(tail, remove(max));
		tail = tail->pred; --n;
	}
}

template <typename T>
void List<T>::insertionSort(ListNode<T>* p, int n)
{
	//int i = 1;
	//for (ListNodePosi(T) q = p->succ;i <= n; ++i, )
	//{
	//	insertAfter(search(q->data, i, p), q->data);
	//  q = q->succ;
	//	remove(q->pred);
	//}
	for (int r = 0; r < n; ++r)
	{
		insertAfter(search(p->data, r, p), p->data);
		p = p->succ; remove(p->pred);
	}
}

template <typename T>
List<T>::~List()
{
	clear();
	delete header;
	delete trailer;
}

template <typename T>
T& List<T>::operator[](Rank r) const
{
	ListNodePosi(T) p = first();
	while (0 < r--)
		p = p->succ;
	return	p->data;
}

template <typename T>
ListNode<T>* List<T>::find(T const& e, int n, ListNode<T>* p) const
{
	while (0 < n--)
		if (e == (p = p->pred)->data)
			return p;
	return nullptr;
}

template <typename T>
ListNode<T>* List<T>::search(T const& e, int n, ListNode<T>* p) const
{
	//assert: 0 <= n <= rank(p) < _size
	while (0 <= n--)
		if (((p = p->pred)->data) <= e)
			break;
	//assert: 至此位置p必符合输出语丿约定——尽管此前最后一次兲键码比较可能没有意义（等效亍不-inf比较）
	return p;
}

template <typename T>
ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n)
{
	ListNodePosi(T) max = p;
	for (ListNodePosi(T) cur = p; 1 < n; --n)
		if (!lt((cur = cur->succ)->data, max->data))
			max = cur;
	return max;
}

template <typename T>
ListNode<T>* List<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

template <typename T>
ListNode<T>* List<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template <typename T>
ListNode<T>* List<T>::insertAfter(ListNode<T>* p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

template <typename T>
ListNode<T>* List<T>::insertBefore(ListNode<T>* p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

template <typename T>
T List<T>::remove(ListNode<T>* p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p; --_size;
	return e;
}

template <typename T>
void List<T>::sort(ListNode<T>* p, int n)
{
	switch (rand()%3)
	{
	case 1:	insertionSort(p, n);
		break;
	case 2:	selectionSort(p, n);
		break;
	default: mergeSort(p, n);
		break;
	}
}

template <typename T>
int List<T>::deduplicate()
{
	if (_size < 2)
		return 0;
	int oldSize = _size;
	ListNodePosi(T) p = header; Rank r = 0;
	while(trailer!=(p=p->succ))
	{
		ListNodePosi(T) q = find(p->data, r, p);
		q ? remove(q) : r++;
	} //assert: 循环过程中的任意时刻，p的所有前驱互不相同
	return oldSize - _size;
}

template <typename T>
int List<T>::uniquify()
{
	if (_size < 2)
		return 0;
	int oldSize = _size;
	ListNodePosi(T) p; ListNodePosi(T) q;
	for (p = header, q = p->succ; trailer != q; p = q, q = q->succ)
		if (p->data == q->data)
			{ remove(q); q = p; }
	return oldSize - _size;
}

template <typename T>
void List<T>::traverse(void(*visit)(T&))
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST& visit)
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
		visit(p->data);
}

