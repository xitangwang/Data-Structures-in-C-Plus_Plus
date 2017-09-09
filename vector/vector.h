/******************************************************************************************
* Data Structures in C++ -- vector
* �����������إ�� 2017/1/23
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"Fib.h"
#include "../PriorityQueue/PQ_ComplHeap.h"
#include <cassert>
#include <cstdlib>

typedef int Rank;//��
#define DEFAULT_CAPACITY 3 //Ĭ�ϵĳ�ʼ����

template <typename T> struct Increase
{
	virtual ~Increase() = default;

	virtual void operator()(T& e)
	{
		++e;
	}
}; 

// ���ֲ����㷨
//���汾A��
template <typename T> 
static Rank binSearch(T* A,T const& e,Rank lo,Rank hi)
{
	while(lo<hi)
	{
		Rank mi = (lo + hi) >> 1;
		if (e < A[mi])
			hi = mi;
		else if (A[mi] < e)
			lo = mi + 1;
		else
			return mi;
	}
	return -1;
}
//// ���汾B��
//template <typename T>
//static Rank binSearch(T* A,T const& e,Rank lo,Rank hi)
//{
//	while (1<hi-lo)
//	{
//		Rank mi = (lo + hi) >> 1;
//		(e < A[mi]) ? hi = mi : lo = mi;
//	}
//	return (e == A[lo]) ? lo : -1;
//}
// (�汾C)
//template <typename T>static Rank binSearch(T* A,T const& e,Rank lo,Rank hi)
//{
//	while(lo<hi)
//	{
//		Rank mi = (lo + hi) >> 1;
//		(e < A[mi]) ? hi = mi : lo = mi + 1;
//	}
//	return --lo;
//}



//fibonacci����
template <typename T>static Rank fibSearch(T* A,T const& e,Rank lo,Rank hi)
{
	Fib fib(hi - lo);
	while(hi-lo)
	{
		while (hi - lo < fib.get())
			fib.prev();
		Rank mi = lo + fib.get() - 1;
		if (e < A[mi])
			hi = mi;
		else if (A[mi] < e)
			lo = mi + 1;
		else
			return mi;
	}
	return -1;
}

template <typename T> class Vector
{
protected:
	Rank _size; int _capacity; T* _elem; //��ģ��������������
	void copyForm(T const * A, Rank lo, Rank hi); //������������A[lo.hi)
	void expand(); //�ռ䲻��������
	void shrink(); //װ�����ӹ�С��ѹ��
	bool bubble(Rank lo, Rank hi); //ɨ�轻��
	void bubbleSort(Rank lo, Rank hi); //��������
	Rank max(Rank lo, Rank hi); //ѡȡ���Ԫ��
	void selectionSort(Rank lo, Rank hi); //ѡ�������㷨
	void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨
	void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
	Rank partition(Rank lo, Rank hi); //��㹹���㷨
	void quickSort(Rank lo, Rank hi); //���������㷨
	void heapSort(Rank lo, Rank hi); //������
public:
// ���캯��

	//����Ϊc����ģΪs������Ԫ�س�ʼΪv
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) 
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	//�������临��
	Vector(T const * A, Rank lo, Rank hi) { copyForm(A, lo, hi); }
	//�������帴��
	Vector(T const * A, Rank n); 
	//�������临��
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyForm(V._elem, lo, hi); }
	//�������帴��
	Vector(Vector<T> const& V) { copyForm(V._elem, 0, V._size); }

// ��������

	~Vector() { delete[] _elem; }
// ֻ�����ʽӿ�

	//��ģ
	Rank size() const { return _size; }
	//�п�
	bool empty() const { return !_size; }
	//�ж������Ƿ�������
	int disordered() const;
	//���������������
	Rank find(T const& e) const { return find(e, 0, static_cast<Rank>(_size)); }
	//���������������
	Rank find(T const& e, Rank lo, Rank hi) const;
	//���������������
	Rank serach(T const& e) const
	{
		return (0 >= _size) ? -1 : serach(e, static_cast<Rank>(0),static_cast<Rank>(_size));
	}
	//���������������
	Rank serach(T const& e, Rank lo, Rank hi) const;

// ��д���ʽӿ�

	//�����±������
	T& operator[](Rank r) const;
	//���ظ��Ʋ�����
	Vector<T> &operator=(Vector<T> const&);
	//�Ƴ���Ϊr��Ԫ��
	T remove(Rank r);
	//ɾ������[lo,hi]
	int remove(Rank lo, Rank hi);
	//����Ԫ��
	Rank insert(Rank r, T const& e);
	//Ĭ��ΪĩԪ�ز���
	Rank insert(T const& e) { return insert(_size, e); }
	//��[lo,hi]����
	/**
	 * \brief 
	 * \param lo 
	 * \param hi 
	 */
	void sort(Rank lo, Rank hi);
	void heapSort();
	//��������
	void sort() { sort(0, _size); }
	//��[lo,hi]����
	void unsort(Rank lo, Rank hi);
	//����������
	void unsort() { unsort(0, _size); }
	//�������������ʹ��Ԫ�صȸ��ʳ�����ÿһλ��
	void permute(Vector<T>& V);
	//����ȥ��,���ر�ɾ��Ԫ����
	int deduplocate();
	//����ȥ��
	int uniquify();
	////ͳһ���������аm��Ԫ��
	void increase(Vector<T> & V)
	{
		V.traverse(Increase<T>());
	}

