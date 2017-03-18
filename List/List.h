/******************************************************************************************
* Data Structures in C++ -- List ADT interface
* �����������إ�� 2017/1/24 23:10
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include "ListNode.h" //�����б�ڵ���

template <typename T> class List 
{ //�б�ģ����

private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //��ģ��ͷ�ڱ���β�ڱ�

protected:
	void init(); //�б���ʱ�ĳ�ʼ��
	int clear(); //������нڵ�
	void copyNodes(ListNodePosi(T), int); //�����б�����λ��p���n��
	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int); //�鲢
	void mergeSort(ListNodePosi(T)&, int); //�Դ�p��ʼ������n���ڵ�鲢����
	void selectionSort(ListNodePosi(T), int); //�Դ�p��ʼ������n���ڵ�ѡ������
	void insertionSort(ListNodePosi(T), int); //�Դ�p��ʼ������n���ڵ��������

public:
	// ���캯��
	List() { init(); } //Ĭ��
	List(List<T> const& L) { copyNodes(L.first(), L._size); } //���帴���б�L
	List(List<T> const& L, Rank r, int n) { copyNodes(L[r], n); } //�����б�L���Ե�r�����n��
	List(ListNodePosi(T) p, int n) { copyNodes(p, n); } //�����б�����λ��p���n��
									// ��������
	~List(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
			 // ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ
	bool empty() const { return _size <= 0; } //�п�
	T& operator[] (Rank r) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
	ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
	ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��
	bool valid(ListNodePosi(T) p) //�ж�λ��p�Ƿ����Ϸ�
	{
		return p && (trailer != p) && (header != p);
	} //��ͷ��β�ڵ��ͬ��NULL
	int disordered() const; //�ж��б��Ƿ�������
	ListNodePosi(T) find(T const& e) const //�����б����
	{
		return find(e, _size, trailer);
	}
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const; //�����������
	ListNodePosi(T) search(T const& e) const //�����б����
	{
		return search(e, _size, trailer);
	}
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const; //�����������
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); //��p����n-1�������ѡ�������
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); } //���������
																		   // ��д���ʽӿ�
	ListNodePosi(T) insertAsFirst(T const& e); //��e�����׽ڵ����
	ListNodePosi(T) insertAsLast(T const& e); //��e����ĩ�ڵ����
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e); //��e����p�ĺ�̲���
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e); //��e����p��ǰ������
	T remove(ListNodePosi(T) p); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
	void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); } //ȫ�б�鲢
	void sort(ListNodePosi(T) p, int n); //�б���������
	void sort() { sort(first(), _size); } //�б���������
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��
	void reverse(); //ǰ���ã�ϰ�⣩
					// ����
	void traverse(void(*) (T&)); //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
	template <typename VST> //������
	void traverse(VST&); //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�
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

template <typename T>//assert: pΪ�Ϸ�λ�ã���������n-1����̽ڵ�
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
	// ע�⣺�ڏ�������T��m���ϣ��п��� this == L && rank(p) + n = rank(q)
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
	//assert: ����λ��p�ط��������دԼ���������ܴ�ǰ���һ�΃̼���ȽϿ���û�����壨��Чء��-inf�Ƚϣ�
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
	} //assert: ѭ�������е�����ʱ�̣�p������ǰ��������ͬ
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

