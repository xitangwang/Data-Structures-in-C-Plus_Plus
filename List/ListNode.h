/******************************************************************************************
* Data Structures in C++ -- ListNode ADT interface
* 丙申猴年腊月廿七 2017/1/24 22:50
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

typedef int Rank;
#define ListNodePosi(T) ListNode<T>*
//template <typename T> typedef ListNode<T>* ListNodePosi;


/**
 * \brief 列表节点模板类（以双向列表形式实现）
 * \tparam T 模板类型
 */
template <typename T> struct ListNode
{
//成员
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ;
//构造函数
	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) :data(e), pred(p), succ(s) {  }
//操作接口
	// 紧靠弼前节点前揑入新节点
	ListNodePosi(T) insertAsPred(T const& e);
	// 紧随弼前节点后揑入新节点
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