// ����

	//������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
	void traverse(void(*)(T&));
	//������ʹ�ú������󣬿�ȫ�����޸ģ�
	template<typename VST> void traverse(VST&);

}; //Vector

template <typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1)
		return;
	if (_size << 2>_capacity)
		return;
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; ++i)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
	bool sorted = true;
	while (++lo < hi)
		if (_elem[lo - 1] > _elem[lo])
		{
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	return sorted;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	assert(0 << lo&&lo < hi&&hi <= _size);
	while (!bubble(lo, hi--));
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = _elem + lo;
	int lb = mi - lo;
	T* B = new T[lb];
	for (Rank i = 0; i < lb; B[i] = A[i++]);
	int lChild = hi - mi;
	T* C = _elem + mi;
	for (Rank i = 0, j = 0, k = 0; (j<lb) || (k<lChild);)
	{
		if ((j < lb) && (!(k < lChild) || (B[j] <= C[k])))
			A[i++] = B[j++];
		if ((k < lChild) && (!(j < lb) || (C[k] < B[j])))
			A[i++] = C[k++];
	}
	delete[] B;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2)
		return;
	int mi = (lo + hi) >> 1;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template <typename T>
int Vector<T>::disordered() const
{
	int n = 0;
	for (int i = 1; i < _size; ++i)
		if (_elem[i - 1] > _elem[i])
			++n;
	return n;
}

template <typename T>
int Vector<T>::uniquify()
{
	//��Ч��
	//int oldSize = _size;
	//int i = 0;
	//while (i < _size - 1)
	//	(_elem[i] == _elem[i + 1]) ? remove(i + 1) : ++i;
	//return oldSize - _size;

	//��Ч��
	//int oldSize = _size;
	//Rank i = 0, j = 0;
	//while(i < _size - 1)
	//{
	//	if (_elem[i] == _elem[i + 1])
	//		++j;
	//	else
	//	{
	//		remove(i, j);
	//		j = ++i;
	//	}
	//}

	Rank i = 0, j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i;
	shrink();
	return j - 1;
}

template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
	/*for (int i = hi; i > lo; --i)
	if (_elem[i] == e)
	return i;
	return -1;*/
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}

template <typename T>
Rank Vector<T>::serach(T const& e, Rank lo, Rank hi) const
{
	return (rand() % 2) ?
		binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template <typename T>
T& Vector<T>::operator[](Rank r) const
{
	assert(0 <= r&&r < _size);
	return _elem[r];
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo;
	for (int i = hi - lo; i > 0; --i)
		swap(V[i - 1], V[rand() % i]);
}

template <typename T>
void Vector<T>::permute(Vector<T>& V)
{
	for (int i = V._size; i > 0; --i)
		swap(V[i - 1], V[rand() % i]); //V[i-1]��V[0,i)��ĳһ���Ԫ�ؽ���
}

template <typename T>
int Vector<T>::deduplocate()
{
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
		(find(_elem[i], 0, i)) ? i++ : remove(i);
	return oldSize = _size;
}

template <typename T>
void Vector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < _size; ++i)
		visit(_elem[i]);
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; ++i)
		visit(_elem[i]);
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem) delete[] _elem;
	copyForm(V._elem, 0, V._size);
	return *this;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
	expand();
	for (int i = _size; i > r; _elem[i] = _elem[--i]);
	_elem[r] = e;
	++_size;
	return r;
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand() % 5)
	{
	case 1:bubbleSort(lo, hi);
		break;
	case 2:selectionSort(lo, hi);
		break;
	case 3:mergeSort(lo, hi);
		break;
	case 4:heapSort(lo, hi);
		break;
	default:quickSort(lo, hi);
		break;
	}
}

template <typename T>
void Vector<T>::heapSort()
{
	hi = _elem;
	PQ_ComplHeap<T> H(0,_elem - 1);
	while (!H.empty())
		_elem[--hi] = H.delMax();
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi)
		return 0;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;
}

template <typename T>
void Vector<T>::copyForm(T const* A, Rank lo, Rank hi)
{
	//����ռ䣬��ģ����
	_elem = new T[_capacity = 2 * (hi = lo)];
	_size = 0;
	while (lo < hi)
		_elem[_size++] = A[lo++];
}

template <typename T>
void Vector<T>::expand()
{
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	//copyForm(oldElem, 0, _size);
	for (int i = 0; i<_size; ++i)
	{
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}