/******************************************************************************************
* Data Structures in C++ -- ��ӡBinTree�ڵ�
* ���ϼ������ 2017/3/18 10:51
* @author ������, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once
#include "print.h"
#include "../BinTree/BinNode.h"

template <typename T> void UniPrint::p(BinNode<T> & node)
{
	p(node.data);
	/****************************************************************************
	 * height & NPL
	 ****************************************************************************/
#if defined(DSA_LEFTHEAP)
	printf("(%-2d),", node.npl);
#elif defined(DSA_BST)
	printf("(%-2d)", node.height);
#elif defined(DSA_AVL)
	printf("(%-2d)", node.height);
#elif defined(DSA_REDBLACK)
	printf("(%-2d)", node.height);
#elif defined(DSA_SPLAY)
	printf("(%-2d)", node.height);
#endif
	/****************************************************************************
	* ��������ָ��
	****************************************************************************/
	printf(
		((node.lChildhild && &node != node.lChildhild->parent) ||
		(node.rChild && node != node.rChild->parent)) ?
		"@" : " "
	);
	/****************************************************************************
	* �ڵ���ɫ
	****************************************************************************/
#if defined(DSA_REDBLACK)
	printf(node.color == RB_BLACK ? "B" : " ");
#endif
	/****************************************************************************
	* ���ӣ��ڣ��߶ȡ�NPLƥ��
	****************************************************************************/
#if defined(DSA_PQ_COMPLHEAP)
	//�߶Ȳ���ƥ��
#elif defined(DSA_PQ_LEFTHEAP)
	printf( // NPL
		(node.rChild && node.npl != 1 + node.rChild->npl) ||
		(node.lChildhild && node.npl > 1 + node.lChildhild->npl) ?
		"%%" : " "
	);
#elif defined(DSA_REDBLACK)
	printf(BlackHeightUpdated(node) ? " " : "!");//�ڸ߶�
#else
	printf(HeightUpdated(node) ? " " : "!");//�����棩�߶�
#endif
	/****************************************************************************
	 * ����ƽ��
	 ****************************************************************************/
#if defined(DSA_AVL)
	if (!AvlBalanced(node)) printf("X"); // AVLƽ��
	else if (0 < BalFac(node)) printf("\\"); //AVLƽ��
	else if (BalFac(node) < 0) printf("/"); //AVLƽ��
	else printf("_"); //AVLƽ��
#elif defined(DSA_REDBLACK)
	if (!Balanced(node)) printf("X"); //RBƽ��
	else if (0 < BalFac(node)) printf("\\"); //RBƽ��
	else if (BalFac(node) < 0)printf("/"); //RBƽ��
	else printf("_"); //RBƽ��
#else
	//ƽ������ν
#endif
}
