/******************************************************************************************
* Data Structures in C++ -- 四联表 ADT 接口
* 丁酉鸡年润六月 2017/8/12 9:00
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "QuadlistNode.h"

template <typename T>
class Quadlist
{
private:
	int _size;QlistNodePosi(T) header;QlistNodePosi(T) trailer;
protected:
	void init();
	int clear();
public:
	Quadlist() { init(); }
	~Quadlist() { clear();delete header;delete trailer; }
// 只读访问接口
	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	QlistNodePosi(T) first() const { return header->succ; }
	QlistNodePosi(T) last() const { return trailer->pred; }
	bool valid(QlistNodePosi(T) p);
// 可写访问接口
	T remove(QlistNodePosi(T) p);
	QlistNodePosi(T) insertAfterAbove(T const & e, QlistNodePosi(T) p, QlistNodePosi(T) b = nullptr);
// 遍历
	void traverse(void(*) (T&)); // 遍历各节点，依次实施指定操作（函数指针，只读或局部修改）
	template<typename VST> // 操作器
	void traverse(VST&);

};

template<typename T>
inline void Quadlist<T>::init()
{
	header = new QuadlistNode<T>;
	trailer = new QuadlistNode<T>;
	header->succ = trailer; header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;
	header->above = trailer->above = nullptr;
	header->below = trailer->below = nullptr;
	_size = 0;
}


template <typename T>
QuadlistNode<T>* Quadlist<T>::insertAfterAbove(T const& e, QuadlistNode<T>* p, QuadlistNode<T>* b = nullptr)
{
	_size++;
	return p->insertAsSuccAbove(e, b); // 返回新节点的位置 (below = nullptr)
}

template <typename T>
bool Quadlist<T>::valid(QuadlistNode<T>* p)
{
	return ((p != nullptr) && (trailer != p) && (header != p));
}

template <typename T>
T Quadlist<T>::remove(QuadlistNode<T>* p)
{
	p->pred->succ = p->succ; p->succ->pred = p->pred; _size--;
	T e = p->entry; delete p;
	return e;
}

template <typename T>
int Quadlist<T>::clear() // 清空Quadlist
{
	int oldSize = _size;
	while (0 < _size) remove(header->succ); // 逐个删除所有节点
	return oldSize;
}



