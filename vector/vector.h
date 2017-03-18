/******************************************************************************************
* Data Structures in C++ -- vector
* �����������إ�� 2017/1/23
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"Fib.h"

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
