/******************************************************************************************
* Data Structures in C++ -- ListNode ADT interface
* �����������إ�� 2017/1/24 22:50
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

typedef int Rank;
#define ListNodePosi(T) ListNode<T>*
//template <typename T> typedef ListNode<T>* ListNodePosi;


/**
 * \brief �б�ڵ�ģ���ࣨ��˫���б���ʽʵ�֣�
 * \tparam T ģ������
 */
template <typename T> struct ListNode
{
//��Ա
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;
//���캯��
	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) :data(e), pred(p), succ(s) {  }
//�����ӿ�
	// ������ǰ�ڵ�ǰ�I���½ڵ�
	ListNodePosi(T) insertAsPred(T const& e);
	// ������ǰ�ڵ��I���½ڵ�
	ListNodePosi(T) insertAsSucc(T const& e);

};

template <typename T>
ListNode<T>* ListNode<T>::insertAsPred(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}

template <typename T>
ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}