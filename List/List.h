/******************************************************************************************
* Data Structures in C++ -- List ADT interface
* 丙申猴年腊月廿七 2017/1/24 23:10
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "ListNode.h" //引入列表节点类

template <typename T> class List 
{ //列表模板类

private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //规模、头哨兵、尾哨兵

protected:
	void init(); //列表创建时的初始化
	int clear(); //清除所有节点
	void copyNodes(ListNodePosi(T), int); //复制列表中自位置p起的n项
	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int); //归并
	void mergeSort(ListNodePosi(T)&, int); //对从p开始连续的n个节点归并排序
	void selectionSort(ListNodePosi(T), int); //对从p开始连续的n个节点选择排序
	void insertionSort(ListNodePosi(T), int); //对从p开始连续的n个节点插入排序

public:
	// 构造函数
	List() { init(); } //默认
	List(List<T> const& L) { copyNodes(L.first(), L._size); } //整体复制列表L
	List(List<T> const& L, Rank r, int n) { copyNodes(L[r], n); } //复制列表L中自第r项起的n项
	List(ListNodePosi(T) p, int n) { copyNodes(p, n); } //复制列表中自位置p起的n项
									// 析构函数
	~List(); //释放（包含头、尾哨兵在内的）所有节点
			 // 只读访问接口
	Rank size() const { return _size; } //规模
	bool empty() const { return _size <= 0; } //判空
	T& operator[] (Rank r) const; //重载，支持循秩访问（效率低）
	ListNodePosi(T) first() const { return header->succ; } //首节点位置
	ListNodePosi(T) last() const { return trailer->pred; } //末节点位置
	bool valid(ListNodePosi(T) p) //判断位置p是否对外合法
	{
		return p && (trailer != p) && (header != p);
	} //将头、尾节点等同于NULL
	int disordered() const; //判断列表是否已排序
	ListNodePosi(T) find(T const& e) const //无序列表查找
	{
		return find(e, _size, trailer);
	}
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const; //无序区间查找
	ListNodePosi(T) search(T const& e) const //有序列表查找
	{
		return search(e, _size, trailer);
	}
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const; //有序区间查找
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); //在p及其n-1个后继中选出最大者
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); } //整体最大者
																		   // 可写访问接口
	ListNodePosi(T) insertAsFirst(T const& e); //将e当作首节点插入
	ListNodePosi(T) insertAsLast(T const& e); //将e当作末节点插入
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e); //将e当作p的后继插入
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e); //将e当作p的前驱插入
	T remove(ListNodePosi(T) p); //删除合法位置p处的节点,返回被删除节点
	void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); } //全列表归并
	void sort(ListNodePosi(T) p, int n); //列表区间排序
	void sort() { sort(first(), _size); } //列表整体排序
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	void reverse(); //前后倒置（习题）
					// 遍历
	void traverse(void(*) (T&)); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
	template <typename VST> //操作器
	void traverse(VST&); //遍历，依次实施visit操作（函数对象，可全局性修改）
}; //List

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
	while (n--)
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
	while (0<m)
		if ((0<n) && (p->data <= q->data))
		{
			if (q == (p = p->succ))break; --n;
		}
		else
		{
			insertBefore(p, L.remove((q = q->succ)->pred)); m--;
		}
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
	while (1<n)
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
	switch (rand() % 3)
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
	while (trailer != (p = p->succ))
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
		{
			remove(q); q = p;
		}
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

