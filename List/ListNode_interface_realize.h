/******************************************************************************************
* Data Structures in C++ -- ListNode ingerface realize
* 丙申猴年腊月廿七 2017/1/24 23:44
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include"ListNode.h"

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


