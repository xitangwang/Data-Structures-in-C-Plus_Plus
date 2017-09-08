/******************************************************************************************
* Data Structures in C++ -- ������ ADT �ӿ�
* ���ϼ��������� 2017/8/12 9:00
* @author ������, xtwyzh@gmail.com, xtwroot.com
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
// ֻ�����ʽӿ�
	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	QlistNodePosi(T) first() const { return header->succ; }
	QlistNodePosi(T) last() const { return trailer->pred; }
	bool valid(QlistNodePosi(T) p);
// ��д���ʽӿ�
	T remove(QlistNodePosi(T) p);
	QlistNodePosi(T) insertAfterAbove(T const & e, QlistNodePosi(T) p, QlistNodePosi(T) b = nullptr);
// ����
	void traverse(void(*) (T&)); // �������ڵ㣬����ʵʩָ������������ָ�룬ֻ����ֲ��޸ģ�
	template<typename VST> // ������
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
	return p->insertAsSuccAbove(e, b); // �����½ڵ��λ�� (below = nullptr)
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
int Quadlist<T>::clear() // ���Quadlist
{
	int oldSize = _size;
	while (0 < _size) remove(header->succ); // ���ɾ�����нڵ�
	return oldSize;
}



