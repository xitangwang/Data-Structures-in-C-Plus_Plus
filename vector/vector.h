/******************************************************************************************
* Data Structures in C++ -- vector
* 丙申猴年腊月廿六 2017/1/23
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"Fib.h"

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
