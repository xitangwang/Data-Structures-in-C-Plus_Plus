/******************************************************************************************
* Data Structures in C++ -- 数据元素、数据结构通用输出接口
* 丁酉鸡年正月 2017/2/26 10:20
* @author 西唐王, xtwyzh@gmail.com, xtwroot.com
* xtwroot Copyright (c) 2017. All rights reserved.
******************************************************************************************/

#pragma once

#include<stdio.h>
#include <typeinfo>
#include "../BinTree/BinTree.h"
#include"../Bitmap/Bitmap.h"
#include "../BST/BST.h"
#include "../AVL/AVL.h"
#include "../Splay/Splay.h"
#include "../GraphMatrix/GraphMatrix.h"
#include "../B_Tree/BTree.h"

#define ROOT 0
#define L_CHILD 1
#define R_CHILD -1*L_CHILD

template <typename T> static void print(T* x) { x ? print(*x) : print(" <NULL>"); }
template <typename T> static void print(T & x) { UniPrint::p(x); }
template <typename T> static void print(const T& x) { UniPrint::p(x); } // for Stack
static void print(char * x) { printf(" %s", x ? x : "<NULL> "); }
static void print(const char* x) { printf("%s", x ? x : "<NULL>"); }

class UniPrint
{
public:
	static void p(int);
	static void p(float);
	static void p(double);
	static void p(char);


	template<typename T> static void p(T&); // 向量、列表等支持tracerse()遍历结构的线性结构
	template<typename T> static void p(T* s) // 所有指针
	{
		s ? p(*s) : print("<NULL>"); // 统一转为引用
	}
	template<typename T>static void p(BinNode<T> &);
	template<typename T>static void p(BinTree<T> & bt)
	{
		printf("%s[%d]*%d:\n", typeid(bt).name(), &bt, bt.size());
		Bitmap* branchType = new Bitmap;
		printBinTree(bt.root(), -1, ROOT, branchType);
		release(branchType);printf("\n");
	}

	
	template <typename T> static void p(BST<T>&); //BST
	template <typename T> static void p(AVL<T>&); //AVL
	template <typename T> static void p(Splay<T>&); //Splay
	template <typename T> static void p(BTree<T>&); //BTree
	/*
	template <typename T> static void p(RedBlack<T>&); //RedBlack
	template <typename T> static void p(Quadlist<T>&); //Quadlist
	template <typename K, typename V> static void p(Skiplist<K, V>&); //Skiplist
	template <typename K, typename V> static void p(Hashtable<K, V>&); //Hashtable
	template <typename T> static void p(PQ_List<T>&); //PQ_List
	template <typename T> static void p(PQ_ComplHeap<T>&); //PQ_ComplHeap
	template <typename T> static void p(PQ_LeftHeap<T>&); //PQ_LeftHeap
	*/
	//template <typename Tv, typename Te> static void p(GraphMatrix<Tv, Te>&); //Graph
	
}; // UniPrint

inline void UniPrint::p(int e) { printf("%04d", e); }
inline void UniPrint::p(float e) { printf("%4.1f", e); }
inline void UniPrint::p(double e) { printf("%4.1f", e); }
inline void UniPrint::p(char e) { printf("%c", (31 < e) && (e < 128) ? e : '$'); }

template <typename T>
void UniPrint::p(T& s)
{
	printf("%s[%d]*%d:\n", typeid(s).name(), &s, s.size()); // 基本信息
	s.traverse(print);
	printf("\n");
}



/******************************************************************************************
* 二叉树各种派生类的统一打印
******************************************************************************************/
template <typename T> //元素类型
static void printBinTree(BinNodePosi(T) bt, int depth, int type, Bitmap* bType)
{
	if (!bt) return;
	if (-1 < depth) //设置当前层的拐向标志
		R_CHILD == type ? bType->set(depth) : bType->clear(depth);
	printBinTree(bt->rChild, depth + 1, R_CHILD, bType); //右子树（在上）
	print(bt); printf(" *");
	for (int i = -1; i < depth; i++) //根据相邻各层
		if ((0 > i) || bType->test(i) == bType->test(i + 1)) //的拐向是否一致，即可确定
			printf("      "); //是否应该
		else  printf("│    "); //打印横线
		switch (type) {
		case  R_CHILD:  printf("┌─");  break;
		case  L_CHILD:  printf("└─");  break;
		default:  printf("──");  break; //root
		}
		print(bt);
#if defined(DSA_HUFFMAN)
		if (IsLeaf(*bt)) bType->print(depth + 1); //输出Huffman编码
#endif
		printf("\n");
		printBinTree(bt->lChild, depth + 1, L_CHILD, bType); //左子树（在下）

}


/******************************************************************************************
* BTree打印
******************************************************************************************/
#include"print_btree.h"

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
	/*printf(
		((node.lChild && &node != node.lChild->parent) ||
		(node.rChild && node != node.rChild->parent)) ?
		"@" : " "
	);*/
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
	//printf(HeightUpdated(node) ? " " : "!");//（常规）高度
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
