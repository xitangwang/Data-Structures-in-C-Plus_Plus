/******************************************************************************************
* Data Structures in C++ -- 打印BinTree节点
* 丁酉鸡年二月 2017/3/18 10:51
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
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
	* 父子链接指针
	****************************************************************************/
	printf(
		((node.lChildhild && &node != node.lChildhild->parent) ||
		(node.rChild && node != node.rChild->parent)) ?
		"@" : " "
	);
	/****************************************************************************
	* 节点颜色
	****************************************************************************/
#if defined(DSA_REDBLACK)
	printf(node.color == RB_BLACK ? "B" : " ");
#endif
	/****************************************************************************
	* 父子（黑）高度、NPL匹配
	****************************************************************************/
#if defined(DSA_PQ_COMPLHEAP)
	//高度不必匹配
#elif defined(DSA_PQ_LEFTHEAP)
	printf( // NPL
		(node.rChild && node.npl != 1 + node.rChild->npl) ||
		(node.lChildhild && node.npl > 1 + node.lChildhild->npl) ?
		"%%" : " "
	);
#elif defined(DSA_REDBLACK)
	printf(BlackHeightUpdated(node) ? " " : "!");//黑高度
#else
	printf(HeightUpdated(node) ? " " : "!");//（常规）高度
#endif
	/****************************************************************************
	 * 左右平衡
	 ****************************************************************************/
#if defined(DSA_AVL)
	if (!AvlBalanced(node)) printf("X"); // AVL平衡
	else if (0 < BalFac(node)) printf("\\"); //AVL平衡
	else if (BalFac(node) < 0) printf("/"); //AVL平衡
	else printf("_"); //AVL平衡
#elif defined(DSA_REDBLACK)
	if (!Balanced(node)) printf("X"); //RB平衡
	else if (0 < BalFac(node)) printf("\\"); //RB平衡
	else if (BalFac(node) < 0)printf("/"); //RB平衡
	else printf("_"); //RB平衡
#else
	//平衡无所谓
#endif
}
