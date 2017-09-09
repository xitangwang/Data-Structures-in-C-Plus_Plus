/******************************************************************************************
* Data Structures in C++ -- vector
* 丙申猴年腊月廿六 2017/1/23
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"Fib.h"
#include "../PriorityQueue/PQ_ComplHeap.h"
#include <cassert>
#include <cstdlib>

typedef int Rank;//秩
#define DEFAULT_CAPACITY 3 //默认的初始容量

template <typename T> struct Increase
{
	virtual ~Increase() = default;

	virtual void operator()(T& e)
	{
		++e;
	}
}; 

// 二分查找算法
//（版本A）
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
//// （版本B）
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
// (版本C)
//template <typename T>static Rank binSearch(T* A,T const& e,Rank lo,Rank hi)
//{
//	while(lo<hi)
//	{
//		Rank mi = (lo + hi) >> 1;
//		(e < A[mi]) ? hi = mi : lo = mi + 1;
//	}
//	return --lo;
//}



//fibonacci查找
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
	Rank _size; int _capacity; T* _elem; //规模、容量、数据区
	void copyForm(T const * A, Rank lo, Rank hi); //复制数组区间A[lo.hi)
	void expand(); //空间不足是扩容
	void shrink(); //装填因子过小是压缩
	bool bubble(Rank lo, Rank hi); //扫描交换
	void bubbleSort(Rank lo, Rank hi); //起泡排序法
	Rank max(Rank lo, Rank hi); //选取最大元素
	void selectionSort(Rank lo, Rank hi); //选择排序算法
	void merge(Rank lo, Rank mi, Rank hi); //归并算法
	void mergeSort(Rank lo, Rank hi); //归并排序算法
	Rank partition(Rank lo, Rank hi); //轴点构造算法
	void quickSort(Rank lo, Rank hi); //快速排序算法
	void heapSort(Rank lo, Rank hi); //堆排序
public:
// 构造函数

	//容量为c、规模为s、所有元素初始为v
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) 
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	//数组区间复制
	Vector(T const * A, Rank lo, Rank hi) { copyForm(A, lo, hi); }
	//数组整体复制
	Vector(T const * A, Rank n); 
	//向量区间复制
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyForm(V._elem, lo, hi); }
	//向量整体复制
	Vector(Vector<T> const& V) { copyForm(V._elem, 0, V._size); }

// 析构函数

	~Vector() { delete[] _elem; }
// 只读访问接口

	//规模
	Rank size() const { return _size; }
	//判空
	bool empty() const { return !_size; }
	//判断向量是否已排序
	int disordered() const;
	//无序向量整体查找
	Rank find(T const& e) const { return find(e, 0, static_cast<Rank>(_size)); }
	//无序向量区间查找
	Rank find(T const& e, Rank lo, Rank hi) const;
	//有序向量整体查找
	Rank serach(T const& e) const
	{
		return (0 >= _size) ? -1 : serach(e, static_cast<Rank>(0),static_cast<Rank>(_size));
	}
	//有序向量区间查找
	Rank serach(T const& e, Rank lo, Rank hi) const;

// 可写访问接口

	//重载下标操作符
	T& operator[](Rank r) const;
	//重载复制操作符
	Vector<T> &operator=(Vector<T> const&);
	//移除秩为r的元素
	T remove(Rank r);
	//删除区间[lo,hi]
	int remove(Rank lo, Rank hi);
	//插入元素
	Rank insert(Rank r, T const& e);
	//默认为末元素插入
	Rank insert(T const& e) { return insert(_size, e); }
	//对[lo,hi]排序
	/**
	 * \brief 
	 * \param lo 
	 * \param hi 
	 */
	void sort(Rank lo, Rank hi);
	void heapSort();
	//整体排序
	void sort() { sort(0, _size); }
	//对[lo,hi]置乱
	void unsort(Rank lo, Rank hi);
	//对整体置乱
	void unsort() { unsort(0, _size); }
	//随机置乱向量，使各元素等概率出现于每一位置
	void permute(Vector<T>& V);
	//无序去重,返回被删除元素数
	int deduplocate();
	//有序去重
	int uniquify();
	////统一逑增向量中癿各元素
	void increase(Vector<T> & V)
	{
		V.traverse(Increase<T>());
	}

// 遍历

	//遍历（使用函数指针，只读或局部性修改）
	void traverse(void(*)(T&));
	//遍历（使用函数对象，可全局性修改）
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
	//分配空间，规模清零
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