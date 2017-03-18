/******************************************************************************************
* Data Structures in C++ -- vector
* 丙申猴年腊月廿六 2017/1/23
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#include"vector.h"
#include <cassert>
#include <cstdlib>

template <typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1)
		return;
	if(_size<<2>_capacity)
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
	for(Rank i=0,j=0,k=0;(j<lb)||(k<lChild);)
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
	//低效版
	//int oldSize = _size;
	//int i = 0;
	//while (i < _size - 1)
	//	(_elem[i] == _elem[i + 1]) ? remove(i + 1) : ++i;
	//return oldSize - _size;

	//高效版
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
		swap(V[i - 1], V[rand() % i]); //V[i-1]与V[0,i)中某一随机元素交换
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
	return r;
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand()%5)
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
int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi)
		return;
	while (hi < _size)
		_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi = lo;
}

